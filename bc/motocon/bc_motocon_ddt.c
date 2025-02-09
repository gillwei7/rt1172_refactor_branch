/*********************************************************************
* @file
* bc_motocon_ddt.c
*
* @brief
* MotoConSDK module - ddt
*
* Copyright 2020-2021 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include <bc_motocon_priv.h>
#include <string.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "timers.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define DDT_TO_PHONE_SEMAPHORE_TIMEOUT_TICKS ( pdMS_TO_TICKS( 100 ) )
#define DDT_TO_PHONE_TIMEOUT_TICKS ( pdMS_TO_TICKS( 3000 ) )

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/
typedef struct
    {
    void ( *result_callback ) ( const bc_motocon_send_result_t );
    bc_motocon_send_type_t control_type;
    bc_motocon_send_type_t data_type;
    uint32_t total_length;
    uint8_t id;
    uint32_t remain_header;
    uint8_t header[BC_MOTOCON_PROTOBUF_HEADER_SIZE];
    uint32_t remain_content;
    const uint8_t* content;
    uint32_t send_point;
    uint32_t send_length;
    uint32_t total_send_length;
    SemaphoreHandle_t semaphore;
    TimerHandle_t timer;
    } bc_motocon_ddt_to_phone_t;

static void ddt_to_phone_timeout( TimerHandle_t timer_handle );

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/
static uint8_t  ddt_to_vehicle_status[BC_MOTOCON_DDT_STATUS_LENGTH]; // (active + session_id)
static uint32_t ddt_to_vehicle_data_size;
static uint8_t  ddt_to_vehicle_buffer[BC_MOTOCON_DDT_TO_VEHICLE_BUFFER_SIZE];
static uint8_t  ddt_to_phone_id;
static bc_motocon_ddt_to_phone_t ddt_to_phone;
static bc_motocon_ddt_to_phone_t ddt_vehicle_information;
static bc_motocon_ddt_to_phone_t ddt_can;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/


/*********************************************************************
*
* @private
* bc_motocon_ddt_init
*
* Initial ddt
*
*********************************************************************/
void bc_motocon_ddt_init
    (
    void
    )
{
ddt_to_phone.control_type = BC_MOTOCON_DDT_TO_PHONE_CONTROL_NOTIFY;
ddt_to_phone.data_type = BC_MOTOCON_DDT_TO_PHONE_DATA_NOTIFY;
ddt_vehicle_information.control_type = BC_MOTOCON_DDT_VEHICLE_INFORMATION_CONTROL_NOTIFY;
ddt_vehicle_information.data_type = BC_MOTOCON_DDT_VEHICLE_INFORMATION_DATA_NOTIFY;
ddt_can.control_type = BC_MOTOCON_DDT_CAN_CONTROL_NOTIFY;
ddt_can.data_type = BC_MOTOCON_DDT_CAN_DATA_NOTIFY;
ddt_to_phone_id = BC_MOTOCON_DDT_INACTIVE_ID;

ddt_to_phone.semaphore = xSemaphoreCreateBinary();
ddt_to_phone.timer = xTimerCreate( "DdtToPhoneTimer", DDT_TO_PHONE_TIMEOUT_TICKS, pdTRUE, ( void * ) &ddt_to_phone, ddt_to_phone_timeout );
configASSERT( NULL != ddt_to_phone.semaphore && NULL != ddt_to_phone.timer );

ddt_vehicle_information.semaphore = xSemaphoreCreateBinary();
ddt_vehicle_information.timer = xTimerCreate( "DdtVehicleInfoTimer", DDT_TO_PHONE_TIMEOUT_TICKS, pdTRUE, ( void * ) &ddt_vehicle_information, ddt_to_phone_timeout );
configASSERT( NULL != ddt_vehicle_information.semaphore && NULL != ddt_vehicle_information.timer );

ddt_can.semaphore = xSemaphoreCreateBinary();
ddt_can.timer = xTimerCreate( "DdtCanTimer", DDT_TO_PHONE_TIMEOUT_TICKS, pdTRUE, ( void * ) &ddt_can, ddt_to_phone_timeout );
configASSERT( NULL != ddt_can.semaphore && NULL != ddt_can.timer );

bc_motocon_ddt_reset();
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_reset
*
* Reset ddt status
*
*********************************************************************/
void bc_motocon_ddt_reset
    (
    void
    )
{
memset( ddt_to_vehicle_status, 0, BC_MOTOCON_DDT_STATUS_LENGTH );
ddt_to_phone.id = BC_MOTOCON_DDT_INACTIVE_ID;
ddt_vehicle_information.id = BC_MOTOCON_DDT_INACTIVE_ID;
ddt_can.id = BC_MOTOCON_DDT_INACTIVE_ID;
if( ddt_to_phone.semaphore != NULL )
    {
    xSemaphoreGive( ddt_to_phone.semaphore );
    }
if( ddt_vehicle_information.semaphore != NULL )
    {
    xSemaphoreGive( ddt_vehicle_information.semaphore );
    }
if( ddt_can.semaphore != NULL )
    {
    xSemaphoreGive( ddt_can.semaphore );
    }
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_get_ddt_to_vehicle_status
*
* Get ddt to vehicle status.
*
* @return uint8_t* (non-null)
* Return status
*
*********************************************************************/
const uint8_t* bc_motocon_ddt_get_ddt_to_vehicle_status
    (
    void
    )
{
return ddt_to_vehicle_status;
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_set_ddt_to_vehicle_status
*
* Handle ddt to vehicle control.
*
* @param bytes Pointer received data
*
* @return uint8_t* (non-null)
* Return status
*
*********************************************************************/
const uint8_t* bc_motocon_ddt_set_ddt_to_vehicle_status
    (
    const uint8_t* bytes
    )
{
BC_MOTOCON_DDT_PRINTF( "%s, %x\r\n", __FUNCTION__, bytes );
ddt_to_vehicle_status[0] = bytes[0] == BC_MOTOCON_DDT_INACTIVE_ID ? 0 : 1;
ddt_to_vehicle_status[1] = bytes[0];
ddt_to_vehicle_data_size = THREE_BYTE_BIG( bytes, 1 );
if( ddt_to_vehicle_data_size > BC_MOTOCON_DDT_TO_VEHICLE_BUFFER_SIZE )
    {
    memset( ddt_to_vehicle_status, 0, BC_MOTOCON_DDT_STATUS_LENGTH );
    BC_MOTOCON_PRINTF( "%s, data overflow: %d > %d(limit)\r\n", __FUNCTION__, ddt_to_vehicle_data_size, BC_MOTOCON_DDT_TO_VEHICLE_BUFFER_SIZE );
    }
return ddt_to_vehicle_status;
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_insert_ddt_to_vehicle_data
*
* Handle ddt to vehicle data.
*
* @param bytes Pointer received data
*
* @return uint8_t*
* Return status is changed or NULL
*
*********************************************************************/
const uint8_t* bc_motocon_ddt_insert_ddt_to_vehicle_data
    (
    const uint8_t* bytes,
    const uint32_t length
    )
{
BC_MOTOCON_DDT_PRINTF( "%s, %d\r\n", __FUNCTION__, length );

const uint8_t  session_id = bytes[0];
const uint32_t data_position = THREE_BYTE_BIG( bytes, 1 );
const uint8_t* data = bytes + BC_MOTOCON_DDT_HEADER_SIZE;
const uint32_t data_length = length - BC_MOTOCON_DDT_HEADER_SIZE;

if( ddt_to_vehicle_status[0] == 0 )
    {
    BC_MOTOCON_PRINTF( "%s, session inactive\r\n", __FUNCTION__ );
    return NULL;
    }

if( ddt_to_vehicle_status[1] != session_id )
    {
    BC_MOTOCON_PRINTF( "%s, invalid session id, expect %d, received %d\r\n", __FUNCTION__, ddt_to_vehicle_status[1], session_id );
    return NULL;
    }

if( data_position + data_length > ddt_to_vehicle_data_size )
    {
    memset( ddt_to_vehicle_status, 0, BC_MOTOCON_DDT_STATUS_LENGTH );
    BC_MOTOCON_PRINTF( "%s, data overflow: %d + %d > %d(expect)\r\n", __FUNCTION__, data_position, data_length, ddt_to_vehicle_data_size );
    return ddt_to_vehicle_status;
    }

memcpy( ddt_to_vehicle_buffer + data_position, data, data_length );
if( data_position + data_length == ddt_to_vehicle_data_size )
    {
    bc_motocon_parser_ddt_to_vehicle_received( ddt_to_vehicle_buffer, ddt_to_vehicle_data_size );
    memset( ddt_to_vehicle_status, 0, BC_MOTOCON_DDT_STATUS_LENGTH );
    return ddt_to_vehicle_status;
    }
return NULL;
}

/*********************************************************************
*
* @private
* id_generator
*
* Get valid id.
*
* @return uint8_t
* Ddt to phone id
*
*********************************************************************/
static uint8_t id_generator
    (
    void
    )
{
ddt_to_phone_id++;
if( ddt_to_phone_id == BC_MOTOCON_DDT_INACTIVE_ID )
    {
    ddt_to_phone_id = 1;
    }
return ddt_to_phone_id;
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_send_ddt_to_phone_data
*
* Send protobuf data by ddt to phone protocol. (include ddt vehicle information & ddt can)
* Input arguments are protobuf's parameters.
*
* @param command         MotoConSDK's command code
* @param bytes           Bytes of protobuf
* @param length          Size of protobuf
* @param result_callback Function pointer of result callback
*
* @return bc_motocon_send_result_t
* Result of send command
*
*********************************************************************/
bc_motocon_send_result_t bc_motocon_ddt_send_ddt_to_phone_data
    (
    const bc_motocon_command_code_t command,
    const uint8_t* bytes,
    const uint32_t length,
    void ( *result_callback ) ( const bc_motocon_send_result_t )
    )
{
BC_MOTOCON_DDT_PRINTF( "%s, command_code: %d, length: %d\r\n", __FUNCTION__, command, length );
// find channel
bc_motocon_ddt_to_phone_t* ddt = &ddt_to_phone;
switch( command )
    {
    case BC_MOTOCON_COMMAND_CODE_VEHICLE_INFORMATION_RESPONSE:
        ddt = &ddt_vehicle_information;
        break;

    case BC_MOTOCON_COMMAND_CODE_CAN_RESPONSE:
        ddt = &ddt_can;
        break;

    default:
        break;
    }
// check state
if( ddt->id != BC_MOTOCON_DDT_INACTIVE_ID )
    {
    if( result_callback != NULL )
        {
        result_callback( BC_MOTOCON_SEND_RESULT_DDT_BUSY );
        }
    return BC_MOTOCON_SEND_RESULT_DDT_BUSY;
    }
// start ddt
ddt->id = id_generator();
ddt->result_callback = result_callback;

ddt->remain_header = BC_MOTOCON_PROTOBUF_HEADER_SIZE;
ddt->header[0] = command >> 8;
ddt->header[1] = command & 0xFF;
ddt->header[2] = ( length >> 16 ) & 0xFF;
ddt->header[3] = ( length >> 8 ) & 0xFF;
ddt->header[4] = length & 0xFF;

ddt->remain_content = length;
ddt->content = bytes;

ddt->total_length = length + BC_MOTOCON_PROTOBUF_HEADER_SIZE;
ddt->send_point = 0;

uint8_t send_data[BC_MOTOCON_DDT_HEADER_SIZE];
send_data[0] = ddt->id;
send_data[1] = ( ddt->total_length >> 16 ) & 0xFF;
send_data[2] = ( ddt->total_length >> 8 ) & 0xFF;
send_data[3] = ddt->total_length & 0xFF;

bc_motocon_send_result_t ret = bc_motocon_send_data( ddt->control_type, send_data, BC_MOTOCON_DDT_HEADER_SIZE );
if( ret == BC_MOTOCON_SEND_RESULT_SUCCESS )
    {
    BaseType_t result = xTimerStart( ddt->timer, 0 );
    configASSERT( result == pdPASS );
    }
else
    {
    ddt->id = BC_MOTOCON_DDT_INACTIVE_ID;
    if( ddt->result_callback != NULL )
        {
        ddt->result_callback( ret );
        }
    }
return ret;
}

/*********************************************************************
*
* @private
* bc_motocon_ddt_received_ddt_to_phone_ack
*
* Get ack from phone and send the next package.
*
* @param type Type of ddt
*
*********************************************************************/
void bc_motocon_ddt_received_ddt_to_phone_ack
    (
    const bc_motocon_ddt_type_t type
    )
{
bc_motocon_ddt_to_phone_t* ddt;
switch( type )
    {
    case BC_MOTOCON_DDT_TO_PHONE:
        ddt = &ddt_to_phone;
        break;

    case BC_MOTOCON_DDT_VEHICLE_INFORMATION:
        ddt = &ddt_vehicle_information;
        break;

    case BC_MOTOCON_DDT_CAN:
        ddt = &ddt_can;
        break;

    default:
        BC_MOTOCON_PRINTF( "%s, invalid ddt to phone type: %d\r\n", __FUNCTION__, type );
        return;
        break;
    }
BaseType_t result = xTimerStop( ddt->timer, 0 );
configASSERT( result == pdPASS );
if( pdTRUE == xSemaphoreTake( ddt->semaphore, DDT_TO_PHONE_SEMAPHORE_TIMEOUT_TICKS ) )
    {
    if( ddt->id == BC_MOTOCON_DDT_INACTIVE_ID )
        {
        BC_MOTOCON_PRINTF( "%s, ddt to phone(%d) inactive, drop ack\r\n", __FUNCTION__, type );
        xSemaphoreGive( ddt->semaphore );
        return;
        }

    if( ( ddt->remain_header + ddt->remain_content ) > 0 )
        {
        ddt->send_length = 0;
        ddt->total_send_length = 0;

        uint8_t send_data[BC_MOTOCON_DDT_TO_PHONE_TOTAL_PACKAGE_SIZE];
        send_data[0] = ddt->id;
        send_data[1] = ( ddt->send_point >> 16 ) & 0xFF;
        send_data[2] = ( ddt->send_point >> 8 ) & 0xFF;
        send_data[3] = ddt->send_point & 0xFF;
        if( ddt->remain_header > 0 )
            {
            ddt->send_length = MIN( ddt->remain_header, BC_MOTOCON_DDT_TO_PHONE_CONTENT_SIZE );
            memcpy( &send_data[BC_MOTOCON_DDT_HEADER_SIZE], ddt->header + ddt->send_point, ddt->send_length );
            ddt->remain_header -= ddt->send_length;
            ddt->send_point += ddt->send_length;
            ddt->total_send_length += ddt->send_length;
            }
        if( ddt->remain_content > 0 && ddt->total_send_length < BC_MOTOCON_DDT_TO_PHONE_CONTENT_SIZE )
            {
            ddt->send_length = MIN( ddt->remain_content, BC_MOTOCON_DDT_TO_PHONE_CONTENT_SIZE - ddt->total_send_length );
            memcpy( &send_data[BC_MOTOCON_DDT_HEADER_SIZE + ddt->total_send_length], ddt->content + ddt->send_point - BC_MOTOCON_PROTOBUF_HEADER_SIZE, ddt->send_length );
            ddt->remain_content -= ddt->send_length;
            ddt->send_point += ddt->send_length;
            ddt->total_send_length += ddt->send_length;
            }
        bc_motocon_send_result_t ret = bc_motocon_send_data( ddt->data_type, send_data, BC_MOTOCON_DDT_HEADER_SIZE + ddt->total_send_length );
        if( ret == BC_MOTOCON_SEND_RESULT_SUCCESS )
            {
            BaseType_t result = xTimerStart( ddt->timer, 0 );
            configASSERT( result == pdPASS );
            }
        else
            {
            ddt->id = BC_MOTOCON_DDT_INACTIVE_ID;
            if( ddt->result_callback != NULL )
                {
                ddt->result_callback( ret );
                }
            }
        }
    else
        {
        ddt->id = BC_MOTOCON_DDT_INACTIVE_ID;
        if( ddt->result_callback != NULL )
            {
            ddt->result_callback( BC_MOTOCON_SEND_RESULT_DDT_COMPLETE );
            }
        }
    xSemaphoreGive( ddt->semaphore );
    }
else
    {
    BC_MOTOCON_PRINTF( "%s, ddt to phone(%d) semaphore timeout, drop ack\r\n", __FUNCTION__, type );
    }
}

/*********************************************************************
*
* @private
* ddt_to_phone_timeout
*
* Post timeout callback
*
* @param timer_handle Timer handle
*
*********************************************************************/
static void ddt_to_phone_timeout
    (
    TimerHandle_t timer_handle
    )
{
BC_MOTOCON_PRINTF( "%s\r\n", __FUNCTION__ );
BaseType_t result = xTimerStop( timer_handle, 0 );
configASSERT( result == pdPASS );
bc_motocon_ddt_to_phone_t* ddt = ( bc_motocon_ddt_to_phone_t* ) pvTimerGetTimerID( timer_handle );
if( ddt != NULL && pdTRUE == xSemaphoreTake( ddt->semaphore, DDT_TO_PHONE_SEMAPHORE_TIMEOUT_TICKS ) )
    {
    if( ddt->id != BC_MOTOCON_DDT_INACTIVE_ID )
        {
        ddt->id = BC_MOTOCON_DDT_INACTIVE_ID;
        if( ddt->result_callback != NULL )
            {
            ddt->result_callback( BC_MOTOCON_SEND_RESULT_DDT_TIMEOUT );
            }
        }
    xSemaphoreGive( ddt->semaphore );
    }
}
