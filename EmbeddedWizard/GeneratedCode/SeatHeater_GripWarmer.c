/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* The template of this heading text can be found in the file 'head.ewt' in the
* directory 'Platforms' of your Embedded Wizard installation directory. If you
* wish to adapt this text, please copy the template file 'head.ewt' into your
* project directory and edit the copy only. Please avoid any modifications of
* the original template file!
*
* Version  : 11.00
* Profile  : iMX_RT
* Platform : NXP.iMX_RT_VGLite.RGBA8888
*
*******************************************************************************/

#include "ewlocale.h"
#include "_ComponentsBaseText.h"
#include "_CoreGroup.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreTimer.h"
#include "_CoreView.h"
#include "_DeviceInterfaceVehicleDataClass.h"
#include "_DeviceInterfaceVehicleDeviceClass.h"
#include "_MenuItemBaseValue.h"
#include "_MenuVerticalMenu.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction.h"
#include "_SeatHeater_GripWarmerSHT02_GPW02_Main.h"
#include "_SeatHeater_GripWarmerScaleIndicator.h"
#include "_ViewsImage.h"
#include "_ViewsRectangle.h"
#include "DeviceInterface.h"
#include "Enum.h"
#include "Fonts.h"
#include "Resource.h"
#include "SeatHeater_GripWarmer.h"
#include "Strings.h"
#include "Views.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x00000040, /* ratio 93.75 % */
  0xB8003D00, 0x000AA452, 0x00CA0037, 0x4E0003C0, 0x00630042, 0x064879D0, 0x76000800,
  0x9001A21E, 0x36002206, 0x019A2F0F, 0xC7A0E750, 0x98DF1D89, 0x65B2C004, 0x00000040,
  0x00000000
};

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 480, 272 }};
static const XRect _Const0001 = {{ 193, 39 }, { 395, 268 }};
static const XRect _Const0002 = {{ 230, 219 }, { 355, 238 }};
static const XRect _Const0003 = {{ 0, 0 }, { 0, 0 }};
static const XRect _Const0004 = {{ 0, 96 }, { 480, 206 }};
static const XRect _Const0005 = {{ 138, 130 }, { 469, 173 }};
static const XRect _Const0006 = {{ 0, 39 }, { 94, 114 }};
static const XRect _Const0007 = {{ 0, 189 }, { 94, 264 }};
static const XRect _Const0008 = {{ 13, 112 }, { 91, 190 }};
static const XStringRes _Const0009 = { _StringsDefault0, 0x0002 };

#ifndef EW_DONT_CHECK_INDEX
  /* This function is used to check the indices when accessing an array.
     If you don't want this verification add the define EW_DONT_CHECK_INDEX
     to your Makefile or project settings. */
  static int EwCheckIndex( int aIndex, int aRange, const char* aFile, int aLine )
  {
    if (( aIndex < 0 ) || ( aIndex >= aRange ))
    {
      EwPrint( "[FATAL ERROR in %s:%d] Array index %d out of bounds %d",
                aFile, aLine, aIndex, aRange );
      EwPanic();
    }
    return aIndex;
  }

  #define EwCheckIndex( aIndex, aRange ) \
    EwCheckIndex( aIndex, aRange, __FILE__, __LINE__ )
#else
  #define EwCheckIndex( aIndex, aRange ) aIndex
#endif

/* Initializer for the class 'SeatHeater_GripWarmer::SHT02_GPW02_Main' */
void SeatHeater_GripWarmerSHT02_GPW02_Main__Init( SeatHeater_GripWarmerSHT02_GPW02_Main _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  MenuBaseMenuView__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( SeatHeater_GripWarmerSHT02_GPW02_Main );

  /* ... then construct all embedded objects */
  CoreSystemEventHandler__Init( &_this->VehicleDataReceivedEventHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( SeatHeater_GripWarmerSHT02_GPW02_Main );

  /* ... and initialize objects, variables, properties, etc. */
  ComponentsBaseComponent__OnSetDDModeEnabled( _this, 1 );
  _this->Super2.SlideOutEffectEnabled = 1;
  ComponentsBaseComponent__OnSetDDModeEnabled( &_this->Super1.Menu, 1 );
  MenuVerticalMenu_OnSetNoOfItems( &_this->Super1.Menu, 3 );
  _this->ItemTitleArray[ 0 ] = EwShareString( EwGetVariantOfString( &StringsGEN_LOW ));
  _this->ItemTitleArray[ 1 ] = EwShareString( EwGetVariantOfString( &StringsGEN_MIDDLE ));
  _this->ItemTitleArray[ 2 ] = EwShareString( EwGetVariantOfString( &StringsGEN_HIGH ));
  _this->VehicleDataReceivedEventHandler.OnEvent = EwNewSlot( _this, SeatHeater_GripWarmerSHT02_GPW02_Main_OnVehicleDataReceivedSlot );
  CoreSystemEventHandler_OnSetEvent( &_this->VehicleDataReceivedEventHandler, &EwGetAutoObject( 
  &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->VehicleDataReceivedSystemEvent );

  /* Call the user defined constructor */
  SeatHeater_GripWarmerSHT02_GPW02_Main_Init( _this, aArg );
}

/* Re-Initializer for the class 'SeatHeater_GripWarmer::SHT02_GPW02_Main' */
void SeatHeater_GripWarmerSHT02_GPW02_Main__ReInit( SeatHeater_GripWarmerSHT02_GPW02_Main _this )
{
  /* At first re-initialize the super class ... */
  MenuBaseMenuView__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSystemEventHandler__ReInit( &_this->VehicleDataReceivedEventHandler );
}

/* Finalizer method for the class 'SeatHeater_GripWarmer::SHT02_GPW02_Main' */
void SeatHeater_GripWarmerSHT02_GPW02_Main__Done( SeatHeater_GripWarmerSHT02_GPW02_Main _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( MenuBaseMenuView );

  /* Finalize all embedded objects */
  CoreSystemEventHandler__Done( &_this->VehicleDataReceivedEventHandler );

  /* Don't forget to deinitialize the super class ... */
  MenuBaseMenuView__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void SeatHeater_GripWarmerSHT02_GPW02_Main_Init( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  _this->ScaleIndicator = EwNewObject( SeatHeater_GripWarmerScaleIndicator, 0 );

  switch ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction )
  {
    case EnumVehicleSupportedFunctionSEAT_HEATER :
    {
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeSEAT_HEATER_VALUE_LOW );
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeSEAT_HEATER_VALUE_MIDDLE );
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeSEAT_HEATER_VALUE_HIGH );
    }
    break;

    case EnumVehicleSupportedFunctionGRIP_WARMER :
    {
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeGRIP_WARMER_VALUE_LOW );
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeGRIP_WARMER_VALUE_MIDDLE );
      SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, EnumVehicleRxTypeGRIP_WARMER_VALUE_HIGH );
    }
    break;

    default :; 
  }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.LoadItemClass()' */
XClass SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemClass( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XInt32 aItemNo )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aItemNo );

  return EW_CLASS( MenuItemBaseValue );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.LoadItemTitle()' */
XString SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemTitle( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XInt32 aItemNo )
{
  XString title = 0;

  if ( aItemNo < 3 )
    title = _this->ItemTitleArray[ EwCheckIndex( aItemNo, 3 )];

  return title;
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.OnItemActivate()' */
void SeatHeater_GripWarmerSHT02_GPW02_Main_OnItemActivate( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XInt32 aItemNo, MenuItemBase aMenuItem )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aMenuItem );

  SeatHeater_GripWarmerScaleIndicator_OnSetLevelValue( _this->ScaleIndicator, (XInt32)_this->ItemValueArray[ 
  EwCheckIndex( aItemNo, 3 )]);
  _this->ItemIdx = aItemNo;

  switch ( aItemNo )
  {
    case 0 :
      if ( 1 == _this->ItemValidStatusArray[ 0 ])
      {
        SeatHeater_GripWarmerScaleIndicator_OnSetScaleIndicatorType( _this->ScaleIndicator, 
        EnumSeatHeaterGripWarmerLevelTypeLOW );
        DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
        DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeHEATER_LEVEL, 0 );
        CoreGroup_PresentDialog((CoreGroup)_this, ((CoreGroup)_this->ScaleIndicator ), 
        0, 0, 0, 0, 0, 0, EwNullSlot, EwNullSlot, 0 );
      }
    break;

    case 1 :
      if ( 1 == _this->ItemValidStatusArray[ 1 ])
      {
        SeatHeater_GripWarmerScaleIndicator_OnSetScaleIndicatorType( _this->ScaleIndicator, 
        EnumSeatHeaterGripWarmerLevelTypeMID );
        DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
        DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeHEATER_LEVEL, 1 );
        CoreGroup_PresentDialog((CoreGroup)_this, ((CoreGroup)_this->ScaleIndicator ), 
        0, 0, 0, 0, 0, 0, EwNullSlot, EwNullSlot, 0 );
      }
    break;

    case 2 :
      if ( 1 == _this->ItemValidStatusArray[ 2 ])
      {
        SeatHeater_GripWarmerScaleIndicator_OnSetScaleIndicatorType( _this->ScaleIndicator, 
        EnumSeatHeaterGripWarmerLevelTypeHIGH );
        DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
        DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeHEATER_LEVEL, 2 );
        CoreGroup_PresentDialog((CoreGroup)_this, ((CoreGroup)_this->ScaleIndicator ), 
        0, 0, 0, 0, 0, 0, EwNullSlot, EwNullSlot, 0 );
      }
    break;

    default :; 
  }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.LoadItemEnabled()' */
XBool SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemEnabled( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XInt32 aItemNo )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aItemNo );

  return (XBool)!DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( 
    EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ));
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.LoadItemBaseValue()' */
XString SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemBaseValue( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XInt32 aItemNo )
{
  XString val = 0;

  if ( aItemNo < 3 )
  {
    if ( 1 == _this->ItemValidStatusArray[ EwCheckIndex( aItemNo, 3 )])
      val = EwNewStringUInt( _this->ItemValueArray[ EwCheckIndex( aItemNo, 3 )], 
      0, 10 );
    else
      val = EwLoadString( &StringsGEN_THREE_HYPHENS );
  }

  return val;
}

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void SeatHeater_GripWarmerSHT02_GPW02_Main_OnVehicleDataReceivedSlot( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XObject sender )
{
  DeviceInterfaceVehicleDataClass VehicleData;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  VehicleData = EwCastObject( _this->VehicleDataReceivedEventHandler.Context, DeviceInterfaceVehicleDataClass );

  if ( VehicleData != 0 )
    switch ( VehicleData->RxType )
    {
      case EnumVehicleRxTypeSEAT_HEATER_VALUE_LOW :
      case EnumVehicleRxTypeSEAT_HEATER_VALUE_MIDDLE :
      case EnumVehicleRxTypeSEAT_HEATER_VALUE_HIGH :
        if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
            == EnumVehicleSupportedFunctionSEAT_HEATER )
          SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, VehicleData->RxType );
      break;

      case EnumVehicleRxTypeGRIP_WARMER_VALUE_LOW :
      case EnumVehicleRxTypeGRIP_WARMER_VALUE_MIDDLE :
      case EnumVehicleRxTypeGRIP_WARMER_VALUE_HIGH :
        if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
            == EnumVehicleSupportedFunctionGRIP_WARMER )
          SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( _this, VehicleData->RxType );
      break;

      case EnumVehicleRxTypeTIMEOUT_ERROR2_UPDATED :
        MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 0, _this->Super1.Menu.NoOfItems 
        - 1 );
      break;

      default :; 
    }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT02_GPW02_Main.UpdateLevel()' */
void SeatHeater_GripWarmerSHT02_GPW02_Main_UpdateLevel( SeatHeater_GripWarmerSHT02_GPW02_Main _this, 
  XEnum aNewType )
{
  DeviceInterfaceVehicleDataClass VehicleData;

  switch ( aNewType )
  {
    case EnumVehicleRxTypeSEAT_HEATER_VALUE_LOW :
    case EnumVehicleRxTypeGRIP_WARMER_VALUE_LOW :
    {
      if ( aNewType == EnumVehicleRxTypeSEAT_HEATER_VALUE_LOW )
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeSEAT_HEATER_VALUE_LOW );
      else
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeGRIP_WARMER_VALUE_LOW );

      if (((( VehicleData != 0 ) && VehicleData->Valid ) && ( 10 >= VehicleData->DataUInt32 )) 
          && ( VehicleData->DataUInt32 >= 1 ))
      {
        _this->ItemValidStatusArray[ 0 ] = 1;
        _this->ItemValueArray[ 0 ] = VehicleData->DataUInt32;

        if ( EnumSeatHeaterGripWarmerLevelTypeLOW == _this->ScaleIndicator->ScaleIndicatorType )
          SeatHeater_GripWarmerScaleIndicator_OnSetLevelValue( _this->ScaleIndicator, 
          (XInt32)VehicleData->DataUInt32 );

        MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 0, 0 );
      }
      else
        if ( !VehicleData->Valid )
        {
          _this->ItemValidStatusArray[ 0 ] = 0;
          MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 0, 0 );
        }
    }
    break;

    case EnumVehicleRxTypeSEAT_HEATER_VALUE_MIDDLE :
    case EnumVehicleRxTypeGRIP_WARMER_VALUE_MIDDLE :
    {
      if ( aNewType == EnumVehicleRxTypeSEAT_HEATER_VALUE_MIDDLE )
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeSEAT_HEATER_VALUE_MIDDLE );
      else
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeGRIP_WARMER_VALUE_MIDDLE );

      if (((( VehicleData != 0 ) && VehicleData->Valid ) && ( 10 >= VehicleData->DataUInt32 )) 
          && ( VehicleData->DataUInt32 >= 1 ))
      {
        _this->ItemValidStatusArray[ 1 ] = 1;
        _this->ItemValueArray[ 1 ] = VehicleData->DataUInt32;

        if ( EnumSeatHeaterGripWarmerLevelTypeMID == _this->ScaleIndicator->ScaleIndicatorType )
          SeatHeater_GripWarmerScaleIndicator_OnSetLevelValue( _this->ScaleIndicator, 
          (XInt32)VehicleData->DataUInt32 );

        MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 1, 1 );
      }
      else
        if ( !VehicleData->Valid )
        {
          _this->ItemValidStatusArray[ 1 ] = 0;
          MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 1, 1 );
        }
    }
    break;

    case EnumVehicleRxTypeSEAT_HEATER_VALUE_HIGH :
    case EnumVehicleRxTypeGRIP_WARMER_VALUE_HIGH :
    {
      if ( aNewType == EnumVehicleRxTypeSEAT_HEATER_VALUE_HIGH )
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeSEAT_HEATER_VALUE_HIGH );
      else
        VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeGRIP_WARMER_VALUE_HIGH );

      if (((( VehicleData != 0 ) && VehicleData->Valid ) && ( 10 >= VehicleData->DataUInt32 )) 
          && ( VehicleData->DataUInt32 >= 1 ))
      {
        _this->ItemValidStatusArray[ 2 ] = 1;
        _this->ItemValueArray[ 2 ] = VehicleData->DataUInt32;

        if ( EnumSeatHeaterGripWarmerLevelTypeHIGH == _this->ScaleIndicator->ScaleIndicatorType )
          SeatHeater_GripWarmerScaleIndicator_OnSetLevelValue( _this->ScaleIndicator, 
          (XInt32)VehicleData->DataUInt32 );

        MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 2, 2 );
      }
      else
        if ( !VehicleData->Valid )
        {
          _this->ItemValidStatusArray[ 2 ] = 0;
          MenuVerticalMenu_InvalidateItems( &_this->Super1.Menu, 2, 2 );
        }
    }
    break;

    default :; 
  }
}

/* Variants derived from the class : 'SeatHeater_GripWarmer::SHT02_GPW02_Main' */
EW_DEFINE_CLASS_VARIANTS( SeatHeater_GripWarmerSHT02_GPW02_Main )
EW_END_OF_CLASS_VARIANTS( SeatHeater_GripWarmerSHT02_GPW02_Main )

/* Virtual Method Table (VMT) for the class : 'SeatHeater_GripWarmer::SHT02_GPW02_Main' */
EW_DEFINE_CLASS( SeatHeater_GripWarmerSHT02_GPW02_Main, MenuBaseMenuView, ScaleIndicator, 
                 VehicleDataReceivedEventHandler, VehicleDataReceivedEventHandler, 
                 VehicleDataReceivedEventHandler, ItemTitleArray, ItemValueArray, 
                 "SeatHeater_GripWarmer::SHT02_GPW02_Main" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetBuffered,
  CoreGroup_OnGetEnabled,
  CoreGroup_OnSetEnabled,
  CoreGroup_OnSetOpacity,
  CoreGroup_OnSetVisible,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_GetViewAtIndex,
  CoreGroup_CountViews,
  CoreGroup_FindNextView,
  CoreGroup_FindSiblingView,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_Add,
  ComponentsBaseComponent_OnShortDownKeyActivated,
  ComponentsBaseComponent_OnShortUpKeyActivated,
  ComponentsBaseComponent_OnShortEnterKeyActivated,
  ComponentsBaseMainBG_OnShortHomeKeyActivated,
  ComponentsBaseComponent_OnLongDownKeyActivated,
  ComponentsBaseComponent_OnLongUpKeyActivated,
  ComponentsBaseComponent_OnLongEnterKeyActivated,
  ComponentsBaseComponent_OnLongHomeKeyActivated,
  ComponentsBaseComponent_OnShortMagicKeyActivated,
  MenuBaseMenuView_OnSetDDModeEnabled,
  ComponentsBaseComponent_OnDownKeyReleased,
  ComponentsBaseComponent_OnUpKeyReleased,
  SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemClass,
  SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemTitle,
  SeatHeater_GripWarmerSHT02_GPW02_Main_OnItemActivate,
  MenuBaseMenuView_LoadItemChecked,
  SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemEnabled,
  SeatHeater_GripWarmerSHT02_GPW02_Main_LoadItemBaseValue,
  MenuBaseMenuView_LoadItemMessage,
  MenuBaseMenuView_LoadItemReceivedTime,
  MenuBaseMenuView_LoadItemCategory,
  MenuBaseMenuView_LoadItemUid,
  MenuBaseMenuView_LoadItemToggle,
  MenuBaseMenuView_LoadItemUnit,
  MenuBaseMenuView_LoadItemValue,
  MenuBaseMenuView_OnItemLongEnterKeyActivate,
  MenuBaseMenuView_LoadItemHour,
  MenuBaseMenuView_LoadItemMinute,
  MenuBaseMenuView_LoadPoiListItemValue,
  MenuBaseMenuView_LoadPoiListItemUnit,
  MenuBaseMenuView_LoadItemIcon1Visible,
  MenuBaseMenuView_LoadItemIcon2Visible,
  MenuBaseMenuView_LoadItemDeviceAddress,
EW_END_OF_CLASS( SeatHeater_GripWarmerSHT02_GPW02_Main )

/* Initializer for the class 'SeatHeater_GripWarmer::ScaleIndicator' */
void SeatHeater_GripWarmerScaleIndicator__Init( SeatHeater_GripWarmerScaleIndicator _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseMainBG__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( SeatHeater_GripWarmerScaleIndicator );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->ScaleIndicatorWindow, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ScaleIndicatorBg, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ScaleIndicatorBar, &_this->_.XObject, 0 );
  CoreSystemEventHandler__Init( &_this->VehicleDataReceivedEventHandler, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( SeatHeater_GripWarmerScaleIndicator );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  ComponentsBaseComponent__OnSetDDModeEnabled( _this, 1 );
  ViewsImage_OnSetVisible( &_this->Super1.MainBottomBG, 0 );
  ViewsRectangle_OnSetVisible( &_this->Super1.BlackBG, 0 );
  CoreRectView__OnSetBounds( &_this->ScaleIndicatorWindow, _Const0001 );
  CoreRectView__OnSetBounds( &_this->ScaleIndicatorBg, _Const0001 );
  CoreRectView__OnSetBounds( &_this->ScaleIndicatorBar, _Const0002 );
  CoreGroup__Add( _this, ((CoreView)&_this->ScaleIndicatorWindow ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ScaleIndicatorBg ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ScaleIndicatorBar ), 0 );
  ViewsImage_OnSetBitmap( &_this->ScaleIndicatorWindow, EwLoadResource( &ResourceScaleIndicatorWindowLow, 
  ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->ScaleIndicatorBg, EwLoadResource( &ResourceScaleIndicatorBg, 
  ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->ScaleIndicatorBar, EwLoadResource( &ResourceScaleIndicatorBar, 
  ResourcesBitmap ));
  _this->VehicleDataReceivedEventHandler.OnEvent = EwNewSlot( _this, SeatHeater_GripWarmerScaleIndicator_OnVehicleDataReceivedSlot );
  CoreSystemEventHandler_OnSetEvent( &_this->VehicleDataReceivedEventHandler, &EwGetAutoObject( 
  &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->VehicleDataReceivedSystemEvent );
}

/* Re-Initializer for the class 'SeatHeater_GripWarmer::ScaleIndicator' */
void SeatHeater_GripWarmerScaleIndicator__ReInit( SeatHeater_GripWarmerScaleIndicator _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseMainBG__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->ScaleIndicatorWindow );
  ViewsImage__ReInit( &_this->ScaleIndicatorBg );
  ViewsImage__ReInit( &_this->ScaleIndicatorBar );
  CoreSystemEventHandler__ReInit( &_this->VehicleDataReceivedEventHandler );
}

/* Finalizer method for the class 'SeatHeater_GripWarmer::ScaleIndicator' */
void SeatHeater_GripWarmerScaleIndicator__Done( SeatHeater_GripWarmerScaleIndicator _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseMainBG );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->ScaleIndicatorWindow );
  ViewsImage__Done( &_this->ScaleIndicatorBg );
  ViewsImage__Done( &_this->ScaleIndicatorBar );
  CoreSystemEventHandler__Done( &_this->VehicleDataReceivedEventHandler );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseMainBG__Done( &_this->_.Super );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::ScaleIndicator.OnShortDownKeyActivated()' */
void SeatHeater_GripWarmerScaleIndicator_OnShortDownKeyActivated( SeatHeater_GripWarmerScaleIndicator _this )
{
  if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )) && ( 1 
      < _this->LevelValue ))
    DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
    DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeBUTTON_STATUS_AUDIO, 0 );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::ScaleIndicator.OnShortUpKeyActivated()' */
void SeatHeater_GripWarmerScaleIndicator_OnShortUpKeyActivated( SeatHeater_GripWarmerScaleIndicator _this )
{
  if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )) && ( 10 
      > _this->LevelValue ))
    DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
    DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeBUTTON_STATUS_AUDIO, 1 );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::ScaleIndicator.OnShortEnterKeyActivated()' */
void SeatHeater_GripWarmerScaleIndicator_OnShortEnterKeyActivated( SeatHeater_GripWarmerScaleIndicator _this )
{
  ComponentsBaseComponent__OnShortHomeKeyActivated( _this );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::ScaleIndicator.OnSetScaleIndicatorType()' */
void SeatHeater_GripWarmerScaleIndicator_OnSetScaleIndicatorType( SeatHeater_GripWarmerScaleIndicator _this, 
  XEnum value )
{
  if ( _this->ScaleIndicatorType != value )
  {
    _this->ScaleIndicatorType = value;

    switch ( _this->ScaleIndicatorType )
    {
      case EnumSeatHeaterGripWarmerLevelTypeLOW :
        ViewsImage_OnSetBitmap( &_this->ScaleIndicatorWindow, EwLoadResource( &ResourceScaleIndicatorWindowLow, 
        ResourcesBitmap ));
      break;

      case EnumSeatHeaterGripWarmerLevelTypeMID :
        ViewsImage_OnSetBitmap( &_this->ScaleIndicatorWindow, EwLoadResource( &ResourceScaleIndicatorWindowMid, 
        ResourcesBitmap ));
      break;

      case EnumSeatHeaterGripWarmerLevelTypeHIGH :
        ViewsImage_OnSetBitmap( &_this->ScaleIndicatorWindow, EwLoadResource( &ResourceScaleIndicatorWindowHigh, 
        ResourcesBitmap ));
      break;

      default :; 
    }
  }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::ScaleIndicator.OnSetLevelValue()' */
void SeatHeater_GripWarmerScaleIndicator_OnSetLevelValue( SeatHeater_GripWarmerScaleIndicator _this, 
  XInt32 value )
{
  if ( _this->LevelValue != value )
  {
    _this->LevelValue = value;

    if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
    {
      XRect NewBounds;
      ViewsImage_OnSetFrameNumber( &_this->ScaleIndicatorBar, 1 );
      NewBounds = _Const0003;
      NewBounds.Point1.X = 230;
      NewBounds.Point1.Y = ( 219 - ( 18 * ( _this->LevelValue - 1 )));
      NewBounds.Point2.X = 355;
      NewBounds.Point2.Y = ( 238 - ( 18 * ( _this->LevelValue - 1 )));
      CoreRectView__OnSetBounds( &_this->ScaleIndicatorBar, NewBounds );
    }
    else
      ViewsImage_OnSetFrameNumber( &_this->ScaleIndicatorBar, 0 );
  }
}

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void SeatHeater_GripWarmerScaleIndicator_OnVehicleDataReceivedSlot( SeatHeater_GripWarmerScaleIndicator _this, 
  XObject sender )
{
  DeviceInterfaceVehicleDataClass VehicleData;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  VehicleData = EwCastObject( _this->VehicleDataReceivedEventHandler.Context, DeviceInterfaceVehicleDataClass );

  if (( VehicleData != 0 ) && ( EnumVehicleRxTypeTIMEOUT_ERROR2_UPDATED == VehicleData->RxType ))
  {
    if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
        &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
      ViewsImage_OnSetFrameNumber( &_this->ScaleIndicatorBar, 1 );
    else
      ViewsImage_OnSetFrameNumber( &_this->ScaleIndicatorBar, 0 );
  }
}

/* Variants derived from the class : 'SeatHeater_GripWarmer::ScaleIndicator' */
EW_DEFINE_CLASS_VARIANTS( SeatHeater_GripWarmerScaleIndicator )
EW_END_OF_CLASS_VARIANTS( SeatHeater_GripWarmerScaleIndicator )

/* Virtual Method Table (VMT) for the class : 'SeatHeater_GripWarmer::ScaleIndicator' */
EW_DEFINE_CLASS( SeatHeater_GripWarmerScaleIndicator, ComponentsBaseMainBG, ScaleIndicatorWindow, 
                 ScaleIndicatorWindow, ScaleIndicatorWindow, ScaleIndicatorWindow, 
                 LevelValue, LevelValue, "SeatHeater_GripWarmer::ScaleIndicator" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetBuffered,
  CoreGroup_OnGetEnabled,
  CoreGroup_OnSetEnabled,
  CoreGroup_OnSetOpacity,
  CoreGroup_OnSetVisible,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  CoreGroup_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_GetViewAtIndex,
  CoreGroup_CountViews,
  CoreGroup_FindNextView,
  CoreGroup_FindSiblingView,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_Add,
  SeatHeater_GripWarmerScaleIndicator_OnShortDownKeyActivated,
  SeatHeater_GripWarmerScaleIndicator_OnShortUpKeyActivated,
  SeatHeater_GripWarmerScaleIndicator_OnShortEnterKeyActivated,
  ComponentsBaseMainBG_OnShortHomeKeyActivated,
  ComponentsBaseComponent_OnLongDownKeyActivated,
  ComponentsBaseComponent_OnLongUpKeyActivated,
  ComponentsBaseComponent_OnLongEnterKeyActivated,
  ComponentsBaseComponent_OnLongHomeKeyActivated,
  ComponentsBaseComponent_OnShortMagicKeyActivated,
  ComponentsBaseMainBG_OnSetDDModeEnabled,
  ComponentsBaseComponent_OnDownKeyReleased,
  ComponentsBaseComponent_OnUpKeyReleased,
EW_END_OF_CLASS( SeatHeater_GripWarmerScaleIndicator )

/* Initializer for the class 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction__Init( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  ComponentsBaseMainBG__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction );

  /* ... then construct all embedded objects */
  ViewsImage__Init( &_this->ImgLCBlueline, &_this->_.XObject, 0 );
  ComponentsBaseText__Init( &_this->CurrentItemTitleText, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ControlUpBg, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ControlDownBg, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ControlDownButton, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->ControlUpButton, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->VehicleFunctionIcon, &_this->_.XObject, 0 );
  CoreSystemEventHandler__Init( &_this->VehicleDataReceivedEventHandler, &_this->_.XObject, 0 );
  CoreTimer__Init( &_this->HighlightTimer, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( &_this->ImgLCBlueline, _Const0004 );
  CoreRectView__OnSetBounds( &_this->CurrentItemTitleText, _Const0005 );
  ViewsText_OnSetAlignment((ViewsText)&_this->CurrentItemTitleText, ViewsTextAlignmentAlignHorzLeft 
  | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString((ViewsText)&_this->CurrentItemTitleText, 0 );
  CoreRectView__OnSetBounds( &_this->ControlUpBg, _Const0006 );
  CoreRectView__OnSetBounds( &_this->ControlDownBg, _Const0007 );
  CoreRectView__OnSetBounds( &_this->ControlDownButton, _Const0007 );
  CoreRectView__OnSetBounds( &_this->ControlUpButton, _Const0006 );
  CoreRectView__OnSetBounds( &_this->VehicleFunctionIcon, _Const0008 );
  ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
  ViewsImage_OnSetVisible( &_this->VehicleFunctionIcon, 1 );
  CoreTimer_OnSetPeriod( &_this->HighlightTimer, 100 );
  CoreTimer_OnSetEnabled( &_this->HighlightTimer, 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ImgLCBlueline ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->CurrentItemTitleText ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ControlUpBg ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ControlDownBg ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ControlDownButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->ControlUpButton ), 0 );
  CoreGroup__Add( _this, ((CoreView)&_this->VehicleFunctionIcon ), 0 );
  ViewsImage_OnSetBitmap( &_this->ImgLCBlueline, EwLoadResource( &ResourceLCBlueline, 
  ResourcesBitmap ));
  ViewsText_OnSetFont((ViewsText)&_this->CurrentItemTitleText, EwLoadResource( &FontsNotoSansCjkJpMedium28pt, 
  ResourcesFont ));
  ViewsImage_OnSetBitmap( &_this->ControlUpBg, EwLoadResource( &ResourceControlButtonBackground, 
  ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->ControlDownBg, EwLoadResource( &ResourceControlButtonBackground, 
  ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->ControlDownButton, EwLoadResource( &ResourceControlDownButton, 
  ResourcesBitmap ));
  ViewsImage_OnSetBitmap( &_this->ControlUpButton, EwLoadResource( &ResourceControlUpButton, 
  ResourcesBitmap ));
  _this->VehicleDataReceivedEventHandler.OnEvent = EwNewSlot( _this, SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnVehicleDataReceivedSlot );
  CoreSystemEventHandler_OnSetEvent( &_this->VehicleDataReceivedEventHandler, &EwGetAutoObject( 
  &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->VehicleDataReceivedSystemEvent );
  _this->HighlightTimer.OnTrigger = EwNewSlot( _this, SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnHighlightEndSlot );

  /* Call the user defined constructor */
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_Init( _this, aArg );
}

/* Re-Initializer for the class 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction__ReInit( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  /* At first re-initialize the super class ... */
  ComponentsBaseMainBG__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  ViewsImage__ReInit( &_this->ImgLCBlueline );
  ComponentsBaseText__ReInit( &_this->CurrentItemTitleText );
  ViewsImage__ReInit( &_this->ControlUpBg );
  ViewsImage__ReInit( &_this->ControlDownBg );
  ViewsImage__ReInit( &_this->ControlDownButton );
  ViewsImage__ReInit( &_this->ControlUpButton );
  ViewsImage__ReInit( &_this->VehicleFunctionIcon );
  CoreSystemEventHandler__ReInit( &_this->VehicleDataReceivedEventHandler );
  CoreTimer__ReInit( &_this->HighlightTimer );
}

/* Finalizer method for the class 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction__Done( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( ComponentsBaseMainBG );

  /* Finalize all embedded objects */
  ViewsImage__Done( &_this->ImgLCBlueline );
  ComponentsBaseText__Done( &_this->CurrentItemTitleText );
  ViewsImage__Done( &_this->ControlUpBg );
  ViewsImage__Done( &_this->ControlDownBg );
  ViewsImage__Done( &_this->ControlDownButton );
  ViewsImage__Done( &_this->ControlUpButton );
  ViewsImage__Done( &_this->VehicleFunctionIcon );
  CoreSystemEventHandler__Done( &_this->VehicleDataReceivedEventHandler );
  CoreTimer__Done( &_this->HighlightTimer );

  /* Don't forget to deinitialize the super class ... */
  ComponentsBaseMainBG__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_Init( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( aArg );

  if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
      == EnumVehicleSupportedFunctionSEAT_HEATER )
  {
    ViewsText_OnSetString((ViewsText)&_this->CurrentItemTitleText, EwGetVariantOfString( 
    &StringsLNC_SEAT_HEATER ));
    SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateHeaterLevel( _this, 
    EnumVehicleRxTypeSEAT_HEATER_STATUS );
  }
  else
    if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
        == EnumVehicleSupportedFunctionGRIP_WARMER )
    {
      ViewsText_OnSetString((ViewsText)&_this->CurrentItemTitleText, EwGetVariantOfString( 
      &StringsGPW01_GRIP_WARMER ));
      SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateHeaterLevel( 
      _this, EnumVehicleRxTypeGRIP_WARMER_STATUS );
    }
    else
      if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
          == EnumVehicleSupportedFunctionWIND_SCREEN )
      {
        ViewsText_OnSetString((ViewsText)&_this->CurrentItemTitleText, EwGetVariantOfString( 
        &StringsWSC01_WIND_SCREEN ));
        ViewsImage_OnSetBitmap( &_this->ControlUpButton, EwLoadResource( &ResourceControlUpButtonArrow, 
        ResourcesBitmap ));
        ViewsImage_OnSetBitmap( &_this->ControlDownButton, EwLoadResource( &ResourceControlDownButtonArrow, 
        ResourcesBitmap ));
      }
      else
        EwTrace( "%s", EwLoadString( &_Const0009 ));
}

/* The method UpdateViewState() is invoked automatically after the state of the 
   component has been changed. This method can be overridden and filled with logic 
   to ensure the visual aspect of the component does reflect its current state. 
   For example, the 'enabled' state of the component can affect its colors (disabled 
   components may appear pale). In this case the logic of the method should modify 
   the respective color properties accordingly to the current 'enabled' state. 
   The current state of the component is passed as a set in the parameter aState. 
   It reflects the very basic component state like its visibility or the ability 
   to react to user inputs. Beside this common state, the method can also involve 
   any other variables used in the component as long as they reflect its current 
   state. For example, the toggle switch component can take in account its toggle 
   state 'on' or 'off' and change accordingly the location of the slider, etc.
   Usually, this method will be invoked automatically by the framework. Optionally 
   you can request its invocation by using the method @InvalidateViewState(). */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateViewState( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  XSet aState )
{
  CoreGroup_UpdateViewState((CoreGroup)_this, aState );

  if (( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
      == EnumVehicleSupportedFunctionSEAT_HEATER ) || ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction == EnumVehicleSupportedFunctionGRIP_WARMER ))
  {
    if (( 0 <= (XUInt32)_this->HeaterSettingStatus ) && ( 3 >= (XUInt32)_this->HeaterSettingStatus ))
      switch ( _this->HeaterSettingStatus )
      {
        case EnumHeaterSettingStatusTypeOFF :
        {
          if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
              == EnumVehicleSupportedFunctionSEAT_HEATER )
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconSeatHeater0Large, ResourcesBitmap ));
          else
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconGripWarmer0Large, ResourcesBitmap ));

          if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( 
              EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
          }
          else
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
          }
        }
        break;

        case EnumHeaterSettingStatusTypeLOW :
        {
          if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
              == EnumVehicleSupportedFunctionSEAT_HEATER )
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconSeatHeater1Large, ResourcesBitmap ));
          else
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconGripWarmer1Large, ResourcesBitmap ));

          if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( 
              EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 0 );
          }
          else
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
          }
        }
        break;

        case EnumHeaterSettingStatusTypeMID :
        {
          if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
              == EnumVehicleSupportedFunctionSEAT_HEATER )
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconSeatHeater2Large, ResourcesBitmap ));
          else
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconGripWarmer2Large, ResourcesBitmap ));

          if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( 
              EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 0 );
          }
          else
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
          }
        }
        break;

        case EnumHeaterSettingStatusTypeHIGH :
        {
          if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
              == EnumVehicleSupportedFunctionSEAT_HEATER )
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconSeatHeater3Large, ResourcesBitmap ));
          else
            ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( 
            &ResourceIconGripWarmer3Large, ResourcesBitmap ));

          if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( 
              EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 0 );
          }
          else
          {
            ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 0 );
            ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
            ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
          }
        }
        break;

        default :; 
      }
  }
  else
    if ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction 
        == EnumVehicleSupportedFunctionWIND_SCREEN )
    {
      ViewsImage_OnSetBitmap( &_this->VehicleFunctionIcon, EwLoadResource( &ResourceIconWindScreenLarge, 
      ResourcesBitmap ));

      if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
          &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
      {
        ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 1 );
        ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 0 );
        ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 0 );
      }
      else
      {
        ViewsImage_OnSetFrameNumber( &_this->VehicleFunctionIcon, 0 );
        ViewsImage_OnSetFrameNumber( &_this->ControlUpButton, 1 );
        ViewsImage_OnSetFrameNumber( &_this->ControlDownButton, 1 );
      }
    }
    else
      EwTrace( "%s", EwLoadString( &_Const0009 ));
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.OnShortDownKeyActivated()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortDownKeyActivated( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
    switch ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction )
    {
      case EnumVehicleSupportedFunctionSEAT_HEATER :
        if ( 0 < (XUInt32)_this->HeaterSettingStatus )
        {
          SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_StartHighlight( 
          _this, &_this->ControlDownBg );
          DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
          DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeSEAT_HEATER_CHANGE_LEVEL, 
          1 );
        }
      break;

      case EnumVehicleSupportedFunctionGRIP_WARMER :
        if ( 0 < (XUInt32)_this->HeaterSettingStatus )
        {
          SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_StartHighlight( 
          _this, &_this->ControlDownBg );
          DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
          DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeGRIP_WARMER_CHANGE_LEVEL, 
          1 );
        }
      break;

      case EnumVehicleSupportedFunctionWIND_SCREEN :
      {
        ViewsImage_OnSetFrameNumber( &_this->ControlDownBg, 1 );
        DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
        DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeWIND_SCREEN_OPERATION, 
        1 );
      }
      break;

      default :; 
    }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.OnShortUpKeyActivated()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortUpKeyActivated( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  if ( !DeviceInterfaceVehicleDeviceClass_OnGetIsTimeoutError2Detected( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )))
    switch ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction )
    {
      case EnumVehicleSupportedFunctionSEAT_HEATER :
        if ( 3 > (XUInt32)_this->HeaterSettingStatus )
        {
          SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_StartHighlight( 
          _this, &_this->ControlUpBg );
          DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
          DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeSEAT_HEATER_CHANGE_LEVEL, 
          2 );
        }
      break;

      case EnumVehicleSupportedFunctionGRIP_WARMER :
        if ( 3 > (XUInt32)_this->HeaterSettingStatus )
        {
          SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_StartHighlight( 
          _this, &_this->ControlUpBg );
          DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
          DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeGRIP_WARMER_CHANGE_LEVEL, 
          2 );
        }
      break;

      case EnumVehicleSupportedFunctionWIND_SCREEN :
      {
        ViewsImage_OnSetFrameNumber( &_this->ControlUpBg, 1 );
        DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
        DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeWIND_SCREEN_OPERATION, 
        2 );
      }
      break;

      default :; 
    }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.OnShortEnterKeyActivated()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortEnterKeyActivated( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  ComponentsBaseComponent__OnShortHomeKeyActivated( _this );
}

/* Callback when down key of on trigger mode is released */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnDownKeyReleased( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  switch ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction )
  {
    case EnumVehicleSupportedFunctionSEAT_HEATER :
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeSEAT_HEATER_CHANGE_LEVEL, 
      0 );
    break;

    case EnumVehicleSupportedFunctionGRIP_WARMER :
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeGRIP_WARMER_CHANGE_LEVEL, 
      0 );
    break;

    case EnumVehicleSupportedFunctionWIND_SCREEN :
    {
      ViewsImage_OnSetFrameNumber( &_this->ControlDownBg, 0 );
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeWIND_SCREEN_OPERATION, 
      0 );
    }
    break;

    default :; 
  }
}

/* Callback when up key of on trigger mode is released */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnUpKeyReleased( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this )
{
  switch ( EwGetAutoObject( &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass )->CurrentVehicleFunction )
  {
    case EnumVehicleSupportedFunctionSEAT_HEATER :
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeSEAT_HEATER_CHANGE_LEVEL, 
      0 );
    break;

    case EnumVehicleSupportedFunctionGRIP_WARMER :
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeGRIP_WARMER_CHANGE_LEVEL, 
      0 );
    break;

    case EnumVehicleSupportedFunctionWIND_SCREEN :
    {
      ViewsImage_OnSetFrameNumber( &_this->ControlUpBg, 0 );
      DeviceInterfaceVehicleDeviceClass_SetData( EwGetAutoObject( &DeviceInterfaceVehicleDevice, 
      DeviceInterfaceVehicleDeviceClass ), EnumVehicleTxTypeWIND_SCREEN_OPERATION, 
      0 );
    }
    break;

    default :; 
  }
}

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnVehicleDataReceivedSlot( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  XObject sender )
{
  DeviceInterfaceVehicleDataClass VehicleData;

  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  VehicleData = EwCastObject( _this->VehicleDataReceivedEventHandler.Context, DeviceInterfaceVehicleDataClass );

  if ( VehicleData != 0 )
    switch ( VehicleData->RxType )
    {
      case EnumVehicleRxTypeSEAT_HEATER_STATUS :
      case EnumVehicleRxTypeGRIP_WARMER_STATUS :
        SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateHeaterLevel( 
        _this, VehicleData->RxType );
      break;

      case EnumVehicleRxTypeTIMEOUT_ERROR2_UPDATED :
        CoreGroup_InvalidateViewState((CoreGroup)_this );
      break;

      default :; 
    }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.UpdateHeaterLevel()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateHeaterLevel( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  XEnum aNewType )
{
  DeviceInterfaceVehicleDataClass VehicleData;

  switch ( aNewType )
  {
    case EnumVehicleRxTypeGRIP_WARMER_STATUS :
    {
      VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeGRIP_WARMER_STATUS );

      if (((( VehicleData != 0 ) && ((XUInt32)_this->HeaterSettingStatus != VehicleData->DataUInt32 )) 
          && ( 3 >= VehicleData->DataUInt32 )) && ( VehicleData->DataUInt32 >= 0 ))
      {
        _this->HeaterSettingStatus = (XEnum)VehicleData->DataUInt32;
        CoreGroup_InvalidateViewState((CoreGroup)_this );
      }
    }
    break;

    case EnumVehicleRxTypeSEAT_HEATER_STATUS :
    {
      VehicleData = DeviceInterfaceVehicleDeviceClass_GetData( EwGetAutoObject( 
      &DeviceInterfaceVehicleDevice, DeviceInterfaceVehicleDeviceClass ), EnumVehicleRxTypeSEAT_HEATER_STATUS );

      if (((( VehicleData != 0 ) && ((XUInt32)_this->HeaterSettingStatus != VehicleData->DataUInt32 )) 
          && ( 3 >= VehicleData->DataUInt32 )) && ( VehicleData->DataUInt32 >= 0 ))
      {
        _this->HeaterSettingStatus = (XEnum)VehicleData->DataUInt32;
        CoreGroup_InvalidateViewState((CoreGroup)_this );
      }
    }
    break;

    default :; 
  }
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.StartHighlight()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_StartHighlight( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  ViewsImage aBackground )
{
  ViewsImage_OnSetFrameNumber( aBackground, 1 );
  _this->HighlightBG = aBackground;
  CoreTimer_OnSetEnabled( &_this->HighlightTimer, 1 );
}

/* 'C' function for method : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction.OnHighlightEndSlot()' */
void SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnHighlightEndSlot( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction _this, 
  XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreTimer_OnSetEnabled( &_this->HighlightTimer, 0 );
  ViewsImage_OnSetFrameNumber( _this->HighlightBG, 0 );
}

/* Variants derived from the class : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction' */
EW_DEFINE_CLASS_VARIANTS( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction )
EW_END_OF_CLASS_VARIANTS( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction )

/* Virtual Method Table (VMT) for the class : 'SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction' */
EW_DEFINE_CLASS( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction, ComponentsBaseMainBG, 
                 HighlightBG, ImgLCBlueline, ImgLCBlueline, ImgLCBlueline, HeaterSettingStatus, 
                 HeaterSettingStatus, "SeatHeater_GripWarmer::SHT01_GPW01_WSC01_VehicleFunction" )
  CoreRectView_initLayoutContext,
  CoreView_GetRoot,
  CoreGroup_Draw,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreGroup_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreGroup_OnSetFocus,
  CoreGroup_OnSetBuffered,
  CoreGroup_OnGetEnabled,
  CoreGroup_OnSetEnabled,
  CoreGroup_OnSetOpacity,
  CoreGroup_OnSetVisible,
  CoreGroup_IsCurrentDialog,
  CoreGroup_IsActiveDialog,
  CoreGroup_DispatchEvent,
  CoreGroup_BroadcastEvent,
  CoreGroup_UpdateLayout,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_UpdateViewState,
  CoreGroup_InvalidateArea,
  CoreGroup_GetViewAtIndex,
  CoreGroup_CountViews,
  CoreGroup_FindNextView,
  CoreGroup_FindSiblingView,
  CoreGroup_RestackTop,
  CoreGroup_Restack,
  CoreGroup_Remove,
  CoreGroup_Add,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortDownKeyActivated,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortUpKeyActivated,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnShortEnterKeyActivated,
  ComponentsBaseMainBG_OnShortHomeKeyActivated,
  ComponentsBaseComponent_OnLongDownKeyActivated,
  ComponentsBaseComponent_OnLongUpKeyActivated,
  ComponentsBaseComponent_OnLongEnterKeyActivated,
  ComponentsBaseComponent_OnLongHomeKeyActivated,
  ComponentsBaseComponent_OnShortMagicKeyActivated,
  ComponentsBaseMainBG_OnSetDDModeEnabled,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnDownKeyReleased,
  SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction_OnUpKeyReleased,
EW_END_OF_CLASS( SeatHeater_GripWarmerSHT01_GPW01_WSC01_VehicleFunction )

/* Embedded Wizard */
