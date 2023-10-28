//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a camera class establishing convenient access to a camera device.
*/

#ifndef INCLUDED_INSTANTCAMERA_H_08725703
#define INCLUDED_INSTANTCAMERA_H_08725703

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>
#include <pylon/ImageEventHandler.h>
#include <pylon/ConfigurationEventHandler.h>
#include <pylon/CameraEventHandler.h>
#include <pylon/BufferFactory.h>
#include <pylon/GrabResultPtr.h>
#include <pylon/DeviceInfo.h>
#include <pylon/WaitObject.h>
#include <pylon/Device.h>
#include <pylon/SfncVersion.h>

namespace Pylon
{
    /// Internal use only.
    class IInstantCameraExtensions;
}

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4275 ) // Class needs to have a dll interface to be used by clients of the class.
#endif

#include <pylon/_InstantCameraParams.h>

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

     /// Lists the possible grab strategies.
    enum EGrabStrategy
    {
        GrabStrategy_OneByOne,        //!< The images are processed in the order of their arrival. This is the default grab strategy.

        GrabStrategy_LatestImageOnly, //!< Only the latest image is kept in the output queue, all other grabbed images are skipped.
                                      //!< If no image is in the output queue when retrieving an image with \c CInstantCamera::RetrieveResult(),
                                      //!< the processing waits for the upcoming image.

        GrabStrategy_LatestImages,    //!< This strategy can be used to grab images while keeping only the latest images. If the application does not
                                      //!< retrieve all images in time, all other grabbed images are skipped. The CInstantCamera::OutputQueueSize parameter can be used to
                                      //!< control how many images can be queued in the output queue. When setting the output queue size to 1, this strategy is equivalent to
                                      //!< GrabStrategy_LatestImageOnly grab strategy. When setting the output queue size to CInstantCamera::MaxNumBuffer,
                                      //!< this strategy is equivalent to GrabStrategy_OneByOne.

        GrabStrategy_UpcomingImage    //!< The input buffer queue is kept empty. This prevents grabbing.
                                      //!< However, when retrieving an image with a call to the \c CInstantCamera::RetrieveResult() method
                                      //!< a buffer is queued into the input queue and then the call waits for the upcoming image.
                                      //!< The buffer is removed from the queue on timeout.
                                      //!< Hence after the call to the \c CInstantCamera::RetrieveResult() method the input buffer queue is empty again.
                                      //!< The upcoming image grab strategy cannot be used together with USB or GenTL-based camera devices. See the advanced topics section of
                                      //!< the pylon Programmer's Guide for more information.
    };

    /// Defines who deletes a passed object if it is not needed anymore.
    enum ECleanup
    {
        Cleanup_None,                 //!< The caller is responsible for deleting the passed object. The object needs to be detached or deregistered before deletion.
        Cleanup_Delete                //!< The passed object is deleted if it is not needed anymore.
    };

    /// Defines the use of an additional grab loop thread.
    enum EGrabLoop
    {
        GrabLoop_ProvidedByInstantCamera, //!< The grab loop thread is provided by the Instant Camera. It calls RetrieveResult() in a loop. Grabbed images are processed by registered image event handlers. The grab loop thread is started when the grab starts.
        GrabLoop_ProvidedByUser           //!< The user code calls RetrieveResult() in a loop to process grabbed images and camera events.
    };

    /// Defines how to register an item.
    enum ERegistrationMode
    {
        RegistrationMode_Append,        //!< The item is appended to the list of registered items.
        RegistrationMode_ReplaceAll     //!< The item replaces all other registered items.
    };

    /// Defines how to register a camera event handler.
    enum ECameraEventAvailability
    {
        CameraEventAvailability_Mandatory,   //!< The camera event must be provided by the camera, otherwise an exception is thrown.
        CameraEventAvailability_Optional     //!< The camera event handler is not used if the camera does not support the camera event.
    };

    /// Defines how to handle a timeout for a method.
    enum ETimeoutHandling
    {
        TimeoutHandling_Return,           //!< The method returns on timeout. What data is returned can be found in the documentation of the method.
        TimeoutHandling_ThrowException    //!< An exception is thrown on timeout.
    };

    /*!
    \class  CInstantCamera
    \brief  Provides convenient access to a camera device.

    <ul>
    <li> Establishes a single access point for accessing camera functionality.
    <li> The class can be used off the shelf without any parameters. The camera uses a default configuration for the camera device. This can be overridden.
    <li> Handles %Pylon device lifetime. This can be overridden.
    <li> Handles opening and closing of a %Pylon device automatically.
    <li> Handles chunk data parsing automatically returning the chunk data in the grab result.
    <li> Handles event grabbing automatically providing a convenient interface for event callbacks. This can be overridden.
    <li> Handles physical camera device removal.
    <li> Handles the creation, reuse, and destruction of buffers.
    <li> The grabbing can be done in the context of the caller or by using an additional grab loop thread.
    <li> The Instant Camera class is extensible using derivation or by registering event handler objects.
    </ul>
    */
    class PYLONBASE_API CInstantCamera : public Basler_InstantCameraParams::CInstantCameraParams_Params
    {
    public:
        //Creation and life time------------------------------------------------

        /*!
        \brief Creates an Instant Camera object with no attached %Pylon device.

        \error
            Does not throw C++ exceptions.
        */
        CInstantCamera();


        /*!
        \brief Creates an Instant Camera object and calls Attach().

        See Attach() for more information.

        \param[in]  pDevice The %Pylon device to attach.
        \param[in]  cleanupProcedure If cleanupProcedure equals Cleanup_Delete, the %Pylon device is destroyed when the Instant Camera object is destroyed.

        \error
            May throw an exception if the passed %Pylon device is open.
            Does not throw C++ exceptions if the passed %Pylon device is closed or NULL.
        */
        CInstantCamera( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete );


        /*!
        \brief Destroys an Instant Camera object.

        Calls Attach( NULL) for destroying or removing a %Pylon device depending on the passed cleanup procedure.

        \error
            Does not throw C++ exceptions.
        */
        virtual ~CInstantCamera();


        /*!
        \brief  Attaches a %Pylon device to the Instant Camera.

        \param[in]  pDevice The %Pylon device to attach.
        \param[in]  cleanupProcedure If cleanupProcedure equals Cleanup_Delete, the %Pylon device is destroyed when the Instant Camera object is destroyed.

        <ul>
        <li> If a %Pylon device is currently attached, it is destroyed (DestroyDevice()) or removed (DetachDevice()) depending on the previously set cleanup procedure value.
        <li> If the pDevice parameter is NULL, nothing more is done.
        <li> The OnAttach configuration event is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> The new %Pylon device is attached.
        <li> The instant camera migration mode setting is applied to the %Pylon device transport layer node map.
        <li> If the passed %Pylon device is open, callbacks for camera events are registered at the camera node map. (This may fail)
        <li> If the passed %Pylon device is open, a device removal call back is registered. (This may fail)
        <li> If the passed %Pylon device is open, access modifiers (see IPylonDevice::Open()) are carried over as camera parameters.
        <li> The OnAttached configuration event is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        </ul>

        \post
        <ul>
        <li>If the passed pointer to the %Pylon device is NULL, the Instant Camera object is in the "no device attached" state.
        <li>If the passed pointer to the %Pylon device is not NULL, the passed %Pylon device is attached.
        <li>If the set cleanup procedure equals Cleanup_Delete, the %Pylon device is destroyed when the Instant Camera object is destroyed or a new device is attached.
        <li>If the passed %Pylon device is open and the registration of callbacks fails, the Instant Camera object is in the "no device attached" state.
        <li>The opened-by-user flag is set, preventing closing of the %Pylon device on StopGrabbing() when the attached %Pylon device is already open.
        </ul>

        \error
            May throw an exception if the passed %Pylon device is open.
            Does not throw C++ exceptions if the passed %Pylon device is closed or NULL.

         \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void Attach( IPylonDevice* pDevice, ECleanup cleanupProcedure = Cleanup_Delete );


        /*!
        \brief Returns the %Pylon device attached state of the Instant Camera object.

        \return True if a %Pylon device is attached.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsPylonDeviceAttached() const;


        /*!
        \brief Returns the connection state of the camera device.

        \attention Due to technical reasons, the IsCameraDeviceRemoved() property may not be updated immediately after the first error caused by a device removal occurs.

        The device removal is only detected while the Instant Camera and therefore the attached %Pylon device are open.

        The attached %Pylon device is not operable anymore if the camera device has been removed from the PC.
        After it is made sure that no access to the %Pylon device or any of its node maps is made anymore
        the %Pylon device should be destroyed using CInstantCamera::DeviceDestroy().
        The access to the %Pylon device can be protected using the lock provided by GetLock(), e.g. when accessing parameters.

        \return True if the camera device removal from the PC has been detected.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsCameraDeviceRemoved() const;


        /*!
        \brief Returns the ownership of the attached %Pylon device.

        \return True if a %Pylon device is attached and the Instant Camera object has been given the ownership
                by passing the cleanup procedure Cleanup_Delete when calling Attach().

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool HasOwnership() const;


        /*!
        \brief  Destroys the attached %Pylon device.

        \attention The node maps, e.g. the camera node map, of the attached %Pylon device must not be accessed anymore while destroying the %Pylon device.

        <ul>
        <li> If no %Pylon device is attached, nothing is done.
        <li> If the %Pylon device is open, it is closed by calling Close().
        <li> The configuration event OnDestroy is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> The %Pylon device is destroyed even if the cleanup procedure Cleanup_None has been passed when calling Attach() before.
        <li> The configuration event OnDestroyed is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        </ul>

        \post No %Pylon device is attached.

        \error
            Does not throw C++ exceptions. Possible C++ exceptions are caught and ignored.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void DestroyDevice();


        /*!
        \brief  Detaches an attached %Pylon device.

        <ul>
        <li> If no %Pylon device is attached, nothing is done.
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> The configuration event OnDetach is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> The %Pylon device is detached.
        <li> The configuration event OnDetached is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        </ul>

        \return The attached %Pylon device or NULL if nothing has been attached before.

        \post
        <ul>
        <li> No %Pylon device is attached.
        <li> The ownership of the %Pylon device goes to the caller who is responsible for destroying the %Pylon device.
        </ul>

        \error
            Does not throw C++ exceptions. Possible C++ exceptions are caught and ignored.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual IPylonDevice* DetachDevice();


        //Control opening and closing of the device-----------------------------

        /*!
        \brief Opens the attached %Pylon device.

        <ul>
        <li> Opened by user flag is set, preventing closing of the device on StopGrabbing().
        <li> If the %Pylon device is already open, nothing more is done.
        <li> The OnOpen configuration event is fired. The notification of event handlers stops when an event call triggers an exception.
        <li> The %Pylon device is opened and a connection to the camera device is established.
        <li> The instant camera migration mode setting is applied to the %Pylon device transport layer node map.
        <li> A device removal call back is registered at the %Pylon device.
        <li> Callbacks for camera events are registered at the camera node map.
        <li> The OnOpened configuration event is fired if the %Pylon device has been opened successfully. The notification of event handlers stops when an event call triggers an exception.
        </ul>

        \pre A %Pylon device is attached.

        \post
        <ul>
        <li> The %Pylon device is open and a connection to the camera device has been established.
        <li> Opened by user flag is set, preventing closing of the %Pylon device on StopGrabbing().
        </ul>

        \error
            The Instant Camera object is still valid after error.
            The %Pylon device open may throw.
            Configuration event calls may throw.
            Callback registrations may throw.
            The %Pylon device is closed with Close() if the OnOpened event call triggers an exception.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void Open();


        /*!
        \brief Returns the open state of the attached %Pylon device object.
        \note This method still returns true if the camera device has been physically removed from the PC while the attached %Pylon device object is open.
              The %Pylon device object will not automatically close itself on device removal. It must be closed by calling CInstantCamera::Close().
              The IsCameraDeviceRemoved() method can be used to check if the connection to the camera device has been lost while the attached %Pylon device object is open.
        \error Does not throw C++ exceptions.
        \return Returns true if a %Pylon device is attached and it is open.
        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsOpen() const;


        /*!
        \brief Closes the attached %Pylon device.

        <ul>
        <li> If no %Pylon device is attached, nothing is done.
        <li> If the %Pylon device is already closed, nothing is done.
        <li> If a grab is in progress, it is stopped by calling StopGrabbing().
        <li> The configuration event OnClose is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> The connection to the camera device is closed and the %Pylon device is closed.
        <li> The configuration event OnClosed is fired if the %Pylon device has been closed successfully. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        </ul>

        \post The connection to the camera device is closed and the %Pylon device is closed.

        \error
            Does not throw C++ exceptions. Possible C++ exceptions are caught and ignored.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void Close();


        //Grab -----------------------------------------------------------------

        /*!
        \brief Starts the grabbing of images.

        <ul>
        <li> If a grab loop thread has been used in the last grab session, the grab loop thread context is joined with the caller's context.
        <li> If the %Pylon device is not already open, it is opened by calling Open().
        <li> The configuration event OnGrabStart is fired. The notification of event handlers stops when an event call triggers an exception.
        <li> Grab-specific parameters of the camera object are locked, e.g. MaxNumBuffers.
        <li> If the camera device parameter ChunkModeActive is enabled, the Instant Camera chunk parsing support is initialized.
        <li> If the Instant Camera parameter GrabCameraEvents is enabled, the Instant Camera event grabbing support is initialized.
        <li> The grabbing is started.
        <li> The AcquisitionStart command of the camera device is executed.
        <li> The configuration event OnGrabStarted is fired if the grab has been started successfully. The notification of event handlers stops when an event call triggers an exception.
        <li> If grabLoopType equals GrabLoop_ProvidedByInstantCamera, an additional grab loop thread is started calling RetrieveResult( GrabLoopThreadTimeout, grabResult) in a loop.
        </ul>

        \param[in]  strategy The grab strategy. See Pylon::EGrabStrategy for more information
        \param[in]  grabLoopType If grabLoopType equals GrabLoop_ProvidedByInstantCamera, an additional grab loop thread is used to run the grab loop.

        \pre
        <ul>
        <li> A %Pylon device is attached.
        <li> The stream grabber of the %Pylon device is closed.
        <li> The grabbing is stopped.
        <li> The attached %Pylon device supports grabbing.
        <li> Must not be called while holding the lock provided by GetLock() when using the grab loop thread.
        </ul>

        \post
        <ul>
        <li> The grabbing is started.
        <li> Grab-specific parameters of the camera object are locked, e.g. MaxNumBuffers.
        <li> If grabLoopType equals GrabLoop_ProvidedByInstantCamera, an additional grab loop thread is running that calls RetrieveResult( GrabLoopThreadTimeout, grabResult) in a loop. Images are processed by registered image event handlers.
        <li> Operating the stream grabber from outside the camera object will result in undefined behavior.
        </ul>

        \error
            The Instant Camera object is still valid after error. Open() may throw. Configuration event calls may throw. The grab implementation may throw.
            The grabbing is stopped with StopGrabbing() if the OnGrabStarted event call triggers an exception. Throws a C++ exception, if Upcoming Image grab strategy
            is used together with USB camera devices.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void StartGrabbing( EGrabStrategy strategy = GrabStrategy_OneByOne, EGrabLoop grabLoopType = GrabLoop_ProvidedByUser );


        /*!
        \brief Starts the grabbing for a maximum number of images.

        Extends the StartGrabbing(EStrategy, EGrabLoop) by a number of images to grab. If the passed count of images has been reached, StopGrabbing is called
        automatically. The images are counted according to the grab strategy. Skipped images are not taken into account.

        The amount of allocated buffers is reduced to maxImages when grabbing fewer images
        than according to the value of the \link Pylon::CInstantCamera::MaxNumBuffer \c MaxNumBuffer \endlink parameter
        and the grab strategy is GrabStrategy_OneByOne.

        \param[in]  maxImages The count of images to grab. This value must be larger than zero.
        \param[in]  strategy The grab strategy. See Pylon::InstantCamera::EStrategy for more information.
        \param[in]  grabLoopType If grabLoopType equals GrabLoop_ProvidedByInstantCamera, an additional grab loop thread is used to run the grab loop.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void StartGrabbing( size_t maxImages, EGrabStrategy strategy = GrabStrategy_OneByOne, EGrabLoop grabLoopType = GrabLoop_ProvidedByUser );


        /*!
        \brief Retrieves a grab result according to the strategy, waits if it is not yet available

        <ul>
        <li> The content of the passed grab result is released.
        <li> If no %Pylon device is attached or the grabbing is not started, the method returns immediately "false".
        <li> Wait for a grab result if it is not yet available. The access to the camera is not locked during waiting. Camera events are handled.
        <li> Only if camera events are used: Incoming camera events are handled.
        <li> One grab result is retrieved per call according to the strategy applied.
        <li> Only if chunk mode is used: The chunk data parsing is performed. The grab result data is updated using chunk data.
        <li> The image event OnImagesSkipped is fired if grab results have been skipped according to the strategy. The notification of event handlers stops when an event call triggers an exception.
        <li> The image event OnImageGrabbed is fired if a grab result becomes available. The notification of event handlers stops when an event call triggers an exception.
        <li> Stops the grabbing by calling StopGrabbing() if the maximum number of images has been grabbed.
        </ul>

        It needs to be checked whether the grab represented by the grab result has been successful, see CGrabResultData::GrabSucceeded().

        \param[in]  timeoutMs  A timeout value in ms for waiting for a grab result, or the INFINITE value.
        \param[out] grabResult  Receives the grab result.
        \param[in]  timeoutHandling  If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.

        \return True if the call successfully retrieved a grab result, false otherwise.

        \pre
        <ul>
        <li> There is no other thread waiting for a result. This will be the case when the Instant Camera grab loop thread is used.
        </ul>

        \post
        <ul>
        <li> If a grab result has been retrieved, one image is removed from the output queue and is returned in the grabResult parameter.
        <li> If no grab result has been retrieved, an empty grab result is returned in the grabResult parameter.
        <li> If the maximum number of images has been grabbed, the grabbing is stopped.
        <li> If camera event handling is enabled and camera events were received, at least one or more camera event messages have been processed.
        </ul>

        \error
            The Instant Camera object is still valid after error. The grabbing is stopped if an exception is thrown.

        \threading
            This method is synchronized using the lock provided by GetLock() while not waiting.
        */
        virtual bool RetrieveResult( unsigned int timeoutMs, CGrabResultPtr& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );


        /*!
        \brief Stops the grabbing of images.

        <ul>
        <li> Nothing is done if the Instant Camera is not currently grabbing.
        <li> The configuration event OnGrabStop is fired. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> The AcquisitionStop command of the camera device is executed.
        <li> The grabbing is stopped.
        <li> All buffer queues of the Instant Camera are cleared.
        <li> The OnGrabStopped configuration event is fired if the grab has been stopped successfully. Possible C++ exceptions from event calls are caught and ignored. All event handlers are notified.
        <li> If the Instant Camera has been opened by StartGrabbing, it is closed by calling Close().
        <li> Grab-specific parameters of the camera object are unlocked, e.g. MaxNumBuffers.
        </ul>

        \post
        <ul>
        <li> The grabbing is stopped.
        <li> If the %Pylon device has been opened by StartGrabbing and no other camera object service requires it to be open, it is closed.
        <li> Grab specific parameters of the camera object are unlocked, e.g. MaxNumBuffers.
        </ul>

        \error
            Does not throw C++ exceptions. Possible C++ exceptions are caught and ignored.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void StopGrabbing();


        /*!
        \brief Returns state of grabbing.

        The camera object is grabbing after a successful call to StartGrabbing() until StopGrabbing() is called.

        \return Returns true if still grabbing.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsGrabbing() const;


        /*!
        \brief Grabs one image.

        The following code shows a simplified version of what is done (happy path):

        \code
            //grab one image
            StartGrabbing( 1, GrabStrategy_OneByOne, GrabLoop_ProvidedByUser);

            //grab is stopped automatically due to maxImages = 1
            return RetrieveResult( timeoutMs, grabResult, timeoutHandling) && grabResult->GrabSucceeded();
        \endcode

        GrabOne() can be used to together with the CAcquireSingleFrameConfiguration.

        \note Using GrabOne is more efficient if the %Pylon device is already open, otherwise the %Pylon device is opened and closed for each call.

        \note Grabbing single images using Software Trigger (CSoftwareTriggerConfiguration) is recommended if you want to maximize frame rate.
              This is because the overhead per grabbed image is reduced compared to Single Frame Acquisition.
              The grabbing can be started using StartGrabbing().
              Images are grabbed using the WaitForFrameTriggerReady(), ExecuteSoftwareTrigger() and RetrieveResult() methods instead of using GrabOne.
              The grab can be stopped using StopGrabbing() when done.

        \param[in]  timeoutMs  A timeout value in ms for waiting for a grab result, or the INFINITE value.
        \param[out] grabResult  Receives the grab result.
        \param[in]  timeoutHandling  If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.

        \return Returns true if the call successfully retrieved a grab result and the grab succeeded (CGrabResultData::GrabSucceeded()).

        \pre Must meet the preconditions of start grabbing.
        \post Meets the postconditions of stop grabbing.

        \error
            The Instant Camera object is still valid after error. See StartGrabbing(), RetrieveResult(), and StopGrabbing() .
            In the case of exceptions after StartGrabbing() the grabbing is stopped using StopGrabbing().
        */
        virtual bool GrabOne( unsigned int timeoutMs, CGrabResultPtr& grabResult, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );


        /*!
        \brief Deprecated: This method has been deprecated. Use the NumQueuedBuffers parameter instead.
        \return The number of buffers that are queued for grabbing.
        */
        virtual size_t GetQueuedBufferCount();


        /*!
        \brief Provides access to a wait object indicating available grab results.

        \return A wait object indicating available grab results.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual const WaitObject& GetGrabResultWaitObject();


        /*!
        \brief Provides access to a wait object indicating that the grabbing has stopped.

        \return A wait object indicating that the grabbing has stopped.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual const WaitObject& GetGrabStopWaitObject();


        /*!
        \brief Provides access to a wait object indicating available camera events.

        This wait object is %Pylon device specific and changes when a new %Pylon device is attached to
        the camera.

        \return A wait object indicating available camera events.

        \pre
        <ul>
        <li> A %Pylon device is attached.
        <li> The %Pylon device is open.
        </ul>

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */

        virtual const WaitObject& GetCameraEventWaitObject();


        //Event handling--------------------------------------------------------

        /*!
        \brief Adds a configurator to the list of registered configurator objects.

        <ul>
        <li> If mode equals RegistrationMode_ReplaceAll, the list of registered configurators is cleared.
        <li> If pointer \c pConfigurator is not NULL, it is appended to the list of configurators.
        </ul>

        \param[in]  pConfigurator  The receiver of configuration events.
        \param[in]  mode  Indicates how to register the new configurator.
        \param[in]  cleanupProcedure If cleanupProcedure equals Cleanup_Delete, the passed event handler is deleted when no longer needed.

        \post The configurator is registered and called on configuration events.

        \error
            Does not throw C++ exceptions, except when memory allocation fails.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void RegisterConfiguration( CConfigurationEventHandler* pConfigurator, ERegistrationMode mode, ECleanup cleanupProcedure );


        /*!
        \brief Removes a configurator from the list of registered configurator objects.

        If the configurator is not found, nothing is done.

        \param[in]  configurator  The registered receiver of configuration events.

        \return True if successful

        \post
        <ul>
        <li> The configurator is deregistered.
        <li> If the configuration has been registered by passing a pointer and the cleanup procedure is Cleanup_Delete, the event handler is deleted.
        </ul>

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool DeregisterConfiguration( CConfigurationEventHandler* configurator );


        /*!
        \brief Adds an image event handler to the list of registered image event handler objects.

        <ul>
        <li> If mode equals RegistrationMode_ReplaceAll, the list of registered image event handlers is cleared.
        <li> If pointer \c pImageEventHandler is not NULL, it is appended to the list of image event handlers.
        </ul>

        \param[in]  pImageEventHandler  The receiver of image events.
        \param[in]  mode  Indicates how to register the new imageEventHandler.
        \param[in]  cleanupProcedure If cleanupProcedure equals Cleanup_Delete, the passed event handler is deleted when no longer needed.

        \post The imageEventHandler is registered and called on image related events.

        \error
            Does not throw C++ exceptions, except when memory allocation fails.

        \threading
            This method is synchronized using the internal image event handler registry lock.
        */
        virtual void RegisterImageEventHandler( CImageEventHandler* pImageEventHandler, ERegistrationMode mode, ECleanup cleanupProcedure );


        /*!
        \brief Removes an image event handler from the list of registered image event handler objects.

        If the image event handler is not found, nothing is done.

        \param[in]  imageEventHandler  The registered receiver of configuration events.

        \return True if successful

        \post
        <ul>
        <li> The imageEventHandler is deregistered.
        <li> If the image event handler has been registered by passing a pointer and the cleanup procedure is Cleanup_Delete, the event handler is deleted.
        </ul>

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the internal image event handler registry lock.
        */
        virtual bool DeregisterImageEventHandler( CImageEventHandler* imageEventHandler );


        /*!
        \brief Adds an camera event handler to the list of registered camera event handler objects.

        <ul>
        <li> If mode equals RegistrationMode_ReplaceAll, the list of registered camera event handlers is cleared.
        <li> If the pointer \c pCameraEventHandler is not NULL, it is appended to the list of camera event handlers.
        </ul>

        \param[in]  pCameraEventHandler  The receiver of camera events.
        \param[in]  nodeName  The name of the event data node updated on camera event, e.g. "ExposureEndEventTimestamp" for exposure end event.
        \param[in]  userProvidedId  This ID is passed as a parameter in CCameraEventHandler::OnCameraEvent and can be used to distinguish between different events.
                                    It is recommended to create an own application specific enum and use it's values as IDs.
        \param[in]  mode  Indicates how to register the new cameraEventHandler.
        \param[in]  cleanupProcedure If cleanupProcedure equals Cleanup_Delete, the passed event handler is deleted when no longer needed.
        \param[in]  availability  If availability equals CameraEventAvailability_Mandatory, the camera must support the data node specified by node name.
                                  If not, an exception is thrown when the Instant Camera is open, the Instant Camera is opened, or an open %Pylon device is attached.

        Internally, a GenApi node call back is registered for the node identified by \c nodeName.
        This callback triggers a call to the \c CCameraEventHandler::OnCameraEvent() method.
        That's why a Camera Event Handler can be registered for any node of the camera node map to get informed about changes.

        \post The cameraEventHandler is registered and called on camera events.

        \error
            Throws an exception if the availability is set to CameraEventAvailability_Mandatory and the node with the name \c nodeName is not available in the camera node map (see GetNodeMap()).
            Throws an exception fail if the node callback registration fails.
            The event handler is not registered when an C++ exception is thrown.

        \threading
            This method is synchronized using the camera event handler lock. If the camera is open, the lock provided by GetLock() and the camera
            node map lock are also used for synchronization.
        */

        virtual void RegisterCameraEventHandler(
            CCameraEventHandler* pCameraEventHandler,
            const String_t& nodeName,
            intptr_t userProvidedId,
            ERegistrationMode mode,
            ECleanup cleanupProcedure,
            ECameraEventAvailability availability = CameraEventAvailability_Mandatory );


        /*!
        \brief Removes a camera event handler from the list of registered camera event handler objects.

        If the camera event handler is not found, nothing is done.

        \param[in]  cameraEventHandler  The registered receiver of camera events.
        \param[in]  nodeName  The name of the event data node updated on camera event, e.g. "ExposureEndEventTimestamp" for exposure end event.

        \return True if successful

        \post
        <ul>
        <li> The cameraEventHandler is deregistered.
        <li> If the camera event handler has been registered by passing a pointer and the cleanup procedure is Cleanup_Delete, the event handler is deleted.
        </ul>

        \error
            Does not throw C++ exceptions.

        \threading
        This method is synchronized using the camera event handler lock. If the camera is open, the camera node map lock
        is also used for synchronization.
        */
        virtual bool DeregisterCameraEventHandler( CCameraEventHandler* cameraEventHandler, const String_t& nodeName );



        //Additional features---------------------------------------------------

        /*!
        \brief Actively waits until the the camera is ready to accept a frame trigger.

        The implementation selects 'FrameTriggerWait' for the 'AcquisitionStatusSelector'
        and waits until the 'AcquisitionStatus' is true.
        If the above mentioned nodes are not available and the 'SoftwareTrigger' node is readable,
        the implementation waits for SoftwareTrigger.IsDone().

        The WaitForFrameTriggerReady method does not work for A600 Firewire cameras.

        \param[in]  timeoutMs The timeout in ms for active waiting.
        \param[in]  timeoutHandling  If timeoutHandling equals TimeoutHandling_ThrowException, a timeout exception is thrown on timeout.
        \return True if the camera can execute a frame trigger.

        \pre The 'AcquisitionStatusSelector' node is writable and the 'AcquisitionStatus' node is readable or the 'SoftwareTrigger' node is readable.
             This depends on the used camera model.

        \error
            Accessing the camera registers may fail.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual bool WaitForFrameTriggerReady( unsigned int timeoutMs, ETimeoutHandling timeoutHandling = TimeoutHandling_ThrowException );


        /*!
        \brief Checks to see whether the camera device can be queried whether it is ready to accept the next frame trigger.

        If 'FrameTriggerWait' can be selected for 'AcquisitionStatusSelector' and 'AcquisitionStatus' is readable, the
        camera device can be queried whether it is ready to accept the next frame trigger.

        If the nodes mentioned above are not available and the 'SoftwareTrigger' node is readable, the
        camera device can be queried whether it is ready to accept the next frame trigger.

        \note If a camera device can't be queried whether it is ready to accept the next frame trigger, the camera device is
        ready to accept the next trigger after the last image triggered has been grabbed, e.g. after you have retrieved
        the last image triggered using RetrieveResult(). Camera devices that can be queried whether they are ready to accept the
        next frame trigger, may not be ready for the next frame trigger after the last image triggered has been grabbed.

        \return Returns true if the camera is open and the camera device can be queried whether it is ready to accept the next frame trigger.

        \post The 'AcquisitionStatusSelector' is set to 'FrameTriggerWait' if writable.

        \error
        Accessing the camera registers may fail.

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool CanWaitForFrameTriggerReady() const;


        /*!
        \brief Executes the software trigger command.

        The camera needs to be configured for software trigger mode.
        Additionally, the camera needs to be ready to accept triggers.
        When triggering a frame this can be checked using the WaitForFrameTriggerReady() method;

        \note The application has to make sure that the correct trigger is selected
              before calling ExecuteSoftwareTrigger().
              This can be done via the camera's TriggerSelector node.
              The \c Pylon::CSoftwareTriggerConfiguration
              selects the correct trigger when the Instant Camera is opened.

        \pre
        <ul>
        <li> The grabbing is started.
        <li> The camera device supports software trigger.
        <li> The software trigger is available. This depends on the configuration of the camera device.
        </ul>

        \error
            Accessing the camera registers may fail. Throws an exception on timeout if \c timeoutHandling is TimeoutHandling_ThrowException.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void ExecuteSoftwareTrigger();


        /*!
        \brief Sets a context that is attached to each grab result of the camera object on RetrieveResult().
        This is useful when handling multiple cameras. It has nothing in common with the context passed to the stream grabber when queuing a buffer.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void SetCameraContext( intptr_t context );


        /*!
        \brief Returns the context that is attached to each grab result of the camera object

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual intptr_t GetCameraContext() const;


        /*!
        \brief Provides access to the device info object of the attached %Pylon device or an empty one.
        \return The info object of the attached %Pylon device or an empty one.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual const CDeviceInfo& GetDeviceInfo() const;


        /*!
        \brief Provides access to the node map of the camera device.

        The %Pylon device must be opened before reading ore writing any parameters of the camera device.
        This can be done using the Open() method of the Instant Camera class.

        \return Reference to the node map of the camera device.

        \pre A %Pylon device is attached.

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetNodeMap();


        /*!
        \brief Provides access to the transport layer node map of the attached %Pylon device.
        \return Reference to the transport layer node map of the attached %Pylon device
            or the reference to the empty node map if a transport layer node map is not supported.
            The GENAPI_NAMESPACE::INodeMap::GetNumNodes() method can be used to check whether the node map is empty.

        \pre A %Pylon device is attached.

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetTLNodeMap();


        /*!
        \brief Provides access to the stream grabber node map of the attached %Pylon device.
        \return Reference to the stream grabber node map of the attached %Pylon device
            or the reference to the empty node map if grabbing is not supported.
            The GENAPI_NAMESPACE::INodeMap::GetNumNodes() method can be used to check whether the node map is empty.

        \pre
        <ul>
        <li> A %Pylon device is attached.
        <li> The %Pylon device is open.
        </ul>

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetStreamGrabberNodeMap();


        /*!
        \brief Provides access to the event grabber node map of the attached %Pylon device.
        \return Reference to the event grabber node map of the attached %Pylon device
            or a reference to the empty node map if event grabbing is not supported.
            The GENAPI_NAMESPACE::INodeMap::GetNumNodes() method can be used to check whether the node map is empty.

        \pre
        <ul>
        <li> A %Pylon device is attached.
        <li> The %Pylon device is open.
        </ul>

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetEventGrabberNodeMap();


        /*!
        \brief Provides access to the node map of the Instant Camera object.

        The node map of the camera device is made available by the GetNodeMap() method.

        \return Reference to the node map of the Instant Camera object.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual GENAPI_NAMESPACE::INodeMap& GetInstantCameraNodeMap();


        /*!
        \brief Sets an alternative buffer factory that is used for buffer allocation.

        This use of this method is optional and intended for advanced use cases only.

        If NULL is passed as buffer factory then the default buffer factory is used.
        Buffers are allocated when StartGrabbing is called.
        A buffer factory must not be deleted while it is attached to the camera object
        and it must not be deleted until the last buffer is freed. To free all buffers
        the grab needs to be stopped and all grab results must be released or destroyed.

        \param[in]  pFactory  A pointer to a buffer factory.
        \param[in]  cleanupProcedure If ownership is cleanupProcedure Cleanup_Delete, the passed factory is destroyed when no longer needed.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual void SetBufferFactory( IBufferFactory* pFactory, ECleanup cleanupProcedure = Cleanup_Delete );


        /*!
        \brief Returns true if an IEEE 1394 %Pylon device is attached to the Instant Camera object.

        This method is provided for convenience only. The device type can also be determined as shown in the following example.

        \code
        #include <pylon/DeviceClass.h>
        ...
        if (camera.GetDeviceInfo().GetDeviceClass() == Basler1394DeviceClass)
        {
            ...
        }
        \endcode

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool Is1394() const;


        /*!
        \brief Returns true if a GigE %Pylon device is attached to the Instant Camera object.

        This method is provided for convenience only. The device type can also be determined as shown in the following example.

        \code
        #include <pylon/DeviceClass.h>
        ...
        if (camera.GetDeviceInfo().GetDeviceClass() == BaslerGigEDeviceClass)
        {
        ...
        }
        \endcode

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsGigE() const;


        /*!
        \brief Returns true if a USB %Pylon device is attached to the Instant Camera object.

        This method is provided for convenience only. The device type can also be determined as shown in the following example.

        \code
        #include <pylon/DeviceClass.h>
        ...
        if (camera.GetDeviceInfo().GetDeviceClass() == BaslerUsbDeviceClass)
        {
        ...
        }
        \endcode

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsUsb() const;


        /*!
        \brief Returns true if a Camera Link %Pylon device is attached to the Instant Camera object.

        This method is provided for convenience only. The device type can also be determined as shown in the following example.

        \code
        #include <pylon/DeviceClass.h>
        ...
        if (camera.GetDeviceInfo().GetDeviceClass() == BaslerCameraLinkDeviceClass)
        {
        ...
        }
        \endcode

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsCameraLink() const;


        /*!
        \brief Returns true if a CoaXPress GenTL device is attached to the Instant Camera object.

        This method is provided for convenience only.

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsCxp() const;


        /*!
        \brief Returns the SFNC version read from the camera node map.

        The SFNC version is read from the camera node map using the integer nodes
        DeviceSFNCVersionMajor, DeviceSFNCVersionMinor, and DeviceSFNCVersionSubMinor.

        \return The SFNC version used by the camera device. The returned SFNC version is 0.0.0 (Pylon::Sfnc_VersionUndefined)
                if no SFNC version information is provided by the camera device.

        \pre A %Pylon device is attached.

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        VersionInfo GetSfncVersion() const;


        //Types used by camera--------------------------------------------------

        /// The type of the camera class
        typedef CInstantCamera InstantCamera_t;
        /// \copybrief Pylon::IPylonDevice
        typedef IPylonDevice IPylonDevice_t;
        /// \copybrief Pylon::CDeviceInfo
        typedef Pylon::CDeviceInfo DeviceInfo_t;
        /// The generic configuration event handler class
        typedef CConfigurationEventHandler ConfigurationEventHandler_t;
        /// The generic image event handler class
        typedef CImageEventHandler ImageEventHandler_t;
        /// The generic image event handler class
        typedef CCameraEventHandler CameraEventHandler_t;
        /// The generic grab result data
        typedef CGrabResultData GrabResultData_t;
        /// The generic grab result smart pointer
        typedef CGrabResultPtr GrabResultPtr_t;

    protected:

        /*!
        \brief Provides access to the attached %Pylon device.

        \return Pointer to the attached %Pylon device.

        \pre A %Pylon device is attached.

        \error
            The Instant Camera object is still valid after error.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        virtual IPylonDevice* GetDevice();


        /*!
        \brief Provides access to the lock used for synchronizing the access to the camera.

        This lock can be used when extending the Instant Camera class.

        Example:
        \code
            class CMyInstantCamera : public CInstantCamera
            {
                // Method extending the Instant Camera class
                void Foo()
                {
                    // Scoped Lock.
                    AutoLock lock( CInstantCamera::GetLock());

                    //...
                }
             };
        \endcode

        \error
            Does not throw C++ exceptions.
        */
        CLock& GetLock();


        /*
        \brief Returns a reference to the empty node map.

        The empty node map can be used by device specific camera classes.
        The pointer to the empty node map does not change during the lifetime of the camera object.

        \return Reference to the empty node map.

        \error
            Does not throw C++ exceptions.

        \threading
            This method is synchronized using the lock provided by GetLock().
        */
        GENAPI_NAMESPACE::INodeMap& GetEmptyNodeMap();


        // Internal use only. Subject to change without notice.
        void InternalRegisterConfiguration( CConfigurationEventHandler*, ERegistrationMode, ECleanup, const long* );
        // Internal use only. Subject to change without notice.
        void InternalRegisterImageEventHandler( CImageEventHandler*, ERegistrationMode, ECleanup, const long* );
        // Internal use only. Subject to change without notice.
        void InternalRegisterCameraEventHandler( CCameraEventHandler*, const String_t&, intptr_t, ERegistrationMode, ECleanup, ECameraEventAvailability, const long* );
        // Internal use only. Subject to change without notice.
        bool InternalDeregisterConfiguration( const long* );
        // Internal use only. Subject to change without notice.
        bool InternalDeregisterImageEventHandler( const long* );
        // Internal use only. Subject to change without notice.
        bool InternalDeregisterCameraEventHandler( const long*, const String_t& );
        // Internal use only. Subject to change without notice.
        void InternalShutdownEventHandlers();

    public:
        // Internal use only. Subject to change without notice.
        IInstantCameraExtensions& GetExtensionInterface();
    private:
        // The camera object can not be copied.
        CInstantCamera( const CInstantCamera& );
        // The camera object can not be copied.
        void operator = ( const CInstantCamera& );

        class CInstantCameraImpl;
        CInstantCameraImpl* m_pImpl;

    protected:
        // Internal use only. Subject to change without notice.
        friend class CGrabResultDataFactory;
        // Internal use only. Subject to change without notice.
        virtual CGrabResultData* CreateDeviceSpecificGrabResultData();
    private:
        // Internal use only. Subject to change without notice.
        CGrabResultData* CreateGrabResultData();
    public:
        /*!
        \brief Returns true if a BCON %Pylon device is attached to the Instant Camera object.

        This method is provided for convenience only. The device type can also be determined as shown in the following example.

        \code
        #include <pylon/DeviceClass.h>
        ...
        if (camera.GetDeviceInfo().GetDeviceClass() == BaslerBconDeviceClass)
        {
        ...
        }
        \endcode

        \threading
        This method is synchronized using the lock provided by GetLock().
        */
        virtual bool IsBcon() const;
    };

    /**
     * @}
     */
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_INSTANTCAMERA_H_08725703 */
