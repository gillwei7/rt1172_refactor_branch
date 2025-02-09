/*!*******************************************************************
* @file CAN_app.c
* @brief CAN Stack Application Client
*
* This file represents the application client for the Garmin OSEK CAN
* Stack implementation. This file includes all of the callback
* notifications that are issued by the CAN stack from the Network
* Management Layer, including notifications for event transitions on
* the CAN Bus such as BusOFF and BusOFF recovery,failures to initialize
* the CAN controller, etc. This file also includes the application CAN
* message frame notifications that are issued by the CAN stack from the
* Interaction Layer.
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*!*******************************************************************
*
* @defgroup can_app CAN Application (CAN Stack Client)
* @ingroup app_comps
* @{
*
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "can_defs.h"
#include "can_cfg.h"
#include "can_bcfg.h"

#include "can_hw.h"
#include "can_drv.h"
#include "can_dll.h"
#include "can_dll_par.h"
#include "can_dll_prv_par.h"
#include "can_il.h"
#include "can_il_prv.h"
#include "can_il_par.h"
#include "can_il_enum.h"
#include "can_il_prv_par.h"
#include "can_nm.h"
#include "can_tp.h"
#include "can_svcs.h"
#include "can_util.h"
#include "can_nim_signals.h"

#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "MIMXRT1172.h"

#include "FreeRTOS.h"
#include "task.h"

#include "VI_pub.h"
#include "can_mid.h"
#include "CAN_pub.h"
#include "CAN_app.h"
#include "client_ble_cmd.h"
/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/
#define LC_NACK                         0xEE
#define LC_SID                          0x20
#define LC_RS_NE                        0x10
#define LC_RS_WR                        0x20
#define LC_FILL                         0x55

#define WAKEUP_GPIO                     GPIO13
#define WAKEUP_GPIO_PIN                 ( 0 )

#define PM_IGN_ON                       ( 0 )
#define PM_IGN_OFF                      ( 1 )

#if( (DEBUG_TX_CAN_SUPPORT)||(DEBUG_RX_CAN_SUPPORT) )
    #define CAN_APP_SIG_DEBUG_TICK      200 //!< 200 * 5  = 1000ms
    #define CAN_APP_FRM_DEBUG_TICK      1000//!< 1000 * 5 = 5ms
#endif

#include "client_dcm_appl.h"
#if( TRUE == APPL_CMD_DBUG )
static uint8 nm_simu_ble_data[100] = { 0 };
uint8 protobuf_length = 0x00;
uint32 data_length = 0;
uint16 rx_cmd = 0;
#endif

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/
/*------------------------------------------------------
CAN system status
------------------------------------------------------*/
typedef enum tagCAN_SYS_STAT_TYPE
    {
    CAN_SYS_STAT_INIT,
    CAN_SYS_STAT_NORMAL,
    CAN_SYS_STAT_COMM_ERR,
    CAN_SYS_STAT_PWR_OFF,

    CAN_SYS_STAT_INVALID
    } can_sys_stat_t;

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/
/*------------------------------------------------------
CAN application BusOFF Status.
------------------------------------------------------*/
static boolean
can_app_bus_off[CAN_NUM_INSTANCES];

/*------------------------------------------------------
CAN application BusOFF Status.
------------------------------------------------------*/
static boolean
can_app_timeout_error2[CAN_NUM_INSTANCES];

/*------------------------------------------------------
CAN system status
------------------------------------------------------*/
static can_sys_stat_t
can_app_sys_stat[CAN_NUM_INSTANCES] = { CAN_SYS_STAT_INIT };

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/
/*!*******************************************************************
*
* @private
* CAN controller initialization failure notification
*
* This function is the callback function that is called by the CAN
* Stack Network Management layer if the process of initializing the
* CAN controller hardware in the low level BSP CAN Driver fails.
*
*********************************************************************/
void
nm_app_notify_init_failed
    (
    can_hw_inst_t       const hw_inst
    )
{
PRINTF( "NM init failed \r\n" );
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* transmit CAN driver message frame
*
* Transmit a CAN network managment message that may be used  to check
* the CAN bus network status. A loopback message etc.
*
* @return can_ret_code
* return code indicating success or failure
*
*********************************************************************/
static can_ret_code_t
nm_app_tx_data
    (
    can_hw_inst_t           hw_inst,
    can_msg_t const * const can_msg_tx_p
    )
{
can_ret_code_t  l_ret_code;
can_tmd_t       l_can_tmd;

/*--------------------------------------------------
fill the transmit structure "Just for NM Loop back frame"
--------------------------------------------------*/
l_can_tmd.identifier    = can_msg_tx_p->id;
l_can_tmd.dlc           = can_msg_tx_p->size;
l_can_tmd.p_data        = can_msg_tx_p->data;
l_can_tmd.handle        = IL_CAN0_RX_NM_AND_LP_BK_RXFRM_HANDLE;
l_can_tmd.options       = CAN_TXMSG_STANDARD;

/*--------------------------------------------------
transmit the NM layer frame
--------------------------------------------------*/
l_ret_code = can_transmit( hw_inst, &l_can_tmd );

return l_ret_code;
}

/*!*******************************************************************
*
* @private
* Network Management layer CAN bus processing
*
* This function is the callback function that is called by the CAN
* Stack Network Management layer when a CAN bus frame has been received.
*
*********************************************************************/
void
nm_app_hook_process_receive
    (
    can_hw_inst_t       const hw_inst,
    can_rmd_t   const * const p_rmd
    )
{
/*------------------------------------------------------
CAN frame from can stack lower layer
------------------------------------------------------*/
#if( TRUE == APPL_CMD_DBUG )
/*For simulate APP ble Command with Canlayer*/
can_msg_t   l_can_msg_rx;
uint8 dlc = 0x00;
/*--------------------------------------------------
process received data from CAN lower layer
--------------------------------------------------*/
if( p_rmd->data[0] == 0xAA )
    {
    rx_cmd = ( p_rmd->data[1] << 8 ) | ( 0x00FF & p_rmd->data[2] );
    data_length = (p_rmd->data[5]);
    protobuf_length = 0;
    }
else if(p_rmd->data[0] == 0xFF && (p_rmd->data[1] == 0xFF) )
    {
    client_ble_cmd_enter_queue(rx_cmd, data_length, nm_simu_ble_data );
    }
else
    {
    dlc = p_rmd->dlc;
    memcpy( &nm_simu_ble_data[protobuf_length], p_rmd->data, dlc);
    protobuf_length += dlc;
    }
#else


can_msg_t   l_can_msg_rx;

/*--------------------------------------------------
process received data from CAN lower layer
--------------------------------------------------*/
l_can_msg_rx.id     = p_rmd->identifier;
l_can_msg_rx.size   = p_rmd->dlc;
memcpy( l_can_msg_rx.data, p_rmd->data, p_rmd->dlc );
#endif

/*--------------------------------------------------
Handling data
--------------------------------------------------*/
//TBD
}

/*!*******************************************************************
*
* @private
* CAN OnLine notification
*
* This function is the callback function that is called by the CAN
* Stack Network Management Layer when the NM layer changes state.
*
*********************************************************************/
void
nm_app_notify_state_change
    (
    can_hw_inst_t       const hw_inst,
    nm_state_t          const nm_state
    )
{
PRINTF( "NM state changed,current state: %x \r\n",nm_state );
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* CAN BusOFF notification
*
* This function is the callback function that is called by the CAN
* Stack Network Management Layer when a CAN BusOFF event occurs.
*
*********************************************************************/
void
nm_app_notify_busoff
    (
    can_hw_inst_t       const hw_inst
    )
{
PRINTF( "BusOFF! \r\n" );
can_app_bus_off[hw_inst] = TRUE;
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* CAN BusOFF recovery notification
*
* This function is the callback function that is called by the CAN
* Stack Network Management layer when a CAN bus that was previously
* faulted (BusOFF) has recovered and resumed normal operation.
*
*********************************************************************/
void
nm_app_notify_busoff_recovery
    (
    can_hw_inst_t       const hw_inst
    )
{
PRINTF( "BusOFF recovery! \r\n" );
can_app_bus_off[hw_inst] = FALSE;
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* CAN controller transmission hardware failed notification
*
* This function is the callback function that is called by the CAN
* Stack Network Management layer if the process of CAN frame transmission
* fail in CAN controller hardware driver(the low level BSP CAN Driver fails).
*
*********************************************************************/
void
nm_app_notify_tx_hw_timeout
    (
    can_hw_inst_t hw_inst,
    can_tmh_t     tmh
    )
{
PRINTF( "NM Tx HW timeout,Tx message handle: %x\r\n", tmh );
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* interaction layer frame transmission complete notify
*
* Notify interactiom layer transmission complete
* and the frame status is IL_TX_STATUS_TXC_NOTIFY
*
* @return can_ret_code
* return code indicating success or failure
*
*********************************************************************/
void
il_app_notify_tx_complete
    (
    dll_frm_handle_t        const frm_handle
    )
{
CAN_IGNORE_PARAMETER( frm_handle );
}

/*!*******************************************************************
*
* @private
* interaction layer transmission timeout
*
* Notify interactiom layer timeout when il frame transmission has a
* timeout satuation and the frame status is
* IL_TX_STATUS_TX_TIMEOUT_NOTIFY
*
* @return can_ret_code
* return code indicating success or failure
*
*********************************************************************/
void
il_app_notify_tx_timeout
    (
    dll_frm_handle_t        const frm_handle
    )
{
CAN_IGNORE_PARAMETER( frm_handle );
}

/*!*******************************************************************
*
* @private
* transmit timeout callback notification
*
* This function is the Interaction Layer frame transmit timeout
* callback notification that is called from the interaction Layer.
*
*********************************************************************/
void
il_app_notify_tx_hw_timeout
    (
    can_hw_inst_t hw_inst,
    can_tmh_t     tmh
    )
{
CAN_IGNORE_PARAMETER( tmh );
CAN_IGNORE_PARAMETER( hw_inst );
}

/*!*******************************************************************
*
* @private
* receive timeout1 callback notification
*
* This function is the Interaction Layer frame reception timeout
* callback notification that is called from the interaction Layer.
*
*********************************************************************/
void
il_app_notify_rx_timeout1
    (
    dll_frm_handle_t rmh,
    boolean          timeout_trig
    )
{
/*------------------------------------------------------
For debugging
------------------------------------------------------*/
#if( DEBUG_RX_CAN_SUPPORT )
    timeout_trig ? PRINTF( " Frm:%x TOE1 happens!\r\n", rmh ) : PRINTF( " Frm:%x TOE1 clears!\r\n", rmh );
#endif

/*------------------------------------------------------
Notify Timeout error1 status
------------------------------------------------------*/
VI_notify_timeout1_changed( rmh, timeout_trig );
}

/*!*******************************************************************
*
* @private
* receive timeout2 callback notification
*
* This function is the Interaction Layer frame reception timeout
* callback notification that is called from the interaction Layer.
*
*********************************************************************/
void
il_app_notify_rx_timeout2
    (
    dll_frm_handle_t   rmh,
    boolean            timeout_trig
    )
{
il_rxfrm_info_t     const *l_p_rxfrm_info;

uint8                     *l_p_frm_FUNCSW_status;
uint8                     *l_p_frm_ECU_indct_status;
uint8                     *l_p_frm_VH_eg_spd;

boolean                    l_toe2_FUNCSW_status;
boolean                    l_toe2_ECU_indct_status;
boolean                    l_toe2_VH_eg_spd;

/*------------------------------------------------------
Get the receive frame information and service all of
the receive frames for this CAN hardware instance
------------------------------------------------------*/
l_p_rxfrm_info = il_get_rxfrm_info_ptr( CAN_CONTROLLER_2 );

/*------------------------------------------------------
Get the receive frame status
------------------------------------------------------*/
l_p_frm_FUNCSW_status     = &( l_p_rxfrm_info->p_status[IL_CAN0_RX6_FUNCSW_STAT_IDX] );
l_p_frm_ECU_indct_status  = &( l_p_rxfrm_info->p_status[IL_CAN0_RX0_ECU_INDCT_STAT_IDX] );
l_p_frm_VH_eg_spd         = &( l_p_rxfrm_info->p_status[IL_CAN0_RXH_VH_EG_SPD_IDX] );

/*------------------------------------------------------
Get the receive frame timeout error1 status
------------------------------------------------------*/
l_toe2_FUNCSW_status     = ( ( *l_p_frm_FUNCSW_status )     & IL_RX_STATUS_TIMEOUT2 );
l_toe2_ECU_indct_status  = ( ( *l_p_frm_ECU_indct_status )  & IL_RX_STATUS_TIMEOUT2 );
l_toe2_VH_eg_spd         = ( ( *l_p_frm_VH_eg_spd ) & IL_RX_STATUS_TIMEOUT2 );

#if( DEBUG_RX_CAN_SUPPORT )
    timeout_trig ? PRINTF( " Frm:%x TOE2 happens!\r\n", rmh ) : PRINTF( " Frm:%x TOE2 clears!\r\n", rmh );
#endif

/*------------------------------------------------------
Notify Timeout error2 status
------------------------------------------------------*/
if( timeout_trig == TRUE )
    {
    /*------------------------------------------------------
    Notify VI TOE2 happened in CAN bus
    ------------------------------------------------------*/
    VI_notify_timeout2_changed( rmh, TRUE );
    can_app_timeout_error2[CAN_CONTROLLER_2] = timeout_trig;

    }
/*------------------------------------------------------
Only the two TOE2 triggered conditions(harg key and ECU
status) have been cleared, the TOE2 is clear.
------------------------------------------------------*/
else
    {
    if( ( ( *l_p_frm_ECU_indct_status ) & IL_RX_STATUS_TIMEOUT2_DIS ) == FALSE )
        {
        /*------------------------------------------------------
        Some Vehicle type use ECU_indct(0x209) and some use
        VH_eg_spd(0x20A)
        ------------------------------------------------------*/
        if( ( l_toe2_FUNCSW_status == FALSE ) &&
            ( l_toe2_ECU_indct_status == FALSE ) )
            {
            /*------------------------------------------------------
            Notify VI TOE2 have been cleared up by mid layer
            ------------------------------------------------------*/
            VI_notify_timeout2_changed( rmh, FALSE );
            can_app_timeout_error2[CAN_CONTROLLER_2] = timeout_trig;

            #if( DEBUG_RX_CAN_SUPPORT )
                PRINTF( " Frm ECU1:All TOE2 clears!\r\n" );
            #endif
            }
        }
    else
        {
        if( ( l_toe2_FUNCSW_status == FALSE ) &&
            ( l_toe2_VH_eg_spd == FALSE ) )
            {
            /*------------------------------------------------------
            Notify VI TOE2 have been cleared up by mid layer
            ------------------------------------------------------*/
            VI_notify_timeout2_changed( rmh, FALSE );
            can_app_timeout_error2[CAN_CONTROLLER_2] = timeout_trig;

            #if( DEBUG_RX_CAN_SUPPORT )
                PRINTF( " Frm ECU2:All TOE2 clears!\r\n" );
            #endif
            }
        }
    }
}

/*!*******************************************************************
*
* @private
* receive timeout1 get
*
* This function is the Interaction Layer frame reception timeout error1
* status get
*
*********************************************************************/
void
il_app_frm_timeout1_get
    (
    il_rx_frm_index_t  msg_index,
    boolean           *p_timeout_err1
    )
{
il_rxfrm_info_t     const *l_p_rxfrm_info;
uint8                     *l_p_frm_status;

/*------------------------------------------------------
Get the receive frame information and service all of
the receive frames for this CAN hardware instance
------------------------------------------------------*/
l_p_rxfrm_info = il_get_rxfrm_info_ptr( CAN_CONTROLLER_2 );

/*------------------------------------------------------
Get the receive frame status
------------------------------------------------------*/
l_p_frm_status = &( l_p_rxfrm_info->p_status[msg_index] );

/*------------------------------------------------------
Get the receive frame timeout error1 status
------------------------------------------------------*/
( *p_timeout_err1 ) = ( ( *l_p_frm_status ) & IL_RX_STATUS_TIMEOUT1 );
}

/*!*******************************************************************
*
* @private
* receive timeout2 get
*
* This function is the Interaction Layer frame reception timeout error2
* status get
*
*********************************************************************/
void
il_app_frm_timeout2_get
    (
    boolean  *p_timeout_err2
    )
{
( *p_timeout_err2 ) = can_app_timeout_error2[CAN_CONTROLLER_2];
}

/*!*******************************************************************
*
* @private
* interaction layer frame put
*
* Put a CAN message which is from other module into interation layer
* frame data structures
*
* @return can_ret_code
* return code indicating success or failure
*
*********************************************************************/
can_ret_code_t
il_app_frm_put
    (
    can_msg_t const * const can_msg_tx_p
    )
{
can_ret_code_t  l_ret_code;

/*--------------------------------------------------
put the interaction layer frame into the specific
data structures for this CAN hardware instance
--------------------------------------------------*/
l_ret_code = il_tx_put_frame_bytes( CAN_CONTROLLER_2, can_msg_tx_p );

return l_ret_code;
}

/*!*******************************************************************
*
* @private
* interaction layer frame get
*
* Get a CAN message which is from lower driver into App layer for other
* module
*
* @return can_ret_code
* return code indicating success or failure
*
*********************************************************************/
can_ret_code_t
il_app_frm_get
    (
    il_rx_frm_index_t   frm_index,
    can_msg_t          *can_msg_rx_p
    )
{
can_ret_code_t  l_ret_code = CAN_RC_NOT_AVAILABLE;

dll_rx_buf_dispatch_t   const * l_p_buf_dispatch;
dll_rx_filt_dispatch_t  const * l_p_filt_dispatch;
dll_rx_frm_dispatch_t   const * l_p_frm_dispatch;
uint8                           l_num_filters;
il_rxfrm_info_t         const * l_p_rxfrm_info;
il_rxfrm_t              const * l_p_rxfrm;

if( can_msg_rx_p == NULL )
    {
    return l_ret_code;
    }

/*------------------------------------------------------
Get the Dispatch Table for this CAN Controller hardware
instance and the specific hardware receive buffer in
this hardware instance. Also get the number of filters
enabled for this specific hardware buffer.
------------------------------------------------------*/
l_num_filters = dll_get_rx_buf_dispatch_table( CAN_CONTROLLER_2, &l_p_buf_dispatch );

/*------------------------------------------------------
Get the receive frame information and service all of
the receive frames for this CAN hardware instance
------------------------------------------------------*/
l_p_rxfrm_info = il_get_rxfrm_info_ptr( CAN_CONTROLLER_2 );

/*------------------------------------------------------
Check for valid filters and a valid filter index
------------------------------------------------------*/
if( ( l_num_filters >  0 ) &&
    ( frm_index < l_num_filters ) &&
    ( l_p_buf_dispatch != NULL ) )
    {
    /*------------------------------------------------------
    Get the CAN ID's for this filter index
    ------------------------------------------------------*/
    l_p_filt_dispatch = &( l_p_buf_dispatch->p_rx_filt_dispatch[frm_index] );
    l_p_frm_dispatch  = l_p_filt_dispatch->p_frame_dispatch;

    /*------------------------------------------------------
    Get pointers to the frame information and initially
    assume this frame is not newly received, then check for
    the frame received since the last task call
    ------------------------------------------------------*/
    l_p_rxfrm = &( l_p_rxfrm_info->p_il_rxfrm[frm_index] );

    /*------------------------------------------------------
    fill the rmd
    ------------------------------------------------------*/
    can_msg_rx_p->id    = l_p_frm_dispatch->identifier;
    can_msg_rx_p->size  = l_p_rxfrm->dlc;
    memcpy( can_msg_rx_p->data, l_p_rxfrm->p_data, l_p_rxfrm->dlc );

    l_ret_code = CAN_RC_OK;
    }

return l_ret_code;
}

/*!*******************************************************************
*
* @private
* interaction layer frame set status
*
* Set a CAN message status
*
* @return none
*
*********************************************************************/
void
il_app_frm_sig_set_status
    (
    il_rx_frm_index_t const frm_index,
    uint8             const frm_stat_bit_mask,
    il_sig_handle_t   const sig_handle,
    uint8             const sig_stat_bit_mask
    )
{
il_rxfrm_info_t   const * l_p_rxfrm_info;
uint8                   * l_p_frm_status;

il_rxsig_info_t   const * l_p_rxsig_info;
uint8                   * l_p_sig_status;
il_sig_index_t            l_sig_index;
il_sig_index_t            l_num_signals;

/*------------------------------------------------------
Get the signal handle and number
------------------------------------------------------*/
l_p_rxsig_info = il_get_rxsig_info_ptr( CAN_CONTROLLER_2 );
l_num_signals  = l_p_rxsig_info->num_signals;
l_sig_index    = IL_GET_INDEX_FROM_SIGNAL_HANDLE( sig_handle );

if( frm_index   >= IL_RX_FRM_INDEX_ERRORS ||
    l_sig_index >= l_num_signals )
    {
    return;
    }

/*------------------------------------------------------
Get the receive frame information
------------------------------------------------------*/
l_p_rxfrm_info = il_get_rxfrm_info_ptr( CAN_CONTROLLER_2 );

/*------------------------------------------------------
Get the frame status pointer and Set the status with mask
------------------------------------------------------*/
l_p_sig_status = &( l_p_rxsig_info->p_status[l_sig_index] );
can_util_set_status_bits( l_p_sig_status, sig_stat_bit_mask );

/*------------------------------------------------------
Get the frame status pointer and Set the status with mask
------------------------------------------------------*/
l_p_frm_status = &( l_p_rxfrm_info->p_status[frm_index] );
can_util_set_status_bits( l_p_frm_status, frm_stat_bit_mask );
}

/*!*******************************************************************
*
* @private
* Interaction Layer CAN message frame reception notification
*
* This function is the Interaction Layer CAN frame reception callback
* that is called by the CAN Stack when an Interaction Layer CAN
* message frame is received on the CAN bus. This notification must be
* enabled as part of configuration of the Garmin OSEK CAN Stack.
*
*********************************************************************/
void
il_app_notify_frame_received
    (
    il_rx_frm_index_t   msg_index
    )
{
can_msg_t app_can_msg_rx = {0};

il_app_frm_get( msg_index, &app_can_msg_rx );

#if( DEBUG_RX_CAN_SUPPORT )
    PRINTF( "CAN ID:%x LEN:%d ", app_can_msg_rx.id, app_can_msg_rx.size );
    for( uint8 i = 0; i < app_can_msg_rx.size; i++ )
        {
        PRINTF( "Data:%x ", app_can_msg_rx.data[i] );
        }
    PRINTF( "\r\n" );
#endif

/*------------------------------------------------------
Handle responses messages from meter
------------------------------------------------------*/
can_mid_resp_cb( &app_can_msg_rx );

/*Demo use case for software update*/
#if 0
    if( app_can_msg_rx.id == 0x5AF )
        {
        if( app_can_msg_rx.data[0] == 0xB0 && app_can_msg_rx.data[1] == 0xC0 )
            {
            ota_jump_to_bootloader();
            }
        }
#endif
/*------------------------------------------------------
Handle request or event messages from meter
------------------------------------------------------*/
VI_notify_vehicle_event_frm_changed( msg_index, &app_can_msg_rx );
}

/*!*******************************************************************
*
* @private
* Interaction Layer CAN signal reception notification
*
* This function is the Interaction Layer CAN signal reception callback
* that is called by the CAN Stack when an Interaction Layer CAN signal
* is received on the CAN bus. This callback is called regardless of
* whether the CAN signal value has changed from the previously
* received value. This notification must be enabled as part of
* configuration of the Garmin OSEK CAN Stack.
*
*********************************************************************/
void
il_app_notify_sig_received
    (
    il_sig_handle_t const sig_handle,   //!< [in] signal handle
    uint8           const num_bytes     //!< [in] signal size in bytes
    )
{
//TBD
}

/*!*******************************************************************
*
* @private
* signal changed callback notification
*
* This function is the Interaction Layer frame reception signal changed
* callback notification that is called from the interaction Layer.
* for IXWW22 the largest signal is 24 bit, so we use the 32bit signal
* value
*
*********************************************************************/
void
il_app_notify_sig_changed
    (
    il_sig_handle_t         const sig_handle,
    uint8_t                 const num_bytes,
    uint32_t                     *p_sig_val
    )
{
//TBD
}

/*!*******************************************************************
*
* @private
* signal putting
*
* This function is the network interface manager Layer frame transmit
* signal that is called from the App Layer.
* for IXWW22 the largest signal is 40 bit, so we use the 64bit signal
* value
*
*********************************************************************/
void
nim_app_sig_put
    (
    il_sig_handle_t         const sig_handle,
    uint8_t                 const num_bytes,
    uint64_t                      sig_val
    )
{
/*------------------------------------------------------
Put the signal value
------------------------------------------------------*/
uint8       l_bytes[sizeof( uint64 )];
uint64      l_temp64;
uint8       l_i_byte;

/*------------------------------------------------------
Input number bytes is over the reserved memory(uint64)
------------------------------------------------------*/
if( num_bytes > sizeof( uint64 ) )
    {
    return;
    }

/*------------------------------------------------------
Convert the UINT32 value to a byte array and transmit it
using the byte array function
------------------------------------------------------*/
l_temp64 = sig_val;

for( l_i_byte = num_bytes; l_i_byte > 0; l_i_byte-- )
    {
    l_bytes[l_i_byte - 1] = (uint8) l_temp64;
    l_temp64 = l_temp64 >> IL_NUM_BITS_IN_BYTE;
    }

il_tx_put_signal_bytes( sig_handle, &( l_bytes[0] ), num_bytes );
}

/*!*******************************************************************
*
* @private
* signal getting
*
* This function is the network interface manager Layer frame transmit
* signal that is called from the App Layer.
* for IXWW22 the largest signal is 24 bit, so we use the 32bit signal
* value
*
*********************************************************************/
void
nim_app_sig_get
    (
    il_sig_handle_t         const sig_handle,
    uint8_t                 const num_bytes,
    uint32_t                     *p_sig_val
    )
{
/*------------------------------------------------------
Put the signal value
------------------------------------------------------*/
uint8       l_bytes[sizeof( uint32 )];
uint8       l_i_byte = 0;
uint32      l_temp32 = 0;

/*------------------------------------------------------
Input number bytes is over the reserved memory(uint32)
------------------------------------------------------*/
if( num_bytes > sizeof( uint32 ) )
    {
    return;
    }

/*------------------------------------------------------
Get the signal value from memory in bytes
------------------------------------------------------*/
il_rx_get_signal_bytes( sig_handle, l_bytes, num_bytes );

/*------------------------------------------------------
Convert the a byte array to UINT32 value
------------------------------------------------------*/
for( l_i_byte = num_bytes; l_i_byte > 0; l_i_byte-- )
    {
    l_temp32 |= l_bytes[l_i_byte - 1] << ( ( num_bytes  - l_i_byte ) * IL_NUM_BITS_IN_BYTE );
    }

(*p_sig_val) = l_temp32;
}

/*!*******************************************************************
*
* @private
* Interaction layer received CAN frame CAN sending
*
* This function is called by the CAN app layer to handle CAN signals
*
*********************************************************************/
void
il_app_hook_sig_changed_handle
    (
    il_rx_frm_index_t             msg_index,
    il_sig_handle_t         const sig_handle,
    uint8_t                 const num_bytes
    )
{
uint32_t l_sig_val;

/*------------------------------------------------------
Get the changed signal value
------------------------------------------------------*/
nim_app_sig_get( sig_handle, num_bytes,&l_sig_val );

/*------------------------------------------------------
Handle the changed signal value
------------------------------------------------------*/
VI_notify_vehicle_cyc_frm_changed( msg_index, sig_handle, l_sig_val );

switch( msg_index )
    {
    case IL_CAN0_RX_NM_AND_LP_BK_IDX:
        /*--------------------------------------------------
        Network managment frame handle
        --------------------------------------------------*/
        break;

    //TBD other frames handler

    default:
        break;

    }
}

/*!*******************************************************************
*
* @private
* Interaction Layer CAN signal reception handler
*
* This function is the Interaction Layer CAN signal reception handler
* that is called by the CAN Stack when an Interaction Layer CAN signal
* is received on the CAN bus. This callback is called regardless of
* whether the CAN signal value has changed from the previously
* received value. This handler must be enabled as part of
* configuration of the Garmin OSEK CAN Stack.
*
*********************************************************************/
void
il_app_hook_sig_received_handle
    (
    il_rx_frm_index_t             msg_index,
    il_sig_handle_t         const sig_handle,
    uint8_t                 const num_bytes
    )
{
uint32_t l_sig_val;

/*------------------------------------------------------
Get the changed signal value
------------------------------------------------------*/
nim_app_sig_get( sig_handle, num_bytes,&l_sig_val );

switch( msg_index )
    {
    //TBD unchanged signals handler

    default:
        break;
    }

}

/*!*******************************************************************
*
* @public
* CAN application initialization
*
* This function is called to init CAN app
*
*********************************************************************/
void app_init
    (
    can_hw_inst_t   const hw_inst       //!< [in] CAN hardware instance
    )
{
/*------------------------------------------------------
CAN application BusOFF Status.
------------------------------------------------------*/
can_app_bus_off[CAN_CONTROLLER_2] = FALSE;

/*------------------------------------------------------
CAN application Timeout error2 Status.
------------------------------------------------------*/
can_app_timeout_error2[CAN_CONTROLLER_2] = FALSE;
}

/*!*******************************************************************
*
* @private
*
* CAN APP system status check
*
* This function is called by the CAN app layer to check if the system
* status enters IGN OFF.
*
*********************************************************************/
void
can_app_sys_stat_check
    (
    void
    )
{
volatile bool ign_status;

ign_status = GPIO_ReadPinInput( WAKEUP_GPIO, WAKEUP_GPIO_PIN );

/*------------------------------------------------------
Switch the CAN status according to thw IGN status
------------------------------------------------------*/
switch( can_app_sys_stat[CAN_CONTROLLER_2] )
    {
    case CAN_SYS_STAT_INIT:
        if( PM_IGN_ON == ign_status )
            {
            can_app_sys_stat[CAN_CONTROLLER_2] = CAN_SYS_STAT_NORMAL;
            il_resume( CAN_CONTROLLER_2 );
            }
        else
            {
            il_suspend( CAN_CONTROLLER_2 );
            }
        break;

    case CAN_SYS_STAT_NORMAL:
        if( PM_IGN_OFF == ign_status )
            {
            can_app_sys_stat[CAN_CONTROLLER_2] = CAN_SYS_STAT_PWR_OFF;
            }
        break;

    case CAN_SYS_STAT_COMM_ERR:

        break;

    case CAN_SYS_STAT_PWR_OFF:
        can_app_sys_stat[CAN_CONTROLLER_2] = CAN_SYS_STAT_INIT;
        break;

    default:
        break;
    }
}

/*!*******************************************************************
*
* @public
* CAN application periodic task
*
* This function is called periodically by the Task Manager during
* normal application execution. This task is needed to schedule and
* send the Signal Service "on change" synchronization signal values
*
*********************************************************************/
void app_task
    (
    can_hw_inst_t   const hw_inst       //!< [in] CAN hardware instance
    )
{
#if( DEBUG_RX_CAN_SUPPORT )
static uint32 test_tick = 0;

if( ( test_tick++ ) >= CAN_APP_FRM_DEBUG_TICK )
    {
    test_tick = 0;

    /*------------------------------------------------------
    Middle layer to handle request messages;
    ------------------------------------------------------*/
    il_app_frm_sig_set_status( IL_CAN0_RX3_BRGTHNSS_CTRL_IDX, ( IL_RX_STATUS_PENDING | IL_RX_STATUS_DATA_CHANGED ),
                               IL_CAN0_BRTNSS_CTRL_MT_TFT_DUTY_RXSIG_HANDLE, IL_SIG_STATUS_VALUE_CHNGD );
    }
#endif

/*------------------------------------------------------
Middle layer to handle request messages;
------------------------------------------------------*/
can_mid_task();

/*------------------------------------------------------
Handle supplement messages;
------------------------------------------------------*/
can_mid_supplement_task();

}

