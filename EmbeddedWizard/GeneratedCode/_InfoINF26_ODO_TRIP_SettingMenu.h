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

#ifndef _InfoINF26_ODO_TRIP_SettingMenu_H
#define _InfoINF26_ODO_TRIP_SettingMenu_H

#ifdef __cplusplus
  extern "C"
  {
#endif

#include "ewrte.h"
#if EW_RTE_VERSION != 0x000B0000
  #error Wrong version of Embedded Wizard Runtime Environment.
#endif

#include "ewgfx.h"
#if EW_GFX_VERSION != 0x000B0000
  #error Wrong version of Embedded Wizard Graphics Engine.
#endif

#include "_ComponentsDDModeMask.h"
#include "_CoreKeyPressHandler.h"
#include "_CoreSystemEventHandler.h"
#include "_CoreTimer.h"
#include "_MenuBaseMenuView.h"
#include "_MenuVerticalMenu.h"
#include "_ViewsImage.h"
#include "_ViewsRectangle.h"

/* Forward declaration of the class Components::BaseMainBG */
#ifndef _ComponentsBaseMainBG_
  EW_DECLARE_CLASS( ComponentsBaseMainBG )
#define _ComponentsBaseMainBG_
#endif

/* Forward declaration of the class Core::DialogContext */
#ifndef _CoreDialogContext_
  EW_DECLARE_CLASS( CoreDialogContext )
#define _CoreDialogContext_
#endif

/* Forward declaration of the class Core::Group */
#ifndef _CoreGroup_
  EW_DECLARE_CLASS( CoreGroup )
#define _CoreGroup_
#endif

/* Forward declaration of the class Core::LayoutContext */
#ifndef _CoreLayoutContext_
  EW_DECLARE_CLASS( CoreLayoutContext )
#define _CoreLayoutContext_
#endif

/* Forward declaration of the class Core::TaskQueue */
#ifndef _CoreTaskQueue_
  EW_DECLARE_CLASS( CoreTaskQueue )
#define _CoreTaskQueue_
#endif

/* Forward declaration of the class Core::View */
#ifndef _CoreView_
  EW_DECLARE_CLASS( CoreView )
#define _CoreView_
#endif

/* Forward declaration of the class Effects::Fader */
#ifndef _EffectsFader_
  EW_DECLARE_CLASS( EffectsFader )
#define _EffectsFader_
#endif

/* Forward declaration of the class Graphics::Canvas */
#ifndef _GraphicsCanvas_
  EW_DECLARE_CLASS( GraphicsCanvas )
#define _GraphicsCanvas_
#endif

/* Forward declaration of the class Info::INF26_ODO_TRIP_SettingMenu */
#ifndef _InfoINF26_ODO_TRIP_SettingMenu_
  EW_DECLARE_CLASS( InfoINF26_ODO_TRIP_SettingMenu )
#define _InfoINF26_ODO_TRIP_SettingMenu_
#endif

/* Forward declaration of the class Menu::ItemBase */
#ifndef _MenuItemBase_
  EW_DECLARE_CLASS( MenuItemBase )
#define _MenuItemBase_
#endif


/* Deklaration of class : 'Info::INF26_ODO_TRIP_SettingMenu' */
EW_DEFINE_FIELDS( InfoINF26_ODO_TRIP_SettingMenu, MenuBaseMenuView )
  EW_OBJECT  ( CheckMarkUpdateTimer, CoreTimer )
  EW_OBJECT  ( VehicleDataReceivedEventHandler, CoreSystemEventHandler )
  EW_ARRAY   ( AllSettings,     XEnum, [4])
  EW_VARIABLE( SelectedItem,    XEnum )
  EW_VARIABLE( MileageSetting,  XEnum )
  EW_ARRAY   ( SupportedSetting, XEnum, [4])
  EW_VARIABLE( IsWaitingForResponse, XBool )
EW_END_OF_FIELDS( InfoINF26_ODO_TRIP_SettingMenu )

/* Virtual Method Table (VMT) for the class : 'Info::INF26_ODO_TRIP_SettingMenu' */
EW_DEFINE_METHODS( InfoINF26_ODO_TRIP_SettingMenu, MenuBaseMenuView )
  EW_METHOD( initLayoutContext, void )( CoreRectView _this, XRect aBounds, CoreOutline 
    aOutline )
  EW_METHOD( GetRoot,           CoreRoot )( CoreView _this )
  EW_METHOD( Draw,              void )( CoreGroup _this, GraphicsCanvas aCanvas, 
    XRect aClip, XPoint aOffset, XInt32 aOpacity, XBool aBlend )
  EW_METHOD( HandleEvent,       XObject )( CoreView _this, CoreEvent aEvent )
  EW_METHOD( CursorHitTest,     CoreCursorHit )( CoreGroup _this, XRect aArea, XInt32 
    aFinger, XInt32 aStrikeCount, CoreView aDedicatedView, XSet aRetargetReason )
  EW_METHOD( ArrangeView,       XPoint )( CoreRectView _this, XRect aBounds, XEnum 
    aFormation )
  EW_METHOD( MoveView,          void )( CoreRectView _this, XPoint aOffset, XBool 
    aFastMove )
  EW_METHOD( GetExtent,         XRect )( CoreRectView _this )
  EW_METHOD( ChangeViewState,   void )( CoreGroup _this, XSet aSetState, XSet aClearState )
  EW_METHOD( OnSetBounds,       void )( CoreGroup _this, XRect value )
  EW_METHOD( OnSetFocus,        void )( CoreGroup _this, CoreView value )
  EW_METHOD( OnSetBuffered,     void )( CoreGroup _this, XBool value )
  EW_METHOD( OnGetEnabled,      XBool )( CoreGroup _this )
  EW_METHOD( OnSetEnabled,      void )( CoreGroup _this, XBool value )
  EW_METHOD( OnSetOpacity,      void )( CoreGroup _this, XInt32 value )
  EW_METHOD( OnSetVisible,      void )( CoreGroup _this, XBool value )
  EW_METHOD( IsCurrentDialog,   XBool )( CoreGroup _this )
  EW_METHOD( IsActiveDialog,    XBool )( CoreGroup _this, XBool aRecursive )
  EW_METHOD( DispatchEvent,     XObject )( CoreGroup _this, CoreEvent aEvent )
  EW_METHOD( BroadcastEvent,    XObject )( CoreGroup _this, CoreEvent aEvent, XSet 
    aFilter )
  EW_METHOD( UpdateLayout,      void )( CoreGroup _this, XPoint aSize )
  EW_METHOD( UpdateViewState,   void )( CoreGroup _this, XSet aState )
  EW_METHOD( InvalidateArea,    void )( CoreGroup _this, XRect aArea )
  EW_METHOD( GetViewAtIndex,    CoreView )( CoreGroup _this, XInt32 aIndex )
  EW_METHOD( CountViews,        XInt32 )( CoreGroup _this )
  EW_METHOD( FindNextView,      CoreView )( CoreGroup _this, CoreView aView, XSet 
    aFilter )
  EW_METHOD( FindSiblingView,   CoreView )( CoreGroup _this, CoreView aView, XSet 
    aFilter )
  EW_METHOD( RestackTop,        void )( CoreGroup _this, CoreView aView )
  EW_METHOD( Restack,           void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
  EW_METHOD( Remove,            void )( CoreGroup _this, CoreView aView )
  EW_METHOD( Add,               void )( CoreGroup _this, CoreView aView, XInt32 
    aOrder )
  EW_METHOD( OnShortDownKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortUpKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortEnterKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortHomeKeyActivated, void )( ComponentsBaseMainBG _this )
  EW_METHOD( OnLongDownKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongUpKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongEnterKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnLongHomeKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnShortMagicKeyActivated, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnSetDDModeEnabled, void )( MenuBaseMenuView _this, XBool value )
  EW_METHOD( OnDownKeyReleased, void )( ComponentsBaseComponent _this )
  EW_METHOD( OnUpKeyReleased,   void )( ComponentsBaseComponent _this )
  EW_METHOD( LoadItemClass,     XClass )( InfoINF26_ODO_TRIP_SettingMenu _this, 
    XInt32 aItemNo )
  EW_METHOD( LoadItemTitle,     XString )( InfoINF26_ODO_TRIP_SettingMenu _this, 
    XInt32 aItemNo )
  EW_METHOD( OnItemActivate,    void )( InfoINF26_ODO_TRIP_SettingMenu _this, XInt32 
    aItemNo, MenuItemBase aMenuItem )
  EW_METHOD( LoadItemChecked,   XBool )( InfoINF26_ODO_TRIP_SettingMenu _this, XInt32 
    aItemNo )
  EW_METHOD( LoadItemEnabled,   XBool )( InfoINF26_ODO_TRIP_SettingMenu _this, XInt32 
    aItemNo )
  EW_METHOD( LoadItemBaseValue, XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemMessage,   XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemReceivedTime, XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemCategory,  XEnum )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemUid,       XUInt32 )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemToggle,    XBool )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemUnit,      XString )( InfoINF26_ODO_TRIP_SettingMenu _this, 
    XInt32 aItemNo )
  EW_METHOD( LoadItemValue,     XString )( InfoINF26_ODO_TRIP_SettingMenu _this, 
    XInt32 aItemNo )
  EW_METHOD( OnItemLongEnterKeyActivate, void )( InfoINF26_ODO_TRIP_SettingMenu _this, 
    XInt32 aItemNo, MenuItemBase aMenuItem )
  EW_METHOD( LoadItemHour,      XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemMinute,    XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadPoiListItemValue, XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadPoiListItemUnit, XString )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemIcon1Visible, XBool )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemIcon2Visible, XBool )( MenuBaseMenuView _this, XInt32 aItemNo )
  EW_METHOD( LoadItemDeviceAddress, XUInt64 )( MenuBaseMenuView _this, XInt32 aItemNo )
EW_END_OF_METHODS( InfoINF26_ODO_TRIP_SettingMenu )

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void InfoINF26_ODO_TRIP_SettingMenu_Init( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XHandle aArg );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemClass()' */
XClass InfoINF26_ODO_TRIP_SettingMenu_LoadItemClass( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemTitle()' */
XString InfoINF26_ODO_TRIP_SettingMenu_LoadItemTitle( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.OnItemActivate()' */
void InfoINF26_ODO_TRIP_SettingMenu_OnItemActivate( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo, MenuItemBase aMenuItem );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemChecked()' */
XBool InfoINF26_ODO_TRIP_SettingMenu_LoadItemChecked( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemEnabled()' */
XBool InfoINF26_ODO_TRIP_SettingMenu_LoadItemEnabled( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemUnit()' */
XString InfoINF26_ODO_TRIP_SettingMenu_LoadItemUnit( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.LoadItemValue()' */
XString InfoINF26_ODO_TRIP_SettingMenu_LoadItemValue( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.OnItemLongEnterKeyActivate()' */
void InfoINF26_ODO_TRIP_SettingMenu_OnItemLongEnterKeyActivate( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XInt32 aItemNo, MenuItemBase aMenuItem );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.OnCheckMarkUpdateSlot()' */
void InfoINF26_ODO_TRIP_SettingMenu_OnCheckMarkUpdateSlot( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XObject sender );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.GetMileageSetting()' */
void InfoINF26_ODO_TRIP_SettingMenu_GetMileageSetting( InfoINF26_ODO_TRIP_SettingMenu _this );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.SetNoOfMenuItems()' */
void InfoINF26_ODO_TRIP_SettingMenu_SetNoOfMenuItems( InfoINF26_ODO_TRIP_SettingMenu _this );

/* 'C' function for method : 'Info::INF26_ODO_TRIP_SettingMenu.GetSelectedOdoTrip()' */
void InfoINF26_ODO_TRIP_SettingMenu_GetSelectedOdoTrip( InfoINF26_ODO_TRIP_SettingMenu _this );

/* This slot method is executed when the associated system event handler 'SystemEventHandler' 
   receives an event. */
void InfoINF26_ODO_TRIP_SettingMenu_OnVehicleDataReceivedSlot( InfoINF26_ODO_TRIP_SettingMenu _this, 
  XObject sender );

#ifdef __cplusplus
  }
#endif

#endif /* _InfoINF26_ODO_TRIP_SettingMenu_H */

/* Embedded Wizard */
