//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief    Low Level API: Definition of IStreamGrabber interface

\attention
The Low Level API has been deprecated in pylon 6.0. It is recommended
to use the Instant Camera classes instead.
*/
#ifndef __ISTREAMGRABBER_H__
#define __ISTREAMGRABBER_H__

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <pylon/stdinclude.h>

namespace Pylon
{
    /*!
    \ingroup Pylon_LowLevelApi
    \brief Used to configure how starting and stopping of streaming are handled.
           If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.
    */

    class GrabResult;
    class WaitObject;
    /// This opaque type represents a registered buffer.
    typedef void* StreamBufferHandle;

    // -------------------------------------------------------------------------
    // interface IStreamGrabber
    // -------------------------------------------------------------------------
    /*!
        \ingroup Pylon_LowLevelApi
        \interface IStreamGrabber
        \brief Low Level API: Interface to an (input) data stream

        \attention
        The Low Level API has been deprecated in pylon 6.0. It is recommended
        to use the Instant Camera classes instead.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.
    */
    interface IStreamGrabber
    {
        /*!
        \brief Opens the stream grabber.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \pre
        <ul>
        <li> The corresponding device is open.
        <li> The stream grabber is closed.
        </ul>

        \post
        <ul>
        <li> The stream grabber is open.
        <li> If the device is closed while the stream grabber is open, the stream grabber is closed automatically.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber is already open or prepared. The stream grabber remains in the same state after raising the exception in this case.
        <li> Throws an exception if the stream grabber is closed and opening the stream grabber fails. The stream grabber remains closed after raising the exception.
        </ul>
        */
        virtual void Open() = 0;


        /*!
        \brief Closes the stream grabber.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        This method calls FinishGrab() automatically if needed.

        \post
        <ul>
        <li> Any running grab has been stopped by calling FinishGrab().
        <li> The stream grabber is closed.
        <li> All results waiting in the output queue are discarded.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        Does not throw C++ exceptions.
        */
        virtual void Close() = 0;


        /*!
        \brief Retrieve whether the stream grabber is open.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \return Returns true if the stream grabber is open.

        \threading
        This method can be synchronized using an internal stream grabber lock.

        \error
        Does not throw C++ exceptions.
        */
        virtual bool IsOpen() const = 0;


        /*!
        \brief Registers a buffer for subsequent use.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \param[in] pBuffer The pointer of the buffer that is to be used for grabbing e.g., for grabbing images.
        \param[in] bufferSize The size of the provided buffer in bytes.
        \return Returns a handle for the registered buffer that can be used in subsequent calls.

        \pre
        <ul>
        <li> pBuffer must not be NULL.
        <li> The buffer size must not exceed the value of the node map integer parameter MaxBufferSize specified when PrepareGrab was called.
        <li> Less buffers are already registered than value of the node map integer parameter MaxNumBuffer specified when PrepareGrab was called.
        <li> The stream grabber is prepared, see PrepareGrab().
        <li> The buffer has not been registered already.
        </ul>

        \post
        <ul>
        <li> The buffer is registered.
        <li> Transport Layer specific preparations have been executed e.g., locking the memory pages of the buffer.
        <li> The buffer must not be freed while being registered.
        <li> If the stream grabber requires the additional streaming state, streaming must not be started, see IsStartAndStopStreamingMandatory() and StartStreamingIfMandatory().
        </ul>

        \threading
        This method can be synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if registering the buffer fails. The buffer is not registered after raising an exception.
        </ul>
        */
        virtual StreamBufferHandle RegisterBuffer( void* pBuffer, size_t bufferSize ) = 0;


        /*!
        \brief Deregisters the buffer.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \param[in] hStreamBuffer The handle of a buffer that has been provided by RegisterBuffer()
        \return Returns the pointer of the corresponding buffer.

        \pre
        <ul>
        <li> The buffer is registered.
        <li> The buffer is not queued. Either it has not been queued yet, see QueueBuffer(), or it has been retrieved after grabbing using RetrieveResult().
        <li> FinishGrab() or Close() have not been called for the grab session yet.
        <li> If the stream grabber requires the additional streaming state, streaming must not be started, see IsStartAndStopStreamingMandatory() and StartStreamingIfMandatory().
        </ul>

        \post
        <ul>
        <li> Transport layer-specific preparations have been reversed.
        <li> The buffer is deregistered.
        <li> The buffer can be freed if needed e.g., by calling delete.
        </ul>

        \error
        Throws an exception if deregistering the buffer fails.
        */
        virtual const void* DeregisterBuffer( StreamBufferHandle hStreamBuffer ) = 0;


        /*!
        \brief Prepares grabbing

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \note pylon uses a pool of buffers with a fixed amount of buffers to grab images. This is required because certain
        preparations e.g., locking the buffer's memory pages, must be made by the driver to be able to grab images into a buffer.
        Thus, using a pool of buffers is much more efficient than allocating a new buffer for every grabbed image.

        The node map integer parameters MaxBufferSize and MaxNumBuffer need to be set before calling PrepareGrab().

        MaxNumBuffer should be set to the number of buffers you plan to use for grabbing.
        \note There can be limitations depending on the transport layer technology used when using a large amount of buffers.

        MaxBufferSize needs to be set according to the PayloadSize parameter of the camera device or the stream grabber.
        If the stream grabber provides a PayloadSize parameter, the MaxBufferSize must be at least the size reported
        by the stream grabber payload size. This is the case if for instance a frame grabber or additional preprocessing
        is used.
        If the stream grabber does not provide a PayloadSize parameter, the MaxBufferSize must be at least the size reported
        by the camera device PayloadSize parameter.

        \pre
        <ul>
        <li> The node map integer parameter MaxBufferSize is set, see GetNodeNap().
        <li> The node map integer parameter MaxNumBuffer is set, see GetNodeNap().
        <li> The stream grabber is open.
        <li> No grab session is currently in progress.
        </ul>

        \post
        <ul>
        <li> Resources required for grabbing are allocated.
        <li> The camera is set up for grabbing.
        <li> Critical camera parameters, provided by IPylonDevice::GetNodeMap(), are locked.
        <li> The stream grabber is prepared.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if preparing the stream grabber fails. The stream grabber is not prepared after raising the exception.
        </ul>
        */
        virtual void PrepareGrab() = 0;


        /*!
        \brief Returns true if the Stream Grabber requires calling StartStreamingIfMandatory() for operation.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        Does not throw C++ exceptions.
        */
        virtual bool IsStartAndStopStreamingMandatory() = 0;


        /*!
        \brief Starts streaming for the stream grabber if this is mandatory for operation.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        Some stream grabbers e.g., some stream grabbers based on GenTL, have limitations on when buffers can
        be registered. For these stream grabbers it is mandatory to register all buffers first and
        call StartStreamingIfMandatory() aftwards.
        Between the StartStreamingIfMandatory() and StopStreamingIfMandatory() calls no buffers can be
        registered or deregistered if such a limitation exists.

        \note This method has been added in pylon 6.0 for supporting CoaXPress. Prior implementations
              of pylon stream grabbers did not require calling start and stop streaming.
              The IsStartAndStopStreamingMandatory(), StartStreamingIfMandatory(), and StopStreamingIfMandatory()
              methods allow backward-compatible operation.

        \pre
        <ul>
        <li> The stream grabber is prepared.
        </ul>

        \post
        <ul>
        <li> If the stream grabber does not require StartStreamingIfMandatory(), nothing is done.
        <li> Streaming is started. For GenTL-based stream grabbers DSStartAcquistion is called
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if start streaming fails. The stream grabber is not streaming after raising the exception.
        </ul>
        */
        virtual void StartStreamingIfMandatory() = 0;


        /*!
        \brief Stops streaming for the stream grabber if this is mandatory for operation.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        Some stream grabbers e.g., some stream grabbers based on GenTL, have limitations on when buffers can
        be registered. For these stream grabbers it is mandatory to call StopStreamingIfMandatory to be able to deregister buffer afterwards.

        \pre
        <ul>
        <li> The stream grabber is in streaming mode if start and stop streaming is mandatory.
        </ul>

        \post
        <ul>
        <li> If the stream grabber does not require StopStreamingIfMandatory(), nothing is done.
        <li> Streaming is stopped. For GenTL-based stream grabbers DSStopAcquistion is called.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if stop streaming fails. The stream grabber is not streaming after raising the exception.
        </ul>
        */
        virtual void StopStreamingIfMandatory() = 0;


        /*!
        \brief Stops grabbing finally

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        This method calls FlushBuffersToOutput() automatically if needed.

        \pre
        <ul>
        <li> The stream grabber is prepared.
        </ul>

        \post
        <ul>
        <li> Resources required for grabbing are freed.
        <li> The camera is not set up for grabbing anymore
        <li> Critical camera parameters, provided by IPylonDevice::GetNodeMap(), are unlocked.
        <li> The stream grabber is open.
        <li> Queued buffers are available in the output queue of the stream grabber and can be retrieved calling RetrieveResult().
        <li> All buffers are deregistered.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if finishing the grab fails. The stream grabber is in open state after raising the exception.
        </ul>
        */
        virtual void FinishGrab() = 0;


        /*!
        \brief Enqueues a buffer in the input queue.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \param[in] hStreamBuffer The handle of a buffer that has been provided by RegisterBuffer().
        \param[in] pContext A user-provided pointer passed along with buffer in the internal input and output queues.

        \pre
        <ul>
        <li> The buffer is registered, see RegisterBuffer().
        <li> The stream grabber is prepared.
        <li> The buffer has not been queued for grabbing yet.
        <li> The buffer is not waiting in the output queue of the stream grabber. The buffer can be queued again after it has been retrieved using RetrieveResult().
        </ul>

        \post
        <ul>
        <li> The buffer is queued to input queue of the stream grabber.
        <li> The buffer cannot be deregistered until it has been retrieved using RetrieveResult().
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if queuing the buffer fails.
        </ul>
        */
        virtual void QueueBuffer( StreamBufferHandle hStreamBuffer, const void* pContext = NULL ) = 0;


        /*!
        \brief Cancels grabbing the current buffer and flushes all buffers to the output queue.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \pre
        <ul>
        <li> The stream grabber is prepared.
        </ul>

        \post
        <ul>
        <li> All queued buffers are placed in the output queue of the stream grabber and can be retrieved using RetrieveResult().
        <li> Buffers that have not been grabbed completely before calling FlushBuffersToOutput are marked with the EGrabStatus Canceled.
        <li> The stream grabber is prepared.
        <li> Buffers can be queued again to continue grabbing.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if canceling the grab fails.
        </ul>
        */
        virtual void FlushBuffersToOutput() = 0;
        ///This method has been renamed to FlushBuffersToOutput(). Calling CancelGrab calls FlushBuffersToOutput();
        virtual void CancelGrab() = 0;


        /*!
        \brief Retrieves one grab result from the output queue.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        param[out] grabResult The object the grab result data is returned in if true is returned. The \c grabResult remains unchanged if false is returned.
        \return Returns true when result was available.

        \pre
        <ul>
        <li> The stream grabber is open.
        </ul>

        \post
        <ul>
        <li> If a grab result was available, it has been removed from the ouput queue.
        <li> The corresponding buffer can be queued again for grabbing.
        </ul>

        \threading
        This method is synchronized using an internal stream grabber lock.

        \error
        <ul>
        <li> Throws a LogicalErrorException if the stream grabber state does not match the preconditions.
        <li> Throws an exception if retrieving the result fails. This does not change the stream grabber state.
        </ul>
        */
        virtual bool RetrieveResult( GrabResult& grabResult ) = 0;


        /*!
        \brief Returns the result event object of the stream grabber.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        This object is associated with the output queue of the stream grabber.
        The event is signaled when output queue is non-empty.

        \return Returns the result event object of the stream grabber.

        \threading
        This method can be synchronized using an internal stream grabber lock.

        \error
        Does not throw C++ exceptions.
        */

        virtual WaitObject& GetWaitObject() const = 0;


        /*!
        \brief Returns the associated stream grabber parameters.

        \note Basler recommends using one of the Instant Camera classes CBaslerUniversalInstantCamera or CInstantCamera for new projects.
              If you want to control which buffers are used for grabbing, you can use the Pylon::IBufferFactory.

        \return Returns the associated stream grabber parameters. The returned pointer is never NULL.

        \threading
        This method can be synchronized using an internal stream grabber lock.

        \error
        Does not throw C++ exceptions.
        */
        virtual GENAPI_NAMESPACE::INodeMap* GetNodeMap() = 0;
    };

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__ISTREAMGRABBER_H__
