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

#ifndef _DeviceInterfaceConnectionStatusContext_H
#define _DeviceInterfaceConnectionStatusContext_H

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

/* Forward declaration of the class DeviceInterface::ConnectionStatusContext */
#ifndef _DeviceInterfaceConnectionStatusContext_
  EW_DECLARE_CLASS( DeviceInterfaceConnectionStatusContext )
#define _DeviceInterfaceConnectionStatusContext_
#endif


/* Deklaration of class : 'DeviceInterface::ConnectionStatusContext' */
EW_DEFINE_FIELDS( DeviceInterfaceConnectionStatusContext, XObject )
  EW_VARIABLE( Status,          XEnum )
EW_END_OF_FIELDS( DeviceInterfaceConnectionStatusContext )

/* Virtual Method Table (VMT) for the class : 'DeviceInterface::ConnectionStatusContext' */
EW_DEFINE_METHODS( DeviceInterfaceConnectionStatusContext, XObject )
EW_END_OF_METHODS( DeviceInterfaceConnectionStatusContext )

#ifdef __cplusplus
  }
#endif

#endif /* _DeviceInterfaceConnectionStatusContext_H */

/* Embedded Wizard */
