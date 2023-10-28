//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Generic pylon CameraLink camera interface
*/

#ifndef PYLON_CAMERALINK_CAMERA_H
#define PYLON_CAMERALINK_CAMERA_H

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include "../DeviceClass.h"
#include "../NodeMapProxy.h"
#include "../StreamGrabberProxy.h"
#include "../EventGrabberProxy.h"

#include "../PylonDeviceProxy.h"


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: pylon CameraLink cameras doesn't support TL Params.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    //PYLON_DEFINE_NODEMAP(CPylonCameraLinkTLParams, CNodeMapProxyT<>);
    typedef void CPylonCameraLinkTLParams;


    //**************************************************************************************************
    //! Low Level API: pylon CameraLink cameras doesn't support stream grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    //PYLON_DEFINE_STREAMGRABBER(CPylonCameraLinkStreamGrabber, CStreamGrabberProxyT<>);
    typedef void CPylonCameraLinkStreamGrabber;


    //**************************************************************************************************
    //! Low Level API: pylon CameraLink cameras doesn't support event grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    //PYLON_DEFINE_EVENTGRABBER(CPylonCameraLinkEventGrabber, CEventGrabberProxyT<>);
    typedef void CPylonCameraLinkEventGrabber;


    //**************************************************************************************************
    //! Low Level API: The camera class for pylon CameraLink camera devices
    /**
    This is the base class for pylon CameraLink cameras providing access to camera parameters.
    \see \ref configuringcameras

    \tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    template<class TCameraParams>
    class CPylonCameraLinkCameraT : public CPylonDeviceProxyT<TCameraParams>
    {
    public:
        typedef void                                 DeviceInfo_t;
        typedef Pylon::CPylonCameraLinkTLParams      TlParams_t;      //!< \copybrief Pylon::CPylonCameraLinkTLParams
        typedef Pylon::CPylonCameraLinkStreamGrabber StreamGrabber_t; //!< \copybrief Pylon::CPylonCameraLinkStreamGrabber
        typedef Pylon::CPylonCameraLinkEventGrabber  EventGrabber_t;  //!< \copybrief Pylon::CPylonCameraLinkEventGrabber

        //! The name of this device class, use this for enumeration
        static String_t DeviceClass()
        {
            return BaslerCameraLinkDeviceClass;
        }

    public:
        //! \name Construction
        // \{

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()

        \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT()
        */
        CPylonCameraLinkCameraT()
        {
        };

              /** \brief \copybrief Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)

              \copydetails Pylon::CPylonDeviceProxyT::CPylonDeviceProxyT(IPylonDevice*,bool)
              */
        CPylonCameraLinkCameraT( IPylonDevice* pDevice, bool takeOwnership = true )
            : CPylonDeviceProxyT<TCameraParams>( pDevice, takeOwnership )
        {
        }

        /** \brief \copybrief Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()

        \copydetails Pylon::CPylonDeviceProxyT::~CPylonDeviceProxyT()
        */
        virtual ~CPylonCameraLinkCameraT()
        {
        }

        //\}
    };


} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // PYLON_CAMERALINK_CAMERA_H
