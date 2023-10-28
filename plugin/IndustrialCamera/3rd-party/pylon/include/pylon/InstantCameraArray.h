//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
\file
\brief Contains the instant camera array class which supports grabbing with multiple camera devices.
*/

#ifndef INCLUDED_INSTANTCAMERAARRAY_H_3108332
#define INCLUDED_INSTANTCAMERAARRAY_H_3108332

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/InstantCamera.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /*!
    \class  CInstantCameraArray
    \brief Supports grabbing with multiple camera devices.

    \threading
        The CInstantCameraArray class is not thread-safe.
    */

    class PYLONBASE_API CInstantCameraArray
    {
    public:
        //Creation and life time------------------------------------------------

        /*!
        \brief Creates an Instant Camera Array of size 0.

        Initialize() can be used to adjust the size of the array.

        \error
            Does not throw C++ exceptions.
        */
        CInstantCameraArray();

        /*!
        \brief Creates an Instant Camera Array.

        Calls Initialize() to adjust the size of the array.

        \param[in]  numberOfCameras The number of cameras the array shall hold. Can be 0.

        The index operator can be used to access the individual cameras
        for attaching a %Pylon Device or for configuration.

        Example:
        \code
        // Create an array of two devices.
        CInstantCamera array(2);
        // Attach Pylon Devices.
        array[0].Attach( pDevice1);
        array[1].Attach( pDevice2);
        \endcode

        \error
            Does not throw C++ exceptions, except when memory allocation fails.
        */
        CInstantCameraArray( size_t numberOfCameras );


        /*!
        \brief Destroys the Instant Camera Array.

        If a grab is in progress, it is stopped by calling StopGrabbing().

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CInstantCameraArray();


        /*!
        \brief Initializes the array.

        <ul>
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> All cameras of the array are destroyed.
        <li> A new set of cameras is created. No %Pylon Devices are attached.
        <li> The camera context values are set to the index of the camera in the array using CInstantCamera::SetCameraContext.
        </ul>

        The index operator can be used to access the individual cameras
        for attaching a %Pylon Device or for configuration.

        \param[in]  numberOfCameras The number of cameras the array shall hold.

        \error
            Does not throw C++ exceptions, except when memory allocation fails.
        */
        virtual void Initialize( size_t numberOfCameras );


        /*!
        \brief Returns the attachment state of cameras in the array.

        \return True if all cameras in the array have a %Pylon Device attached. False is returned if the size of the array is 0.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsPylonDeviceAttached() const;


        /*!
        \brief Returns the connection state of the camera devices used by the Instant Cameras in the array.

        The device removal is only detected if the Instant Cameras and therefore the attached %Pylon Devices are open.

        The %Pylon Device is not operable after this event.
        After it is made sure that no access to the %Pylon Device or any of its node maps is made anymore
        the %Pylon Device should be destroyed using InstantCamera::DeviceDestroy().
        The access to the %Pylon Device can be protected using the lock provided by GetLock(), e.g. when accessing parameters.

        \return True if the camera device removal from the PC for any camera in the array has been detected.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsCameraDeviceRemoved() const;


        /*!
        \brief  Destroys the %Pylon Devices that are attached to the Instant Cameras in the array.

        \attention The node maps, e.g. the camera node map, of the attached %Pylon Device must not be accessed anymore while destroying the %Pylon Device.

        <ul>
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> DestroyDevice is called for all cameras. See CInstantCamera::DestroyDevice() for more information.
        </ul>

        \post
            No %Pylon Devices are attached to the cameras in the array.

        \error
            Does not throw C++ exceptions.
        */
        virtual void DestroyDevice();


        /*!
        \brief  Detaches all %Pylon Devices that are attached to the Instant Cameras in the array.

        <ul>
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> DetachDevice is called for all cameras, see CInstantCamera::DetachDevice() for more information.
        </ul>

        \post
        <ul>
        <li> No %Pylon Devices are attached to the cameras in the array.
        <li> The ownership of the %Pylon Devices goes to the caller who is responsible for destroying the %Pylon Devices.
        </ul>

        \error
            Does not throw C++ exceptions.
        */
        virtual void DetachDevice();


        //Control opening and closing of the device-----------------------------

        /*!
        \brief Opens all cameras in the array.

        Open is called for all cameras. See CInstantCamera::Open() for more information.

        \pre
        <ul>
        <li> The size of the array is larger than 0.
        <li> All devices are attached.
        </ul>

        \post
            The cameras are open.

        \error
            If one camera throws an exception, all cameras are closed by calling Close().
        */
        virtual void Open();


        /*!
        \brief Returns the open state of the cameras in the array.
        \error Does not throw C++ exceptions.
        \return Returns true if all cameras in the array are open. False is returned if the size of the array is 0.
        */
        virtual bool IsOpen() const;


        /*!
        \brief Closes all cameras in the array.

        <ul>
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> Close is called for all cameras, see CInstantCamera::Close() for more information.
        </ul>

        \post
            All cameras in the array are closed.

        \error
            Does not throw C++ exceptions.
        */
        virtual void Close();


        /*!
        \brief Returns the size of the array.

        \error
            Does not throw C++ exceptions.
        */
        virtual size_t GetSize() const;


        /*!
        \brief Retrieve a camera by index

        \pre
            The index is smaller than GetSize();

        \error
            Throws an exception if the index is not valid.
        */
        virtual CInstantCamera& operator[]( size_t index );


        /*!
        \brief Retrieve a camera by index

        \pre
            The index is smaller than GetSize();

        \error
            Throws an exception if the index is not valid.
        */
        virtual const CInstantCamera& operator[]( size_t index ) const;

        //Grab -----------------------------------------------------------------

        /*!
        \brief Starts the grabbing of images for all cameras.

        <ul>
        <li> StartGrabbing is called for all cameras with the provided parameters, see CInstantCamera::StartGrabbing() for more information.
        <li> The grabbing is started.
        <li> The starting position for retrieving results is set to the first camera.
        </ul>

        \param[in]  strategy  The grab strategy, see Pylon::InstantCamera::EStrategy for more information.
        \param[in]  grabLoopType Indicates using the internal grab thread of the camera.

        \pre
            <ul>
            <li> The size of the array is larger than 0.
            <li> All devices are attached.
            <li> The grabbing is stopped.
            <li> The preconditions for calling StartGrabbing() are met for every camera in the array.
            </ul>

        \post
            The grabbing is started.

        \error
            The camera objects may throw an exception. The grabbing is stopped calling StopGrabbing() in this case.
        */
        virtual void StartGrabbing( EGrabStrategy strategy = GrabStrategy_OneByOne, EGrabLoop grabLoopType = GrabLoop_ProvidedByUser );


        /*!
        \brief Retrieves a grab result according to the strategy, waits if it is not yet available

        <ul>
        <li> The content of the passed grab result is released.
        <li> If the grabbing is not started, the method returns immediately false.
        <li> If GrabStrategy_UpcomingImage strategy: RetrieveResult is called for a camera. Cameras are processed using a round-robin strategy.
        <li> If GrabStrategy_OneByOne, GrabStrategy_LatestImageOnly or GrabStrategy_LatestImages strategy: Pending images or camera events are retrieved. Cameras are processed using a round-robin strategy.
        <li> If GrabStrategy_OneByOne, GrabStrategy_LatestImageOnly or GrabStrategy_LatestImages strategy: Wait for a grab result if it is not yet available. Camera events are handled.
        </ul>

        The camera array index is assigned to the context value of the instant camera when Initialize() is called.
        This context value is attached to the result when the result is retrieved and can be obtained using the grab result method GrabResultData::GetCameraContext().
        The context value can be used to associate the result with the camera from where it originated.

        \param[in]  timeoutMs  A timeout value in ms for waiting for a grab result, or the INFINITE value.
        \param[out] grabResult  Receives the grab result.
        \param[in]  timeoutHandling  If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.

        \return True if the call successfully retrieved a grab result, false otherwise.

        \pre
            The preconditions for calling StartGrabbing() are met for every camera in the array.

        \post
        <ul>
        <li> If successful, one image is removed from the output queue of a camera and is returned in the grabResult parameter.
        <li> If not successful, an empty grab result is returned in the grabResult parameter.
        </ul>

        \error
            The Instant Camera Array object is still valid after error. The grabbing is stopped by calling StopGrabbing() if an exception is thrown.
        */
        virtual bool RetrieveResult( unsigned int timeoutMs, CGrabResultPtr& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );


        /*!
        \brief Stops the grabbing of images.

        The grabbing is stopped.
        StopGrabbing is called for all cameras. See CInstantCamera::StopGrabbing() for more information.

        \post
            The grabbing is stopped.

        \error
            Does not throw C++ exceptions.

        \threading
            Can be called while one other thread is polling RetrieveResult() in a IsGrabbing()/RetrieveResult() loop
            to stop grabbing.
        */
        virtual void StopGrabbing();


        /*!
        \brief Returns state of grabbing.

        The camera array is grabbing after a successful call to StartGrabbing() until StopGrabbing() has been called.

        \return Returns true if still grabbing.

        \error
            Does not throw C++ exceptions.
        */
        virtual bool IsGrabbing() const;

    public:
        /// The type of the camera class in the array.
        typedef CInstantCamera InstantCamera_t;

    protected:
        //Functionality that can be provided by specializing class--------------

        /*
        \brief Creates an instance of an instant camera class.

        The method is called from Initialize() method.

        \return Returns pointer to the created class.

        \error
            Does not throw C++ exceptions, except when memory allocation fails.
        */
        virtual CInstantCamera* CreateInstantCamera();


        /*
        \brief Destroys an instance of an instant camera class.

        The method is called from Initialize() method.
        Cameras are destroyed in the reverse order they are created.

        \param[in] pCamera Camera instance to destroy.

        \error
            Does not throw C++ exceptions.
        */
        virtual void DestroyInstantCamera( CInstantCamera* pCamera );

    private:
        // The camera array object can not be copied.
        CInstantCameraArray( const CInstantCameraArray& );
        // The camera array object can not be copied.
        void operator = ( const CInstantCameraArray& );

        class CInstantCameraArrayImpl;
        CInstantCameraArrayImpl* m_pImpl;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_INSTANTCAMERAARRAY_H_3108332 */
