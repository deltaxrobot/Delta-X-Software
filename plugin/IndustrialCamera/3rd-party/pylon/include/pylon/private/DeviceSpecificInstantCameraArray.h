//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Template for device specific instant camera array class.
*/

#ifndef INCLUDED_DEVICESPECIFICINSTANTCAMERAARRAY_H_4299977
#define INCLUDED_DEVICESPECIFICINSTANTCAMERAARRAY_H_4299977

#include <pylon/InstantCameraArray.h>

namespace Pylon
{
    /*!
    \class  CDeviceSpecificInstantCameraArrayT
    \brief  Implementation Detail: Header only implementation class for creating device specific Instant Camera Array classes.
    */
    template <typename CameraT>
    class CDeviceSpecificInstantCameraArrayT : public CInstantCameraArray
    {
    public:

        /*!
            \copybrief CInstantCameraArray::CInstantCameraArray()
            \copydetails CInstantCameraArray::CInstantCameraArray()
        */
        CDeviceSpecificInstantCameraArrayT()
        {
        }

        /*!
            \copybrief CInstantCameraArray::CInstantCameraArray( size_t)
            \copydetails CInstantCameraArray::CInstantCameraArray( size_t)
        */
        CDeviceSpecificInstantCameraArrayT( size_t numberOfCameras )
        {
            CInstantCameraArray::Initialize( numberOfCameras );
        }

        /*!
        \copybrief CInstantCameraArray::~CInstantCameraArray()
        \copydetails CInstantCameraArray::~CInstantCameraArray()
        */
        virtual ~CDeviceSpecificInstantCameraArrayT()
        {
            // Stop grabbing and free all cameras.
            Initialize( 0 );
        }

        /*!
            \copybrief Pylon::CInstantCameraArray::operator[]( size_t)
            \copydetails Pylon::CInstantCameraArray::operator[]( size_t)
        */
        virtual CameraT& operator[]( size_t index )
        {
            //Cast camera at the index to the device specific camera type and return the result of the cast.
            return dynamic_cast<CameraT&>(CInstantCameraArray::operator[]( index ));
        }

        /*!
            \copybrief Pylon::CInstantCameraArray::operator[]( size_t)
            \copydetails Pylon::CInstantCameraArray::operator[]( size_t)
        */
        virtual const CameraT& operator[]( size_t index ) const
        {
            //Cast to the specific camera type and return it.
            return dynamic_cast<const CameraT&>(CInstantCameraArray::operator[]( index ));
        }

        /*!
            \copybrief Pylon::CInstantCameraArray::RetrieveResult
            \copydetails Pylon::CInstantCameraArray::RetrieveResult
        */
        virtual bool RetrieveResult( unsigned int timeoutMs, typename CameraT::GrabResultPtr_t& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException )
        {
            //Release the grab result.
            grabResult.Release();
            // Use basic grab result.
            CGrabResultPtr grabResultLocal;
            // Call basic RetrieveResult.
            CInstantCameraArray::RetrieveResult( timeoutMs, grabResultLocal, timeoutHandling );
            // Convert.
            grabResult = grabResultLocal;
            // Returns true if grabResultLocal is valid and the conversion to the device specific grab result type has been successful.
            return grabResult.IsValid();
        }

        // Also available.
        using CInstantCameraArray::RetrieveResult;
    public:
        /// The type of the camera class in the array.
        typedef CameraT InstantCamera_t;
    protected:
        //Create a specific camera object.
        virtual CInstantCamera* CreateInstantCamera()
        {
            return new CameraT;
        }

        //Destroy a specific camera object.
        virtual void DestroyInstantCamera( CInstantCamera* pCamera )
        {
            delete pCamera;
        }
    };
}

#endif /* INCLUDED_DEVICESPECIFICINSTANTCAMERAARRAY_H_4299977 */
