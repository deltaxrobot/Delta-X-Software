//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief    Low Level API: Definition of IPylonDevice
*/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <Base/GCException.h>
#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>
#include <pylon/WaitObject.h>
#include <pylon/WaitObjects.h>  // for backward compatibility reasons
#include <pylon/DeviceInfo.h>
#include <pylon/EventAdapter.h>
#include <pylon/Callback.h>
#include <pylon/DeviceAccessMode.h>

namespace Pylon
{

    interface IStreamGrabber;
    interface IEventGrabber;
    interface IChunkParser;
    interface ISelfReliantChunkParser;
    interface IPylonDevice;

    /// callback type with a IPylonDevice as parameter
    typedef Pylon::Callback1<IPylonDevice*> DeviceCallback;
    /// opaque device callback object
    typedef void* DeviceCallbackHandle;

    class CDeviceInfo;
    // -------------------------------------------------------------------------
    // interface IDevice
    // -------------------------------------------------------------------------
    /*! \interface IDevice
        \brief Low Level API: The interface implemented by all device objects
        \ingroup Pylon_LowLevelApi
    */
    interface PUBLIC_INTERFACE IDevice
    {

        /// Opens a device
        /**
          The open method initializes all involved drivers and establishes a connection
          to the device.

          A device may support different access modes, e.g. EDeviceAccessMode::Exclusive providing
          an exclusive access to the device.

          \param mode The desired device access mode
         */
        virtual void Open( AccessModeSet mode = (Stream | Control | Event) ) = 0;

        /// Closes a device
        /**
            The close method closes all involved drivers and an existing connection to
            the device will be released. Other applications now can access the device.
         */
        virtual void Close() = 0;

        /// Checks if a device already is opened
        /**
            \return true, when the device already has been opened by the calling application.

            \note When a device has been opened an application A, IsOpen() will return false
            when called by an application B not having called the device's open method.
            */
        virtual bool IsOpen() const = 0;

        /// Returns the access mode used to open the device
        virtual AccessModeSet AccessMode( void ) const = 0;

        /** \brief Returns the device info object storing information like
          the device's name.

          \return A reference to the device info object used to create the device by a device factory
          */
        virtual const CDeviceInfo& GetDeviceInfo() const = 0;
    };

    // ---------------------------------------------------------------------
    // interface IPylonDevice
    // ---------------------------------------------------------------------
    /** \interface IPylonDevice
        \brief Low Level API: Interface for camera objects
        \ingroup Pylon_LowLevelApi
    */
    interface PUBLIC_INTERFACE IPylonDevice : public IDevice
    {
    public:

        /// Returns the number of stream grabbers the camera object provides
        virtual uint32_t GetNumStreamGrabberChannels() const = 0;

        /// Returns a pointer to a stream grabber
        /**
            Stream grabbers (IStreamGrabber) are the objects used to grab images
            from a camera device. A camera device might be able to send image data
            over more than one logical channel called stream. A stream grabber grabs
            data from one single stream.

            \param index The number of the grabber to return
            \return A pointer to a stream grabber, NULL if index is out of range
        */
        virtual IStreamGrabber* GetStreamGrabber( uint32_t index ) = 0;

        /// Returns a pointer to an event grabber
        /**
            Event grabbers are used to handle events sent from a camera device.
            */
        virtual IEventGrabber* GetEventGrabber() = 0;

        /// Returns the set of camera parameters.
        /**
          \return Pointer to the GenApi node map holding the parameters
          */
        virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap() = 0;

        /// Returns the set of camera related transport layer parameters.
        /**
            \return Pointer to the GenApi node holding the transport layer parameter. If
            there are no transport layer parameters for the device, NULL is returned.
            */
        virtual GENAPI_NAMESPACE::INodeMap* GetTLNodeMap() = 0;

        /** \brief Creates a chunk parser used to update those camera object members
            reflecting the content of additional data chunks appended to the image data.

            \return Pointer to the created chunk parser

            \note Don't try to delete a chunk parser pointer by calling free or delete. Instead,
            use the DestroyChunkParser() method
        */
        virtual Pylon::IChunkParser* CreateChunkParser() = 0;

        /// Deletes a chunk parser
        /**
        \param pChunkParser Pointer to the chunk parser to be deleted
        */
        virtual void DestroyChunkParser( Pylon::IChunkParser* pChunkParser ) = 0;

        /*!
        Creates an Event adapter
        */
        virtual IEventAdapter* CreateEventAdapter() = 0;

        /*!
        Deletes an Event adapter
        */
        virtual void DestroyEventAdapter( IEventAdapter* ) = 0;

        /*!
        Creates a a self-reliant chunk parser, returns NULL if not supported
        */
        virtual ISelfReliantChunkParser* CreateSelfReliantChunkParser() = 0;

        /*!
        Deletes a self-reliant chunk parser
        */
        virtual void DestroySelfReliantChunkParser( ISelfReliantChunkParser* ) = 0;

        /// Registers a surprise removal callback object
        /**
            \param d reference to a device callback object
            \return A handle which must be used to deregister a callback
            It is recommended to use one of the RegisterRemovalCallback() helper functions
            to register a callback.

            Example how to register a C function
            \code
                void MyRemovalCallback( Pylon::IPylonDevice* pDevice)
                {
                    // handle removal
                }

                DeviceCallbackHandle h =
                    Pylon::RegisterRemovalCallback( m_pCamera, &MyRemovalCallback);
            \endcode

            Example how to register a class member function
            \code
                class C
                {
                    void MyRemovalCallback( Pylon::IPylonDevice* pDevice )
                    {
                      // handle removal
                    }
                } c;

                DeviceCallbackHandle h =
                    Pylon::RegisterRemovalCallback( m_pCamera, c, &C::MyRemovalCallback);
            \endcode
        */
        virtual DeviceCallbackHandle RegisterRemovalCallback( DeviceCallback& d ) = 0;

        /// Deregisters a surprise removal callback object
        /*!
        \param h Handle of the callback to be removed
        */
        virtual bool DeregisterRemovalCallback( DeviceCallbackHandle h ) = 0;

    };


#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning( disable : 4239 ) // nonstandard extension used
#endif
    /**
    \brief Low Level API: Register a C-function as a removal callback
    \ingroup Pylon_LowLevelApi
    \see Pylon::IPylonDevice::RegisterRemovalCallback()
    \param pDevice Pointer to the device that generates callbacks
    \param f The function to be called
    */
    template<class Function>
    DeviceCallbackHandle RegisterRemovalCallback( IPylonDevice* pDevice, Function f )
    {
        if (NULL == pDevice)
            throw RUNTIME_EXCEPTION( "Failed to register removal callback, invalid device object." );
        DeviceCallback cb( make_FunctionCallback<Function, Pylon::Callback1<IPylonDevice*>, IPylonDevice* >( f ) );
        return pDevice->RegisterRemovalCallback( cb );
    }

    /**
    \brief Low Level API: Register a C++-member function as removal callback
    \ingroup Pylon_LowLevelApi
    \see Pylon::IPylonDevice::RegisterRemovalCallback()
    \param pDevice Pointer to the device that generates callbacks
    \param c The client object
    \param m The member function to be called
    */
    template<class Client, class Member>
    DeviceCallbackHandle RegisterRemovalCallback( IPylonDevice* pDevice, Client& c, Member m )
    {
        if (NULL == pDevice)
            throw RUNTIME_EXCEPTION( "Failed to register removal callback, invalid device object." );
        DeviceCallback x( make_MemberFunctionCallback<Client, Member, DeviceCallback, IPylonDevice*>( c, m ) );
        return pDevice->RegisterRemovalCallback( x );
    }
#ifdef _MSC_VER
#pragma warning ( pop )
#endif


}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__DEVICE_H__
