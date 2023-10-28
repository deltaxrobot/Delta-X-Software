//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of CTlFactory class
*/

#ifndef __TLFACTORY_H__
#define __TLFACTORY_H__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>
#include <pylon/TlInfo.h>
#include <pylon/TransportLayer.h>
#include <pylon/DeviceFactory.h>


namespace Pylon
{
    // forwards
    class CSimpleMutex;
    class CTlInfo;
    interface ITransportLayer;
    interface IDeviceFactory;
    class TlMap;
    class ImplicitTlRefs;

    //------------------------------------------------------------------------
    // class CTlFactory
    //------------------------------------------------------------------------
    /*!
        \ingroup Pylon_TransportLayer
        \brief the Transport Layer Factory

        Creates, Destroys and Enumerates transport layers as well as
        their devices.
    */
    class PYLONBASE_API CTlFactory : public IDeviceFactory
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// Retrieve the transport layer factory singleton.
        /// Throws an exception when Pylon::PylonInitialize() has not been called before.
        static CTlFactory& GetInstance();

        /**
            \brief Retrieves a list of available transport layers.

            The list contains Pylon::CTlInfo objects used for transport layer creation.

            \param list List to be filled with transport layer info objects.
            \return Number of transport layers found.
        */
        int EnumerateTls( TlInfoList_t& list );

        /**
            \brief Creates a transport layer object from a transport layer info object.

            This method accepts a transport layer info object which can be obtained by calling EnumerateTls.
            For each successfully returned transport layer object, you must call ReleaseTl to free the transport layer object.

            If the creation fails, a GenApi::GenericException will be thrown.

            \param ti Transport layer info object specifying which transport layer to create.
            \return Pointer to the transport layer object created. If no matching transport layer could be found, NULL will be returned.
        */
        ITransportLayer* CreateTl( const CTlInfo& ti );

        /**
            \brief Creates a transport layer object from a device class string.

            This method accepts a device class string. You can see a list of available device classes in the DeviceClass.h file.
            For each successfully returned transport layer object, you must call ReleaseTl to free the transport layer object.

            If the creation fails, a GenApi::GenericException will be thrown.

            \param deviceClass Transport layer info object specifying which transport layer to create.
            \return Pointer to the transport layer object created. If no matching transport layer could be found, NULL will be returned.
        */
        ITransportLayer* CreateTl( const String_t& deviceClass );

        /**
            \brief Releases a transport layer object created by a call to CreateTl().

            For each successfully returned transport layer object from any CreateTl() function,
            you must call this function to free the transport layer object.

            \param pTl Pointer to the transport layer object to be released.
        */
        void ReleaseTl( const ITransportLayer* pTl );

        // returns a list of available devices, see IDeviceFactory for more information
        virtual int EnumerateDevices( DeviceInfoList_t&, bool addToList = false );

        // returns a list of available devices that match the filter, see IDeviceFactory for more information
        virtual int EnumerateDevices( DeviceInfoList_t& list, const DeviceInfoList_t& filter, bool addToList = false );

        // creates a device from a device info object, see IDeviceFactory for more information
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di );

        // creates first found device from a device info object, see IDeviceFactory for more information
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di = CDeviceInfo() );

        // creates a device from a device info object, injecting additional GenICam XML definition strings
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings );

        // creates first found device from a device info object, injecting additional GenICam XML definition strings
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings );

        // Use CreateDevice and pass a CDeviceInfo object containing the full name as a property.
        // example: IPylonDevice* device = TlFactory.CreateDevice(CDeviceInfo().SetFullName(fullname));
        // creates a device that matches its full name (i.e., as returned by CDeviceInfo::GetFullName).
        virtual IPylonDevice* CreateDevice( const String_t& );

        // destroys a device
        virtual void DestroyDevice( IPylonDevice* );

        // implements IDeviceFactory::IsDeviceAccessible
        virtual bool IsDeviceAccessible( const CDeviceInfo& deviceInfo, AccessModeSet mode = Control, EDeviceAccessiblityInfo* pAccessibilityInfo = NULL );

    protected:
        void InternalEnumerateTls( TlInfoList_t& );
        virtual IPylonDevice* InternalCreateDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings, bool allowAnyFirstFound );

        TlMap* m_pTls;
        ImplicitTlRefs* m_pImplicitlyCreatedTls;
        CSimpleMutex* m_pMemberLock;

    private:
        void Terminate( void );
        void checkInitialized( void ); // fires an exception when Terminate() already has been called

        CTlFactory( void );
        CTlFactory& operator=( const CTlFactory& );
        CTlFactory( const CTlFactory& );

        virtual ~CTlFactory( void );

        friend void Pylon::PylonInitialize();
        friend void Pylon::PylonTerminate( bool );
        friend void Pylon::SetProperty( int propertyId, const void* pData, size_t size );
        friend void Pylon::GetProperty( int propertyId, void* pData, size_t* pSize );
    };

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* __TLFACTORY_H__ */
