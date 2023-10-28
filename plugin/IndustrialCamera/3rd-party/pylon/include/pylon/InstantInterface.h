//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  DV
//------------------------------------------------------------------------------

#pragma once

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>
#include <pylon/InterfaceInfo.h>
#include <pylon/DeviceInfo.h>
#include <pylon/TransportLayer.h>
#include <pylon/Interface.h>
#include <pylon/_BaslerUniversalInterfaceParams.h>


namespace Pylon
{
    /*!
    \class  CInstantInterface
    \brief  Provides convenient access to an interface. An interface is used to represent a frame grabber board, a network card, etc.

    <ul>
    <li> Establishes a single access point for accessing interface functionality.
    <li> Handles %Pylon interface lifetime.
    <li> Handles opening and closing of a %Pylon interface automatically.
    </ul>

    \note   Currently, this object type is mainly used for the pylon GenTL Consumer Transport Layer, e.g., for CoaXPress.
            All other pylon transport layers currently return one default interface.
    */
    template <typename T>
    class CInstantInterface : public T, public IInterface
    {
    public:
        /*!
        \brief Constructor. Creates a CInstantInterface object from a CDeviceInfo or CInterfaceInfo object.

        The following steps are taken:
        <ul>
        <li> The DeviceClass property is used to create the transport layer.
        <li> If the DeviceClass property is not available, the TlType property is used to create the first matching transport layer.
        <li> If the DeviceClass and TlType properties are not be available, an error will be thrown.
        <li> If the provided argument is of CInterfaceInfo type, this is used to create the interface.
        <li> If the provided argument is of CDeviceInfo type, use the InterfaceID property to create the interface.
        <li> If the above steps fail, the first interface is created.
        </ul>

        \error
            May throw an exception if the passed argument cannot be used to create an interface object.
        */
        CInstantInterface( const Pylon::CInfoBase& info ) : T()
            , m_pTransportLayer( NULL )
            , m_pInterface( NULL )
        {
            if (info.IsDeviceClassAvailable())
            {
                // find transport layer by DeviceClass
                CTlFactory& theFactory = CTlFactory::GetInstance();
                m_pTransportLayer = theFactory.CreateTl( info.GetDeviceClass() );
            }
            else if (info.IsTLTypeAvailable())
            {
                // find transport layer by TlType (choose first)
                TlInfoList_t tlList;
                CTlFactory& theFactory = Pylon::CTlFactory::GetInstance();
                theFactory.EnumerateTls( tlList );
                for (TlInfoList_t::const_iterator it = tlList.begin(); it != tlList.end(); ++it)
                {
                    const CTlInfo& tinfo = *it;
                    if (tinfo.GetTLType() == info.GetTLType())
                    {
                        m_pTransportLayer = theFactory.CreateTl( tinfo.GetDeviceClass() );
                        break;
                    }
                }
            }
            else
            {
                throw RUNTIME_EXCEPTION( "Not enough information to create the desired transport layer." );
            }

            if (m_pTransportLayer == NULL)
            {
                throw RUNTIME_EXCEPTION( "Cannot create transport layer." );
            }

            const CInterfaceInfo* pInterfaceInfo = dynamic_cast<const CInterfaceInfo*>(&info);
            const CDeviceInfo* pDeviceInfo = dynamic_cast<const CDeviceInfo*>(&info);
            if (pInterfaceInfo != NULL)
            {
                // parameter might be CInterfaceInfo
                m_pInterface = m_pTransportLayer->CreateInterface( *pInterfaceInfo );
            }
            else if ((pDeviceInfo != NULL) && (pDeviceInfo->IsInterfaceIDAvailable()))
            {
                // parameter might be CDeviceInfo
                CInterfaceInfo ii;
                ii.SetDeviceClass( info.GetDeviceClass() );
                ii.SetInterfaceID( pDeviceInfo->GetInterfaceID() );
                m_pInterface = m_pTransportLayer->CreateInterface( ii );
            }
            else
            {
                // open first interface
                InterfaceInfoList infoList;
                m_pTransportLayer->EnumerateInterfaces( infoList );
                m_pInterface = m_pTransportLayer->CreateInterface( infoList.at( 0 ) );
            }

            if (m_pInterface == NULL)
            {
                throw RUNTIME_EXCEPTION( "Cannot create interface." );
            }
        }

        /*!
        \brief Destructor. All created objects are destroyed correctly.
        */
        ~CInstantInterface()
        {
            if (m_pInterface != NULL)
            {
                if (IsOpen())
                {
                    Close();
                }

                m_pTransportLayer->DestroyInterface( m_pInterface );
            }

            if (m_pTransportLayer != NULL)
            {
                CTlFactory& theFactory = CTlFactory::GetInstance();
                theFactory.ReleaseTl( m_pTransportLayer );
            }
        }

        // IInterface

        /*!
        \brief Opens the attached %Pylon interface.

        This call is neccessary to work with all parameters.

        \post
            <ul>
            <li> The interface is opened.
            <li> The nodemap and parameters are available and accessable.
            </ul>

        \error
            May throw C++ exceptions.
        */
        virtual void Open()
        {
            m_pInterface->Open();
            this->_Initialize( m_pInterface->GetNodeMap() );
        }

        /*!
        \brief Checks if the interface is open.

        \note The 'open' status of an interface instance won't change even if an attached camera is used, e.g., opened or closed.

        \return Returns true if the interface is open.

        \error
            May throw C++ exceptions.
        */
        virtual bool IsOpen() const
        {
            bool isOpen = false;
            if (m_pInterface != NULL)
            {
                isOpen = m_pInterface->IsOpen();
            }
            return isOpen;
        }

        /*!
        \brief Closes an interface.

        \post
            <ul>
            <li> The interface is closed.
            <li> Any previously acquired objects and references have been deleted and must not be used any longer.
            </ul>

        \error
            May throw C++ exceptions.
        */
        virtual void Close()
        {
            if (m_pInterface != NULL)
            {
                m_pInterface->Close();
            }
            this->_Initialize( NULL );
        }

        /*!
        \brief Returns the interface info object storing information like the Interface ID property.

        This information is available at all times regardless of whether the interface is open or closed.

        \return A reference to the interface info object.

        \error
            May throw C++ exceptions.
        */
        virtual const CInterfaceInfo& GetInterfaceInfo() const
        {
            return m_pInterface->GetInterfaceInfo();
        }

        /*!
        \brief Returns the GenApi node map used for accessing parameters provided by the interface.

        \note The default interface object does not provide a node map.

        \note Interfaces will only provide a nodemap after calling Open().

        \return Returns the GenApi node map used for accessing parameters provided by the interface.
                If no parameters are available, NULL is returned.

        \error
            May throw C++ exceptions.
        */
        virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap()
        {
            return m_pInterface->GetNodeMap();
        }

        // IDeviceFactory

        /// @copydoc IDeviceFactory::EnumerateDevices(DeviceInfoList_t&,bool)
        /// \error
        ///     May throw C++ exceptions.
        virtual int EnumerateDevices( DeviceInfoList_t& list, bool addToList = false )
        {
            return m_pInterface->EnumerateDevices( list, addToList );
        }

        /// @copydoc IDeviceFactory::EnumerateDevices(DeviceInfoList_t&,const DeviceInfoList_t&,bool)
        /// \error
        ///     May throw C++ exceptions.
        virtual int EnumerateDevices( DeviceInfoList_t& list, const DeviceInfoList_t& filter, bool addToList = false )
        {
            return m_pInterface->EnumerateDevices( list, filter, addToList );
        }

        /// @copydoc IDeviceFactory::CreateDevice(const CDeviceInfo&)
        /// \error
        ///     May throw C++ exceptions.
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di )
        {
            return m_pInterface->CreateDevice( di );
        }

        /// @copydoc IDeviceFactory::CreateFirstDevice(const CDeviceInfo&)
        /// \error
        ///     May throw C++ exceptions.
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di = CDeviceInfo() )
        {
            return m_pInterface->CreateFirstDevice( di );
        }

        /// @copydoc IDeviceFactory::CreateDevice(const CDeviceInfo&,const StringList_t&)
        /// \error
        ///     May throw C++ exceptions.
        virtual IPylonDevice* CreateDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings )
        {
            return m_pInterface->CreateDevice( di, InjectedXmlStrings );
        }

        /// @copydoc IDeviceFactory::CreateFirstDevice(const CDeviceInfo&,const StringList_t&)
        /// \error
        ///     May throw C++ exceptions.
        virtual IPylonDevice* CreateFirstDevice( const CDeviceInfo& di, const StringList_t& InjectedXmlStrings )
        {
            return m_pInterface->CreateFirstDevice( di, InjectedXmlStrings );
        }

        /// @copydoc IDeviceFactory::CreateDevice(const String_t&)
        /// \error
        ///     May throw C++ exceptions.
        virtual IPylonDevice* CreateDevice( const String_t& s )
        {
            return m_pInterface->CreateDevice( s );
        }

        /// @copydoc IDeviceFactory::DestroyDevice(IPylonDevice*)
        /// \error
        ///     May throw C++ exceptions.
        virtual void DestroyDevice( IPylonDevice* pDevice )
        {
            return m_pInterface->DestroyDevice( pDevice );
        }

        /// @copydoc IDeviceFactory::IsDeviceAccessible(const CDeviceInfo&,AccessModeSet,EDeviceAccessiblityInfo*)
        /// \error
        ///     May throw C++ exceptions.
        virtual bool IsDeviceAccessible( const CDeviceInfo& deviceInfo, AccessModeSet mode = Control, EDeviceAccessiblityInfo* pAccessibilityInfo = NULL )
        {
            return m_pInterface->IsDeviceAccessible( deviceInfo, mode, pAccessibilityInfo );
        }

    private:
        // Do not use
        CInstantInterface();

        ITransportLayer* m_pTransportLayer;
        IInterface* m_pInterface;
    };

    typedef CInstantInterface<Basler_UniversalInterfaceParams::CUniversalInterfaceParams_Params> CUniversalInstantInterface;

} // namespace Pylon

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
