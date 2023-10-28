//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief Low Level API: Generic pylon GigE Vision camera interface
*/

#ifndef PYLON_GIGE_CAMERA_H
#define PYLON_GIGE_CAMERA_H

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

#include "BaslerGigEDeviceInfo.h"
#include "PylonGigEDeviceProxy.h"

#include "_GigETLParams.h"
#include "_GigEStreamParams.h"
#include "_GigEEventParams.h"


namespace Pylon
{
    //**************************************************************************************************
    //! Low Level API: Class for pylon GigE Vision cameras providing access to transport layer related parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_NODEMAP( CPylonGigETLParams, CNodeMapProxyT<Basler_GigETLParams::CGigETLParams_Params> );


    //**************************************************************************************************
    //! Low Level API: Class for pylon GigE Vision cameras providing access to stream grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_STREAMGRABBER( CPylonGigEStreamGrabber, CStreamGrabberProxyT<Basler_GigEStreamParams::CGigEStreamParams_Params> );


    //**************************************************************************************************
    //! Low Level API: Class for pylon GigE Vision cameras providing access to event grabber related methods and parameters.
    /**
    \see \ref configuringcameras
    \ingroup Pylon_LowLevelApi
    */
    //**************************************************************************************************
    PYLON_DEFINE_EVENTGRABBER( CPylonGigEEventGrabber, CEventGrabberProxyT<Basler_GigEEventParams::CGigEEventParams_Params> );


    //**************************************************************************************************
    //! Low Level API: The camera class for pylon GigE Vision camera devices
    /**
    This is the base class for pylon GigE Vision cameras providing access to camera parameters.
    \see \ref configuringcameras

    \tparam TCameraParams  The camera specific parameter class (auto generated from camera xml file)
    \ingroup Pylon_LowLevelApi

    \deprecated This class is deprecated in pylon 6.0. Please consider using CBaslerUniversalInstantCamera instead.
    */
    //**************************************************************************************************
    template<class TCameraParams>
    class CPylonGigECameraT : public CPylonGigEDeviceProxyT<TCameraParams>
    {
    public:
        typedef Pylon::CBaslerGigEDeviceInfo   DeviceInfo_t;    //!< \copybrief Pylon::CBaslerGigEDeviceInfo
        typedef Pylon::CPylonGigETLParams      TlParams_t;      //!< \copybrief Pylon::CPylonGigETLParams
        typedef Pylon::CPylonGigEStreamGrabber StreamGrabber_t; //!< \copybrief Pylon::CPylonGigEStreamGrabber
        typedef Pylon::CPylonGigEEventGrabber  EventGrabber_t;  //!< \copybrief Pylon::CPylonGigEEventGrabber

        //! The name of this device class, use this for enumeration
        static String_t DeviceClass()
        {
            return BaslerGigEDeviceClass;
        }

    public:
        //! \name Construction
        // \{

        /** \brief \copybrief Pylon::CPylonGigEDeviceProxyT::CPylonGigEDeviceProxyT()

        \copydetails Pylon::CPylonGigEDeviceProxyT::CPylonGigEDeviceProxyT()
        */
        CPylonGigECameraT()
        {
        };

              /** \brief \copybrief Pylon::CPylonGigEDeviceProxyT::CPylonGigEDeviceProxyT(IPylonDevice*,bool)

              \copydetails Pylon::CPylonGigEDeviceProxyT::CPylonGigEDeviceProxyT(IPylonDevice*,bool)
              */
        CPylonGigECameraT( IPylonDevice* pDevice, bool takeOwnership = true )
            : CPylonGigEDeviceProxyT<TCameraParams>( pDevice, takeOwnership )
        {
        }

        /** \brief \copybrief Pylon::CPylonGigEDeviceProxyT::~CPylonGigEDeviceProxyT()

        \copydetails Pylon::CPylonGigEDeviceProxyT::~CPylonGigEDeviceProxyT()
        */
        virtual ~CPylonGigECameraT()
        {
        }
        //\}
    };


} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // PYLON_GIGE_CAMERA_H
