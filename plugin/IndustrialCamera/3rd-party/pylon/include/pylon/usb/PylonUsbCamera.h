//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Generic pylon USB3 Vision camera interface
*/

#ifndef PYLON_USB3VISION_CAMERA_H
#define PYLON_USB3VISION_CAMERA_H

#if _MSC_VER > 1000
#   pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include "../DeviceClass.h"
#include "../NodeMapProxy.h"
#include "../StreamGrabberProxy.h"
#include "../EventGrabberProxy.h"

#include "BaslerUsbDeviceInfo.h"
#include "../PylonDeviceProxy.h"

#include "_UsbStreamParams.h"
#include "_UsbEventParams.h"
#include "_UsbTLParams.h"


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: Class for pylon USB3 Vision cameras providing access to transport layer related parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_NODEMAP( CPylonUsbTLParams, CNodeMapProxyT<Basler_UsbTLParams::CUsbTLParams_Params> );


    //**************************************************************************************************
    //! Low Level API: Class for pylon USB3 Vision cameras providing access to stream grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_STREAMGRABBER( CPylonUsbStreamGrabber, CStreamGrabberProxyT<Basler_UsbStreamParams::CUsbStreamParams_Params> );


    //**************************************************************************************************
    //! Low Level API: Class for pylon USB3 Vision cameras providing access to event grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_EVENTGRABBER( CPylonUsbEventGrabber, CEventGrabberProxyT<Basler_UsbEventParams::CUsbEventParams_Params> );


    //**************************************************************************************************
    //! Low Level API: The camera class for pylon USB3 Vision camera devices
    /**
    This is the base class for pylon USB3 Vision cameras providing access to camera parameters.
    \see \ref configuringcameras

    \tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    template<class TCameraParams>
    class CPylonUsbCameraT : public CPylonDeviceProxyT<TCameraParams>
    {
    public:
        typedef Pylon::CBaslerUsbDeviceInfo   DeviceInfo_t;    //!< \copybrief Pylon::CBaslerUsbDeviceInfo
        typedef Pylon::CPylonUsbTLParams      TlParams_t;      //!< \copybrief Pylon::CPylonUsbTLParams
        typedef Pylon::CPylonUsbStreamGrabber StreamGrabber_t; //!< \copybrief Pylon::CPylonUsbStreamGrabber
        typedef Pylon::CPylonUsbEventGrabber  EventGrabber_t;  //!< \copybrief Pylon::CPylonUsbEventGrabber

        /// The name of this device class, use this for enumeration
        static String_t DeviceClass()
        {
            return BaslerUsbDeviceClass;
        }

    public:
        //! \name Construction
        // \{

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()

        \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()
        */
        CPylonUsbCameraT()
        {
        };

              /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)

              \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)
              */
        CPylonUsbCameraT( IPylonDevice* pDevice, bool takeOwnership = true )
            : CPylonDeviceProxyT<TCameraParams>( pDevice, takeOwnership )
        {
        }

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()

        \copydetails Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()
        */
        virtual ~CPylonUsbCameraT()
        {
        };

        //\}
    };


} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // PYLON_USB3VISION_CAMERA_H
