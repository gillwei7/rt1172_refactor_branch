/*********************************************************************
* @file
* ew_key.c
*
* @brief
* EW module - Receive key events from Vehicle Information Module and
*             send to Embedded Wizard
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "ewrte.h"
#include "ew_bsp_event.h"
#include "EW_pub.h"
#include "EW_priv.h"
#include "Core.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define QUEUE_LENGTH    ( 10 )

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/
static QueueHandle_t queue_key_events;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
* @private
* ew_get_key_event
*
* Get key event from queue
* @retval ew_key_event
*
*********************************************************************/
ew_key_event ew_get_key_event
    (
    void
    )
{
ew_key_event key_event = {CoreKeyCodeNoKey, KEY_STATE_RELEASE};
xQueueReceive( queue_key_events, &key_event, 0 );
return key_event;
}

/*********************************************************************
*
* @public
* EW_send_key_event
*
* Send key event to queue and wake up the embedded wizard task
*
* @param code CoreKeyCode code
* @param state key_state
*
*********************************************************************/
void EW_send_key_event
    (
    const CoreKeyCode code,
    const key_state   state
    )
{
ew_key_event key_event = {code, state};
if( pdTRUE == xQueueSend( queue_key_events, &key_event, 0 ) )
    {
    EwBspEventTrigger();
    }
else
    {
    EwPrint( "%s err\r\n", __FUNCTION__ );
    }
}

/*********************************************************************
*
* @private
* ew_key_init
*
* Create the queue to keep the key events
*
*********************************************************************/
void ew_key_init
    (
    void
    )
{
queue_key_events = xQueueCreate( QUEUE_LENGTH, sizeof( ew_key_event ) );
configASSERT( NULL != queue_key_events );
}
