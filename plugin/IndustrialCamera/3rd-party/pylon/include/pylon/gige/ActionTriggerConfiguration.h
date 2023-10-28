//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author: Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief An instant camera configuration for triggering via GigE Vision action commands.
       This  instant camera configuration is provided as header-only file. The code
       can be copied and modified for creating own configuration classes.
*/

#ifndef INCLUDED_ACTIONTRIGGERCONFIGURATION_H_4655834
#define INCLUDED_ACTIONTRIGGERCONFIGURATION_H_4655834

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/InstantCamera.h>
#include <pylon/ParameterIncludes.h>
#include <pylon/ConfigurationHelper.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiUniversal
     * @{
     */
    // Arbitrarily chosen constants for camera selection. For an explanation and
    // tips see the "Multi-Camera Applications and GigE Vision 2.0" White paper
    const uint32_t AllGroupMask( 0xffffffff );  // camera will respond to any mask other than 0

    /*!
    \class  CActionTriggerConfiguration
    \brief  Changes the configuration of the camera so that it is triggered by the first
    available action command.

    This configuration enables the frame start trigger and disables all other trigger
    types. As trigger source the first available action command is selected, i.e., the
    camera will be triggered by action commands issued by the application.

    In contrast to using the software trigger triggering with action commands allows
    to trigger multiple cameras simultaneously.

    Either register this configuration as an Instant Camera's event handler or apply
    the configuration to the node map of an opened pylon device using one of the
    ApplyConfiguration methods.

    The %CActionTriggerConfiguration is provided as header-only file.
    The code can be copied and modified for creating own configuration classes.
    */
    class CActionTriggerConfiguration : public CConfigurationEventHandler
    {
    public:
        struct ActionParameter
        {
            uint32_t DeviceKey;
            uint32_t GroupKey;
            uint32_t GroupMask;

            ActionParameter()
                : DeviceKey( 0 ), GroupKey( 0 ), GroupMask( AllGroupMask )
            {
            }
            ActionParameter( uint32_t DeviceKey_, uint32_t GroupKey_, uint32_t GroupMask_ = AllGroupMask )
                : DeviceKey( DeviceKey_ ), GroupKey( GroupKey_ ), GroupMask( GroupMask_ )
            {
            }
        };

        // constructors and assignment
        CActionTriggerConfiguration( uint32_t DeviceKey, uint32_t GroupKey, uint32_t GroupMask = AllGroupMask ) :
            m_Parameter( DeviceKey, GroupKey, GroupMask )
        {
        }
        CActionTriggerConfiguration( const ActionParameter& p )
            : m_Parameter( p )
        {
        }
        CActionTriggerConfiguration( const CActionTriggerConfiguration& other ) : CConfigurationEventHandler( other )
        {
            m_Parameter = other.m_Parameter;
        }
        CActionTriggerConfiguration& operator=( const CActionTriggerConfiguration& rhs )
        {
            m_Parameter = rhs.m_Parameter;
            return *this;
        }
        // destructor
        virtual ~CActionTriggerConfiguration()
        {
        }

        /// Apply action trigger configuration to a given camera device node map.
        static void ApplyConfiguration( GENAPI_NAMESPACE::INodeMap& deviceNodeMap, const ActionParameter& p )
        {
            ApplyConfiguration( deviceNodeMap, p.DeviceKey, p.GroupKey, p.GroupMask );
        }

        /// Apply action trigger configuration to a given camera device node map.
        static void ApplyConfiguration( GENAPI_NAMESPACE::INodeMap& deviceNodeMap, uint32_t DeviceKey, uint32_t GroupKey, uint32_t GroupMask = AllGroupMask )
        {
            using namespace GenApi;

            //Disable compression mode.
            CConfigurationHelper::DisableCompression( deviceNodeMap );

            //Disable GenDC streaming.
            CConfigurationHelper::DisableGenDC( deviceNodeMap );

            //Select image component.
            CConfigurationHelper::SelectRangeComponent( deviceNodeMap );

            //////////////////////////////////////////////////////////////////
            // get the nodes we need and do a check before we start changing the camera configuration

            CIntegerParameter actionDeviceKey( deviceNodeMap, "ActionDeviceKey" );
            CIntegerParameter actionGroupKey( deviceNodeMap, "ActionGroupKey" );
            CIntegerParameter actionGroupMask( deviceNodeMap, "ActionGroupMask" );
            CIntegerParameter actionSelector( deviceNodeMap, "ActionSelector" );

            if (!actionDeviceKey.IsWritable() ||
                 !actionGroupKey.IsWritable() ||
                 !actionGroupMask.IsWritable() ||
                 !actionSelector.IsWritable())
            {
                throw RUNTIME_EXCEPTION( "Device doesn't support action commands. The ActionCommand features are not writable." );
            }

            // Get required enumerations to configure triggering on action commands
            CEnumParameter triggerSelector( deviceNodeMap, "TriggerSelector" );
            CEnumParameter triggerSource( deviceNodeMap, "TriggerSource" );
            CEnumParameter triggerMode( deviceNodeMap, "TriggerMode" );

            // to use triggering we need to switch Continuous Grab
            CEnumParameter acquisitionMode( deviceNodeMap, "AcquisitionMode" );

            if (!triggerSelector.IsWritable() ||
                 !triggerSource.IsWritable() ||
                 !triggerMode.IsWritable())
            {
                throw RUNTIME_EXCEPTION( "Trigger nodes not writable" );
            }

            // Check the available camera trigger mode(s)
            const String_t triggerName( "FrameStart" );
            if (!triggerSelector.CanSetValue( triggerName ))
            {
                throw RUNTIME_EXCEPTION( "Device does not support \"FrameStart\"" );
            }


            if (!acquisitionMode.IsWritable())
            {
                throw RUNTIME_EXCEPTION( "Acquisition mode not writable" );
            }


            //////////////////////////////////////////////////////////////////
            // start changing the camera configuration

            // Select the first action (usually "Action 1")
            actionSelector.SetToMinimum();
            String_t selectedAction = GenICam::gcstring( "Action" ) += actionSelector.ToString();


            actionDeviceKey.SetValue( DeviceKey );
            actionGroupKey.SetValue( GroupKey );
            actionGroupMask.SetValue( GroupMask );

            // The goal is to issue a trigger for each single frame. Configure the
            // corresponding trigger mode, disable all other trigger types.
            {

                // Get all settable enumeration entries of Trigger Selector.
                StringList_t triggerSelectorEntries;
                triggerSelector.GetSettableValues( triggerSelectorEntries );

                const String_t originalSelectorValue = triggerSelector.GetValue();

                // Iterate through all available trigger modes, configure the frame start
                // trigger, disable all other trigger types.
                for (StringList_t::const_iterator it = triggerSelectorEntries.begin(); it != triggerSelectorEntries.end(); ++it)
                {
                    // Set Trigger Mode to off if the trigger is available.
                    triggerSelector.SetValue( *it );
                    if (triggerName == *it)
                    {
                        // Activate trigger.
                        triggerMode.SetValue( "On" );

                        // Set the trigger source to the selected action.
                        triggerSource.SetValue( selectedAction );
                    }
                    else
                    {
                        triggerMode.TrySetValue( "Off" );
                    }
                }

                // reset to old value
                triggerSelector.SetValue( originalSelectorValue );
            }

            // Set acquisition mode.
            acquisitionMode.SetValue( "Continuous" );
        }

    private:
        // Apply settings when the camera is opened.
        /* virtual */ void OnOpened( CInstantCamera& camera )
        {
            try
            {
                ApplyConfiguration( camera.GetNodeMap(), m_Parameter );
            }
            catch (const GenericException& e)
            {
                throw RUNTIME_EXCEPTION( "Could not apply configuration. Pylon::GenericException caught in OnOpened method msg=%hs", e.what() );
            }
            catch (const std::exception& e)
            {
                throw RUNTIME_EXCEPTION( "Could not apply configuration. std::exception caught in OnOpened method msg=%hs", e.what() );
            }
            catch (...)
            {
                throw RUNTIME_EXCEPTION( "Could not apply configuration. Unknown exception caught in OnOpened method." );
            }
        }

    private:
        ActionParameter m_Parameter;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_ACTIONTRIGGERCONFIGURATION_H_4655834 */
