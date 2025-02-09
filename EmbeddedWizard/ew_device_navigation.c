/*********************************************************************
* @file
* ew_device_navigation.c
*
* @brief
* EW module - Navigation related device interface implementation
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "ewrte.h"
#include "ew_bsp_inout.h"
#include "ew_bsp_clock.h"
#include "ew_bsp_event.h"
#include "ew_priv.h"
#include "DeviceInterface.h"
#include <string.h>
#include <stdbool.h>
#include "JPEG_pub.h"
#include "TEST_pub.h"
#include "NAVI_pub.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#ifdef _DeviceInterfaceNavigationDeviceClass_
    typedef int device_function( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyMapUpdate_
    static int ew_notify_navi_map_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyCurRdUpdate_
    static int ew_notify_cur_rd_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyETAUpdate_
    static int ew_notify_eta_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDayNightModeUpdate_
    static int ew_notify_daynight_mode_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifySpeedLimitUpdate_
    static int ew_notify_speed_limit_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviAlertUpdate_
    static int ew_notify_navi_alert_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNavigatingStatusUpdate_
    static int ew_notify_navi_navigating_status_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyRouteCalProgressUpdate_
    static int ew_notify_navi_route_cal_progress_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyZoomLevelUpdate_
    static int ew_notify_navi_zoom_level_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDialogEventUpdate_
    static int ew_notify_navi_dialog_event_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyTbtListUpdate_
    static int ew_notify_navi_tbt_list_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyViaPointUpdate_
    static int ew_notify_via_point_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviConnectUpdate_
    static int ew_notify_connect_status_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviDisconnectUpdate_
    static int ew_notify_disconnect_status_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyAlertDistanceUpdate_
    static int ew_notify_navi_alert_dist_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyPoiListUpdate_
    static int ew_notify_navi_poi_list_update( void );
#endif

#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyBtThroughputStatusUpdate_
    static int ew_notify_navi_bt_throughput_status_update( void );
#endif

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
#ifdef _DeviceInterfaceNavigationDeviceClass_
    static DeviceInterfaceNavigationDeviceClass device_object = 0;
    device_function* const navi_function_lookup_table[] =
        {
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyMapUpdate_
            ew_notify_navi_map_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyCurRdUpdate_
            ew_notify_cur_rd_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyETAUpdate_
            ew_notify_eta_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDayNightModeUpdate_
            ew_notify_daynight_mode_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifySpeedLimitUpdate_
            ew_notify_speed_limit_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviAlertUpdate_
            ew_notify_navi_alert_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNavigatingStatusUpdate_
            ew_notify_navi_navigating_status_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyRouteCalProgressUpdate_
            ew_notify_navi_route_cal_progress_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyZoomLevelUpdate_
            ew_notify_navi_zoom_level_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDialogEventUpdate_
            ew_notify_navi_dialog_event_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyViaPointUpdate_
            ew_notify_via_point_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyTbtListUpdate_
            ew_notify_navi_tbt_list_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviConnectUpdate_
            ew_notify_connect_status_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviDisconnectUpdate_
            ew_notify_disconnect_status_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyAlertDistanceUpdate_
            ew_notify_navi_alert_dist_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyPoiListUpdate_
            ew_notify_navi_poi_list_update,
        #endif
        #ifdef _DeviceInterfaceNavigationDeviceClass__NotifyBtThroughputStatusUpdate_
            ew_notify_navi_bt_throughput_status_update
        #endif
        };
    const int num_of_navi_func = sizeof( navi_function_lookup_table )/sizeof( device_function* );
    static int is_map_update = 0;
    static int is_cur_rd_update = 0;
    static int is_eta_update = 0;
    static int is_daynight_mode_update = 0;
    static int is_speed_limit_update = 0;
    static int is_navi_alert_update = 0;
    static int is_navigating_status_update = 0;
    static int is_tbt_list_update = 0;
    static int is_route_cal_progress_update = 0;
    static int is_zoom_level_update = 0;
    static int is_dialog_event_update = 0;
    static int is_via_point_update = 0;
    static int is_navi_app_connected = 0;
    static int is_navi_app_disconnected = 0;
    static int is_alert_distance_update = 0;
    static int is_poi_list_update = 0;
    static int is_bt_throughput_status_update = 0;

#endif
/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
* @private
* ew_device_navi_init
*
* Embedded Wizard navigation device interface initialization
*
*********************************************************************/
void ew_device_navi_init
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
     /*
       Get access to the counterpart of this device driver: get access to the
       device class that is created as autoobject within your Embedded Wizard
       project. For this purpose you can call the function EwGetAutoObject().
       This function contains two paramters: The pointer to the autoobject and
       the class of the autoobject.
       Assuming you have implemented the class 'DeviceClass' within the unit
       'Application' and you have an autoobject with the name 'Device', make
       the following call:
       EwGetAutoObject( &ApplicationDevice, ApplicationDeviceClass );
    */
    device_object = EwGetAutoObject( &DeviceInterfaceNavigationDevice, DeviceInterfaceNavigationDeviceClass );
    /*
       Once you have the access to the autoobject, lock it as long as you need
       the access (typically, until your device driver is closed). By locking
       the autoobject, you can ensure that the object of the device class will
       be kept within the memory and not freed by the Garbage Collector.
       Once the device class is locked, you can easily store it within a static
       variable to access the driver class during the runtime.
    */
    EwLockObject( device_object );
#endif
}

/*********************************************************************
*
* @private
* ew_device_navi_deinit
*
* Embedded Wizard navigation device interface de-initialization
*
*********************************************************************/
void ew_device_navi_deinit
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    if( device_object )
        {
        EwUnlockObject( device_object );
        }
    device_object = 0;
#endif
}

/*********************************************************************
*
* @private
* ew_device_navi_proc
*
* Select the function from navi function table and execute it.
*
*********************************************************************/
int ew_device_navi_proc
    (
    void
    )
{
int need_update = 0;

#ifdef _DeviceInterfaceNavigationDeviceClass_
    if( device_object == 0 ||
        num_of_navi_func == 0 )
        {
        return 0;
        }

    for( int i = 0; i < num_of_navi_func; i++ )
        {
        if( navi_function_lookup_table[i]() )
            {
            need_update = 1;
            }
        }
#endif

return need_update;
}

/*********************************************************************
*
* @private
* ew_navi_is_map_frame_ready
*
* Check if the map frame of RGB format is ready.
*
* @return True if the map frame is ready in the RGB buffer.
*
*********************************************************************/
bool ew_navi_is_map_frame_ready
    (
    void
    )
{
return JPEG_is_rgb_ready();
}

/*********************************************************************
*
* @private
* ew_notify_navi_map_update
*
* Notify EW GUI that map has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyMapUpdate_
    static int ew_notify_navi_map_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_map_update )
        {
        is_map_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyMapUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_cur_rd_update
*
* Notify EW GUI that current road has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyCurRdUpdate_
    static int ew_notify_cur_rd_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_cur_rd_update )
        {
        is_cur_rd_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyCurRdUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_eta_update
*
* Notify EW GUI that ETA has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyETAUpdate_
    static int ew_notify_eta_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_eta_update )
        {
        is_eta_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyETAUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_daynight_mode_update
*
* Notify EW GUI that daynight mode has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDayNightModeUpdate_
    static int ew_notify_daynight_mode_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_daynight_mode_update )
        {
        is_daynight_mode_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyDayNightModeUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_speed_limit_update
*
* Notify EW GUI that speed limit has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifySpeedLimitUpdate_
    static int ew_notify_speed_limit_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_speed_limit_update )
        {
        is_speed_limit_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifySpeedLimitUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_alert_update
*
* Notify EW GUI that navi alert has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviAlertUpdate_
    static int ew_notify_navi_alert_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_navi_alert_update )
        {
        is_navi_alert_update = 0;
        DeviceInterfaceNavigationDeviceClass__NotifyNaviAlertUpdate( device_object );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_navigating_status_update
*
* Notify EW GUI that navigation status has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNavigatingStatusUpdate_
    static int ew_notify_navi_navigating_status_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_navigating_status_update )
        {
        is_navigating_status_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyNavigatingStatusUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_route_cal_progress_update
*
* Notify EW GUI that new route calculation progress has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyRouteCalProgressUpdate_
    static int ew_notify_navi_route_cal_progress_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_route_cal_progress_update )
        {
        is_route_cal_progress_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyRouteCalProgressUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_zoom_level_update
*
* Notify EW GUI that new zoom level has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyZoomLevelUpdate_
    static int ew_notify_navi_zoom_level_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_zoom_level_update )
        {
        is_zoom_level_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyZoomLevelUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_dialog_event_update
*
* Notify EW GUI that new dialog event has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyDialogEventUpdate_
    static int ew_notify_navi_dialog_event_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_dialog_event_update )
        {
        is_dialog_event_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyDialogEventUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_via_point_update
*
* Notify EW GUI that new dialog event has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyViaPointUpdate_
    static int ew_notify_via_point_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_via_point_update )
        {
        is_via_point_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyViaPointUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_tbt_list_update
*
* Notify EW GUI that tbt list has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyTbtListUpdate_
    static int ew_notify_navi_tbt_list_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_tbt_list_update )
        {
        is_tbt_list_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyTbtListUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_connect_status_update
*
* Notify EW GUI that navi app is connected.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviConnectUpdate_
    static int ew_notify_connect_status_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_navi_app_connected )
        {
        is_navi_app_connected = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyNaviConnectUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_disconnect_status_update
*
* Notify EW GUI that navi app is disconnected.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyNaviDisconnectUpdate_
    static int ew_notify_disconnect_status_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_navi_app_disconnected )
        {
        is_navi_app_disconnected = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyNaviDisconnectUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_alert_dist_update
*
* Notify EW GUI that new alert distance has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyAlertDistanceUpdate_
    static int ew_notify_navi_alert_dist_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_alert_distance_update )
        {
        is_alert_distance_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyAlertDistanceUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_poi_list_update
*
* Notify EW GUI that poi list has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyPoiListUpdate_
    static int ew_notify_navi_poi_list_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_poi_list_update )
        {
        is_poi_list_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyPoiListUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_navi_bt_throughput_status_update
*
* Notify EW GUI that new bt throughput status has received.
*
*********************************************************************/
#ifdef _DeviceInterfaceNavigationDeviceClass__NotifyBtThroughputStatusUpdate_
    static int ew_notify_navi_bt_throughput_status_update
        (
        void
        )
    {
    int need_update = 0;
    if( is_bt_throughput_status_update )
        {
        is_bt_throughput_status_update = 0;
        need_update = 1;
        DeviceInterfaceNavigationDeviceClass__NotifyBtThroughputStatusUpdate( device_object );
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @public
* EW_notify_navi_map_update
*
* Notify Embedded Wizard map frame of RGB format is ready.
*
*********************************************************************/
void EW_notify_navi_map_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_map_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_current_road_update
*
* Notify Embedded Wizard that the current road name is updated.
*
*********************************************************************/
void EW_notify_current_road_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_cur_rd_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_eta_update
*
* Notify Embedded Wizard that the ETA is updated.
*
*********************************************************************/
void EW_notify_eta_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_eta_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_daynight_mode_update
*
* Notify Embedded Wizard that the daynight mode is updated.
*
*********************************************************************/
void EW_notify_daynight_mode_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_daynight_mode_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_navigating_status_update
*
* Notify Embedded Wizard that the navigating status is updated.
*
*********************************************************************/
void EW_notify_navigating_status_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_navigating_status_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_speed_limit_update
*
* Notify Embedded Wizard that the speed limit is updated.
*
*********************************************************************/
void EW_notify_speed_limit_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_speed_limit_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_navi_alert_update
*
* Notify Embedded Wizard that the navigation alert is updated.
*
*********************************************************************/
void EW_notify_navi_alert_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_navi_alert_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_tbt_list_update
*
* Notify Embedded Wizard that the tbt list is updated.
*
*********************************************************************/
void EW_notify_tbt_list_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_tbt_list_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_route_cal_progress_update
*
* Notify Embedded Wizard that the route calculation progress is updated.
*
*********************************************************************/
void EW_notify_route_cal_progress_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_route_cal_progress_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_zoom_level_update
*
* Notify Embedded Wizard that zoom level is updated.
*
*********************************************************************/
void EW_notify_zoom_level_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_zoom_level_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_dialog_event_update
*
* Notify Embedded Wizard that dialog event is updated.
*
*********************************************************************/
void EW_notify_dialog_event_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_dialog_event_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_via_point_update
*
* Notify Embedded Wizard that number of via point is updated.
*
*********************************************************************/
void EW_notify_via_point_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_via_point_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_connect_status_update
*
* Notify Embedded Wizard that navi app is connected.
*
*********************************************************************/
void EW_notify_connect_status_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_navi_app_connected = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_disconnect_status_update
*
* Notify Embedded Wizard that navi app is disconnected.
*
*********************************************************************/
void EW_notify_disconnect_status_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_navi_app_disconnected = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_alert_distance_update
*
* Notify Embedded Wizard that alert distance is updated.
*
*********************************************************************/
void EW_notify_alert_distance_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_alert_distance_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_poi_list_update
*
* Notify Embedded Wizard that poi list is updated.
*
*********************************************************************/
void EW_notify_poi_list_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_poi_list_update = 1;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_bt_throughput_status_update
*
* Notify Embedded Wizard that bt throughput status is updated.
*
*********************************************************************/
void EW_notify_bt_throughput_status_update
    (
    void
    )
{
#ifdef _DeviceInterfaceNavigationDeviceClass_
    is_bt_throughput_status_update = 1;
    EwBspEventTrigger();
#endif
}