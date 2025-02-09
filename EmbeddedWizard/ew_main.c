/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software
* components. It is provided as an example software which is intended to be
* modified and extended according to particular requirements.
*
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability
* and non-infringement of any third party IPR or other rights which may result
* from the use or the inability to use the software.
*
********************************************************************************
*
* DESCRIPTION:
*   This file implements a generic framework for running Embedded Wizard
*   generated GUI applications on a dedicated target with or without the usage
*   of an operating system.
*   The module ewmain contains three major functions that are used within
*   every Embedded Wizard GUI application: EwInit() - EwProcess() - EwDone().
*   These functions represent the lifecycle of the entire GUI application.
*
*   EwInit() is responsible to initialize the system, to configure the display,
*   to get access to the desired input devices (like keyboard or touch),
*   to initialize the Embedded Wizard Runtime Environment / Graphics Engine,
*   to create an instance of the application class and to initialize all
*   needed peripheral components.
*
*   EwProcess() implements one cycle of the main loop. This function has to be
*   called in an (endless) loop and contains typically the following steps:
*   1. Processing data from your device driver(s)
*   2. Processing key events
*   3. Processing cursor or touch screen events
*   4. Processing timers
*   5. Processing signals
*   6. Updating the screen
*   7. Triggering the garbage collection
*
*   EwDone() is responsible to shutdown the application and to release all
*   used resources.
*
*   Important: Please be aware that every Embedded Wizard GUI application
*   requires the execution in a single GUI task!
*   If you are working with an operating system and your software is using
*   several threads/tasks, please take care to access your GUI application
*   only within the context of your GUI thread/task. Use operating system
*   services to exchange data or events between the GUI thread/task and other
*   worker threads/tasks.
*
*   In order to keep this framework independent from the particular GUI
*   application, the application class and the screen size are taken from the
*   generated code. In this manner, it is not necessary to modify this file
*   when creating new GUI applications. Just set the attributes 'ScreenSize'
*   and 'ApplicationClass' of the profile in the Embedded Wizard IDE.
*
*   For more information concerning the integration of an Embedded Wizard
*   generated GUI application into your main application, please see
*   https://doc.embedded-wizard.de/main-loop
*
*******************************************************************************/

#include "ewconfig.h"
#include "ew_main.h"
#include "Core.h"
#include "Graphics.h"

#include "ew_bsp_clock.h"
#include "ew_bsp_event.h"
#include "ew_bsp_display.h"
#include "ew_priv.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "fsl_common.h"
#include "FRTOS_pub.h"
#include "GRM_pub_prj.h"
#include "PM_pub.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define EW_TASK_PRIORITY   ( TASK_PRIO_EMBEDDED_WIZARD )
#define EW_TASK_STACK_SIZE ( 2048 )
#define EW_TASK_NAME       "ew_task"

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

/* memory pool */
#ifdef EW_MEMORY_POOL_SECTION
    EW_MEMORY_POOL_SECTION static unsigned long EwMemory[ EW_MEMORY_POOL_SIZE / sizeof( unsigned long )];
    #define EW_MEMORY_POOL_ADDR EwMemory
#endif

/* optional second memory pool */
#ifdef EW_EXTRA_POOL_SECTION
    EW_EXTRA_POOL_SECTION static unsigned long EwExtraMemory[ EW_EXTRA_POOL_SIZE / sizeof( unsigned long )];
    #define EW_EXTRA_POOL_ADDR EwExtraMemory
#else
    AT_BOARDSDRAM_SECTION( uint8_t EW_MEMORY_POOL_ADDR[EW_MEMORY_POOL_SIZE] );
#endif

static CoreRoot     RootObject;
static XViewport*   Viewport;
static XDisplayInfo DisplayInfo;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/
#define CHECK_HANDLE( handle ) \
  if ( !handle )               \
  {                            \
    EwPrint( "[failed]\n" );   \
    return 0;                  \
  }                            \
  else                         \
    EwPrint( "[OK]\n" );

/* helper functions used within this module */
static void EwUpdate( XViewport* aViewport, CoreRoot aApplication );

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/
static void task_main( void * arg );

/*******************************************************************************
* FUNCTION:
*   EwInit
*
* DESCRIPTION:
*   EwInit() is responsible to initialize the system, to configure the display,
*   to get access to the desired input devices (like keyboard or touch),
*   to initialize the Embedded Wizard Runtime Environment / Graphics Engine,
*   to create an instance of the application class and to initialize all
*   needed peripheral components.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   1 if successful, 0 otherwise.
*
*******************************************************************************/
int EwInit( void )
{
  /* initalize system clocks */
  EwBspClockInit();

  /* set RTC, if current RTC time is before the minimum time */
  if ( EwBspClockGetTime() < RTC_MINIMUM_TIME )
    EwBspClockSetTime( RTC_DEFAULT_TIME );

  /* initialize display */
  EwPrint( "Initialize Display...                        " );
  CHECK_HANDLE( EwBspDisplayInit( EwScreenSize.X, EwScreenSize.Y, &DisplayInfo ));

  #if EW_MEMORY_POOL_SIZE > 0
    /* initialize heap manager */
    EwPrint( "Initialize Memory Manager...                 " );
    EwInitHeap( 0 );
    EwAddHeapMemoryPool( (void*)EW_MEMORY_POOL_ADDR, EW_MEMORY_POOL_SIZE );

    #if EW_EXTRA_POOL_SIZE > 0
      EwAddHeapMemoryPool( (void*)EW_EXTRA_POOL_ADDR, EW_EXTRA_POOL_SIZE );
    #endif

    EwPrint( "[OK]\n" );
  #endif

  /* initialize the Graphics Engine and Runtime Environment */
  EwPrint( "Initialize Graphics Engine...                " );
  CHECK_HANDLE( EwInitGraphicsEngine( 0 ));

  /* create the applications root object ... */
  EwPrint( "Create Embedded Wizard Root Object...        " );
  RootObject = (CoreRoot)EwNewObjectIndirect( EwApplicationClass, 0 );
  CHECK_HANDLE( RootObject );

  EwLockObject( RootObject );
  CoreRoot__Initialize( RootObject, EwScreenSize );

  /* create Embedded Wizard viewport object to provide uniform access to the framebuffer */
  EwPrint( "Create Embedded Wizard Viewport...           " );
  Viewport = EwInitViewport( EwScreenSize, EwNewRect( 0, 0, DisplayInfo.BufferWidth, DisplayInfo.BufferHeight ),
    0, 255, DisplayInfo.FrameBuffer, DisplayInfo.DoubleBuffer, 0, 0 );
  CHECK_HANDLE( Viewport );

  /* initialize your device driver(s) that provide data for your GUI */
  ew_device_interface_init();

  ew_power_init();

  return 1;
}

/*******************************************************************************
* FUNCTION:
*   EwDone
*
* DESCRIPTION:
*   EwDone() is responsible to shutdown the application and to release all
*   used resources.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwDone( void )
{
  /* deinitialize your device driver(s) */
  ew_device_interface_deinit();

  /* destroy the applications root object and release unused resources and memory */
  EwPrint( "Shutting down Application...                 " );
  EwDoneViewport( Viewport );
  EwUnlockObject( RootObject );
  EwReclaimMemory();
  EwPrint( "[OK]\n" );

  /* deinitialize the Graphics Engine */
  EwPrint( "Deinitialize Graphics Engine...              " );
  EwDoneGraphicsEngine();
  EwPrint( "[OK]\n" );

  #if EW_MEMORY_POOL_SIZE > 0
  /* deinitialize heap manager */
  EwDoneHeap();
  #endif

  /* deinitialize display */
  EwBspDisplayDone( &DisplayInfo );

  Viewport   = 0;
  RootObject = 0;

  EW_power_update_ignoff_task_status( IGN_OFF_TASK_DISPLAY_OFF );
}

/*******************************************************************************
* FUNCTION:
*   EwProcess
*
* DESCRIPTION:
*   EwProcess() implements one cycle of the main loop. This function has to be
*   called in an (endless) loop and contains typically the following steps:
*   1. Processing data from your device driver(s)
*   2. Processing key events
*   3. Processing cursor or touch screen events
*   4. Processing timers
*   5. Processing signals
*   6. Updating the screen
*   7. Triggering the garbage collection
*   For more information concerning the integration of an Embedded Wizard
*   generated GUI application into your main application, please see
*   https://doc.embedded-wizard.de/main-loop
*
* ARGUMENTS:
*   None.
*
* RETURN VALUE:
*   1, if further processing is needed, 0 otherwise.
*
*******************************************************************************/
int EwProcess( void )
{
int     timers  = 0;
int     signals = 0;
int     events  = 0;
int     devices = 0;
int     keep_processing = 1;
ew_key_event key_event;

/* process data of your device driver(s) and update the GUI
   application by setting properties or by triggering events */
devices = ew_device_interface_process();

key_event = ew_get_key_event();
if( CoreKeyCodeNoKey != key_event.code )
    {
    switch( key_event.state )
        {
        case KEY_STATE_PRESS:
            events |= CoreRoot__DriveKeyboardHitting( RootObject, key_event.code, 0, 1 );
            break;
        case KEY_STATE_RELEASE:
            events |= CoreRoot__DriveKeyboardHitting( RootObject, key_event.code, 0, 0 );
            break;
        default:
            EwPrint( "undefined key state: %d\r\n", key_event.state );
            break;
        }
    }

/* process expired timers */
timers = EwProcessTimers();

/* process the pending signals */
signals = EwProcessSignals();

/* refresh the screen, if something has changed and draw its content */
if( devices || timers || signals || events )
    {
    if( CoreRoot__DoesNeedUpdate( RootObject ) )
        {
        EwUpdate( Viewport, RootObject );
        }

    /* just for debugging purposes: check the memory structure */
    EwVerifyHeap();

    /* after each processed message start the garbage collection */
    EwReclaimMemory();

    /* print current memory statistic to console interface */
    #ifdef EW_PRINT_MEMORY_USAGE
        EwPrintProfilerStatistic( 0 );
    #endif

    /* evaluate memory pools and print report */
    #ifdef EW_DUMP_HEAP
        EwDumpHeap( 0 );
    #endif
    }
else
    {
    /* otherwise sleep/suspend the UI application until a certain event occurs or a timer expires... */
    EwBspEventWait( EwNextTimerExpiration() );
    }

return keep_processing;
}

/*******************************************************************************
* FUNCTION:
*   EwUpdate
*
* DESCRIPTION:
*   The function EwUpdate performs the screen update of the dirty area.
*
* ARGUMENTS:
*   aViewPort    - Viewport used for the screen update.
*   aApplication - Root object used for the screen update.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
static void EwUpdate( XViewport* aViewport, CoreRoot aApplication )
{
  XBitmap*       bitmap;
  GraphicsCanvas canvas     = EwNewObject( GraphicsCanvas, 0 );
  XRect          updateRect = {{ 0, 0 }, { 0, 0 }};

  if ( !canvas )
    return;

  if ( DisplayInfo.UpdateMode == EW_BSP_DISPLAY_UPDATE_NORMAL )
  {
    bitmap = EwBeginUpdate( aViewport );

    /* redraw the dirty area of the screen */
    if ( bitmap  )
    {
      GraphicsCanvas__AttachBitmap( canvas, (XHandle)bitmap );
      updateRect = CoreRoot__UpdateGE20( aApplication, canvas );
      GraphicsCanvas__DetachBitmap( canvas );
      EwEndUpdate( aViewport, updateRect );
    }
  }
  else
  {
    int regions = CoreRoot__BeginUpdate( aApplication );

    while ( regions-- )
    {
      /* get rectangular area of the update region for scratch-pad buffer */
      if ( DisplayInfo.UpdateMode == EW_BSP_DISPLAY_UPDATE_SCRATCHPAD )
        updateRect = CoreRoot__GetUpdateRegion( aApplication, regions );

      /* iterate through all update areas */
      while ( EwBspDisplayGetUpdateArea( &updateRect ))
      {
        /* update the current subarea */
        bitmap = EwBeginUpdateArea( aViewport, updateRect );
        GraphicsCanvas__AttachBitmap( canvas, (XHandle)bitmap );
        CoreRoot__UpdateCanvas( aApplication, canvas, updateRect.Point1 );
        GraphicsCanvas__DetachBitmap( canvas );
        EwEndUpdate( aViewport, updateRect );
      }

      if ( DisplayInfo.UpdateMode != EW_BSP_DISPLAY_UPDATE_SCRATCHPAD )
        break;
    }
    CoreRoot__EndUpdate( aApplication );
  }
}

/*******************************************************************************
* FUNCTION:
*   EwPrintSystemInfo
*
* DESCRIPTION:
*   This function prints system and configuration information - very helpful in
*   case of any support issues.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwPrintSystemInfo( void )
{
  EwPrint( "---------------------------------------------\n" );
  EwPrint( "Target system                                %s      \n", EW_PLATFORM_STRING );
  EwPrint( "Color format                                 %s      \n", EW_FRAME_BUFFER_COLOR_FORMAT_STRING );
  #if EW_MEMORY_POOL_SIZE > 0
  EwPrint( "MemoryPool address                           0x%08X  \n", EW_MEMORY_POOL_ADDR );
  EwPrint( "MemoryPool size                              %u bytes\n", EW_MEMORY_POOL_SIZE );
  #endif
  #if EW_EXTRA_POOL_SIZE > 0
  EwPrint( "ExtraPool address                            0x%08X  \n", EW_EXTRA_POOL_ADDR );
  EwPrint( "ExtraPool size                               %u bytes\n", EW_EXTRA_POOL_SIZE );
  #endif
  #if EW_USE_SCRATCHPAD_BUFFER == 1
  EwPrint( "Scratch-pad buffer address                   0x%08X  \n", DisplayInfo.FrameBuffer );
  EwPrint( "Scratch-pad buffer size                      %u pixel\n", DisplayInfo.BufferWidth * DisplayInfo.BufferHeight );
  #else
  EwPrint( "Framebuffer address                          0x%08X  \n", DisplayInfo.FrameBuffer );
  #endif
  #if EW_USE_DOUBLE_BUFFER == 1
  EwPrint( "Doublebuffer address                         0x%08X  \n", DisplayInfo.DoubleBuffer );
  #endif
  #if EW_USE_OFFSCREEN_BUFFER == 1
  EwPrint( "Off-screen buffer                            used    \n" );
  #endif
  EwPrint( "Display size                                 %u x %u \n", DisplayInfo.DisplayWidth, DisplayInfo.DisplayHeight );
  EwPrint( "Framebuffer size                             %u x %u \n", DisplayInfo.BufferWidth, DisplayInfo.BufferHeight );
  EwPrint( "EwScreenSize                                 %d x %d \n", EwScreenSize.X, EwScreenSize.Y );
  EwPrint( "Graphics accelerator                         %s      \n", GRAPHICS_ACCELERATOR_STRING );
  EwPrint( "Warp function support                        %s      \n", WARP_FUNCTION_SUPPORT_STRING );
  EwPrint( "Vector graphics support                      %s      \n", VECTOR_GRAPHICS_SUPPORT_STRING );
  EwPrint( "Bidirectional text support                   %s      \n", BIDI_TEXT_SUPPORT_STRING );
  EwPrint( "Gradients support                            %s      \n", GRADIENTS_SUPPORT_STRING );
  EwPrint( "Compression support                          %s      \n", COMPRESSION_SUPPORT_STRING );
  EwPrint( "Index8 bitmap resource format                %s      \n", INDEX8_SURFACE_SUPPORT_STRING );
  EwPrint( "RGB565 bitmap resource format                %s      \n", RGB565_SURFACE_SUPPORT_STRING );
  EwPrint( "Native bitmap resource format                %s      \n", NATIVE_SURFACE_SUPPORT_STRING );
  EwPrint( "Native destination bitmap support            %s      \n", NATIVE_DESTINATION_SURFACE_SUPPORT_STRING );
  EwPrint( "Operating system                             %s      \n", OPERATING_SYSTEM_STRING );
  EwPrint( "External Flash memory                        %s      \n", EXTERNAL_FLASH_STRING );
  #ifdef EW_BITMAP_PIXEL_SECTION_NAME
  EwPrint( "Linker section for bitmap pixel              %s      \n", EW_STRINGIZE( EW_BITMAP_PIXEL_SECTION_NAME ));
  #endif
  #ifdef EW_FONT_PIXEL_SECTION_NAME
  EwPrint( "Linker section for font pixel                %s      \n", EW_STRINGIZE( EW_FONT_PIXEL_SECTION_NAME ));
  #endif
  #ifdef EW_FONT_DATA_SECTION_NAME
  EwPrint( "Linker section for font metrics              %s      \n", EW_STRINGIZE( EW_FONT_DATA_SECTION_NAME ));
  #endif
  #ifdef EW_CONST_STRING_SECTION_NAME
  EwPrint( "Linker section for string constants          %s      \n", EW_STRINGIZE( EW_CONST_STRING_SECTION_NAME ));
  #endif
  EwPrint( "Toolchain                                    %s      \n", TOOLCHAIN_STRING );
  #ifdef COMPILER_VERSION_STRING
  EwPrint( "C-Compiler version                           %s      \n", COMPILER_VERSION_STRING );
  #endif
  EwPrint( "Build date and time                          %s, %s  \n", __DATE__, __TIME__ );
  EwPrint( "Runtime Environment (RTE) version            %u.%02u \n", EW_RTE_VERSION >> 16, EW_RTE_VERSION & 0xFF );
  EwPrint( "Graphics Engine (GFX) version                %u.%02u \n", EW_GFX_VERSION >> 16, EW_GFX_VERSION & 0xFF );
  EwPrint( "Max surface cache size                       %u bytes\n", EW_MAX_SURFACE_CACHE_SIZE );
  EwPrint( "Glyph cache size                             %u x %u \n", EW_MAX_GLYPH_SURFACE_WIDTH, EW_MAX_GLYPH_SURFACE_HEIGHT );
  EwPrint( "Max issue tasks                              %u      \n", EW_MAX_ISSUE_TASKS );
  EwPrint( "Surface rotation                             %u      \n", EW_SURFACE_ROTATION );
  EwPrint( "---------------------------------------------\n" );
}
/* msy, mli */

/*******************************************************************************
*
* @private
* task_main
*
* EW module - task process
*
* @param arg not used
*
*******************************************************************************/
static void task_main
    (
    void* arg
    )
{
if( EwInit() == 0 )
    {
    return;
    }

EwPrintSystemInfo();

while( EwProcess() )
    {
    /* no body */
    }

EwDone();
vTaskDelete( NULL );
}

/*********************************************************************
*
* @private
* create_task
*
* EW module - create task that drives the Embedded Wizard GUI application
*
*********************************************************************/
static void create_task
    (
    void
    )
{
TaskHandle_t task_handle;

EwPrint( "Create ew task...                            " );
if( pdPASS == xTaskCreate( task_main, EW_TASK_NAME, EW_TASK_STACK_SIZE, NULL, EW_TASK_PRIORITY, &task_handle ) )
    {
    EwBspEventSetTaskHandle( task_handle );
    EwPrint( "[OK]\n" );
    }
else
    {
    EwPrint( "[FAIL]\n" );
    }
}

/*********************************************************************
*
* @public
* EW_init
*
* EW module - init
*
*********************************************************************/
void EW_init
    (
    void
    )
{
ew_device_bt_create_queue();
create_task();
ew_key_init();
ew_system_int();
}

