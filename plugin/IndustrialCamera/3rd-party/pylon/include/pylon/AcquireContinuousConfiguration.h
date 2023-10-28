//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief An instant camera configuration for free-running continuous acquisition.
    This  instant camera configuration is provided as header-only file. The code
    can be copied and modified for creating own configuration classes.
*/

#ifndef INCLUDED_ACQUIRECONTINUOUSCONFIGURATION_H_7346765
#define INCLUDED_ACQUIRECONTINUOUSCONFIGURATION_H_7346765

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/InstantCamera.h>
#include <pylon/ParameterIncludes.h>
#include <pylon/ConfigurationHelper.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /*!
    \class  CAcquireContinuousConfiguration
    \brief Changes the configuration of the camera to free-running continuous acquisition.

        The \c CAcquireContinuousConfiguration is the default configuration of the Instant Camera class.
        The CAcquireContinuousConfiguration is automatically registered when an Instant Camera object is created.

        This instant camera configuration is provided as header-only file. The code
        can be copied and modified for creating own configuration classes.
    */
    class CAcquireContinuousConfiguration : public CConfigurationEventHandler
    {
    public:
        /// Destructor
        virtual ~CAcquireContinuousConfiguration()
        {
        }

        /// Apply acquire continuous configuration.
        static void ApplyConfiguration( GENAPI_NAMESPACE::INodeMap& nodemap )
        {
            using namespace GENAPI_NAMESPACE;

            //Disable all trigger types.
            CConfigurationHelper::DisableAllTriggers( nodemap );

            //Disable compression mode.
            CConfigurationHelper::DisableCompression( nodemap );

            //Disable GenDC streaming.
            CConfigurationHelper::DisableGenDC( nodemap );

            // Set image component.
            CConfigurationHelper::SelectRangeComponent( nodemap );

            //Set acquisition mode.
            CEnumParameter( nodemap, "AcquisitionMode" ).SetValue( "Continuous" );
        }


        //Set basic camera settings.
        virtual void OnOpened( CInstantCamera& camera )
        {
            try
            {
                ApplyConfiguration( camera.GetNodeMap() );
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
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_ACQUIRECONTINUOUSCONFIGURATION_H_7346765 */
