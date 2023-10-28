//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for Instant Camera

The parameter class is used by the \c Pylon::CInstantCamera class.
The code sample \ref sample_Grab shows the usage by setting the MaxNumBuffer parameter.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_INSTANTCAMERAPARAMS_H
#define BASLER_PYLON_INSTANTCAMERAPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_InstantCameraParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************

    
    
    //**************************************************************************************************
    // Parameter class CInstantCameraParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for Instant Camera

    The parameter class is used by the \c Pylon::CInstantCamera class.
    The code sample \ref sample_Grab shows the usage by setting the MaxNumBuffer parameter.
    */
    class PYLONBASE_API CInstantCameraParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CInstantCameraParams_Params_v6_2_0( void );

        //! Destructor
        ~CInstantCameraParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CInstantCameraParams_Params_v6_2_0_Data;
        CInstantCameraParams_Params_v6_2_0_Data* m_pCInstantCameraParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Root
        //@{
        /*!
            \brief If set, this will automatically execute AcquisitionStart when calling StartGrabbing and AcquisitionStop when calling StopGrabbing  This option is enabled by default - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& AcquisitionStartStopExecutionEnable;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables/disables the use of a chunk node map for each grab result  Grab result chunk node maps can be disabled to save resources - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& ChunkNodeMapsEnable;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief If set, all buffers will be cleared (set to 0) before grabbing an image  Note that this requires additional processing time per frame - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& ClearBufferModeEnable;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables/disables the grabbing of camera events while images are grabbed  Is writable when the camera object is closed - Applies to: InstantCamera


            Visibility: Expert

        */
        Pylon::IBooleanEx& GrabCameraEvents;

        //@}


        //! \name Categories: GrabLoopThread
        //@{
        /*!
            \brief The grab loop thread priority - Applies to: InstantCamera

            This value sets the absolute thread priority for the grab loop thread.

            Visibility: Guru

        */
        Pylon::IIntegerEx& GrabLoopThreadPriority;

        //@}


        //! \name Categories: GrabLoopThread
        //@{
        /*!
            \brief If enabled, the user can set a custom priority for the grab loop thread  Otherwise, the priority of the newly created thread is not changed - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& GrabLoopThreadPriorityOverride;

        //@}


        //! \name Categories: GrabLoopThread
        //@{
        /*!
            \brief A custom timeout for the grab loop thread's call to RetrieveResult  RetrieveResult is configured to throw an exception on timeout, which will stop the grab session - Applies to: InstantCamera


            Visibility: Beginner

        */
        Pylon::IIntegerEx& GrabLoopThreadTimeout;

        //@}


        //! \name Categories: GrabLoopThread
        //@{
        /*!
            \brief If enabled, the user can set a custom timeout for the grab loop thread's call to RetrieveResult  RetrieveResult is configured to throw an exception on timeout, which will stop the grab session - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& GrabLoopThreadUseTimeout;

        //@}


        //! \name Categories: InternalGrabEngineThread
        //@{
        /*!
            \brief The internal grab engine thread priority - Applies to: InstantCamera

            This value sets the absolute thread priority for the internal grab engine thread operating the stream grabber.

            Visibility: Guru

        */
        Pylon::IIntegerEx& InternalGrabEngineThreadPriority;

        //@}


        //! \name Categories: InternalGrabEngineThread
        //@{
        /*!
            \brief If enabled, the user can set a custom priority for the internal grab engine thread operating the stream grabber  Otherwise the priority defaults to 25 - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& InternalGrabEngineThreadPriorityOverride;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The maximum number of buffers that are allocated and used for grabbing - Applies to: InstantCamera


            Visibility: Beginner

        */
        Pylon::IIntegerEx& MaxNumBuffer;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The maximum number of grab results available at any time during a grab session  This value can be limited to save resources  Furthermore, it can be used to check that the grab results are returned correctly - Applies to: InstantCamera


            Visibility: Beginner

        */
        Pylon::IIntegerEx& MaxNumGrabResults;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The maximum number of buffers that are queued in the stream grabber input queue - Applies to: InstantCamera


            Visibility: Beginner

        */
        Pylon::IIntegerEx& MaxNumQueuedBuffer;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The migration mode is set up according to this setting at defined points e g , when the camera is opened - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& MigrationModeActive;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The camera object is set to monitor mode when enabled, e g  when using the GigE multicast feature  Is writable when the camera object is closed - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IBooleanEx& MonitorModeActive;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The number of empty buffers that are not used for grabbing yet - Applies to: InstantCamera


            Visibility: Expert

        */
        Pylon::IIntegerEx& NumEmptyBuffers;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The number of buffers queued at Low Level API stream grabber - Applies to: InstantCamera

            
        
            This is the number of buffers that are queued for grabbing in the stream grabber.
            The number is influenced by the number of available free buffers and the
            maximum number of buffers that can be queued.
            See also the MaxNumBuffer and MaxNumQueuedBuffer parameters.

            This parameter can be used to check whether the number of buffers ready for grabbing
            is stable, which means that the image processing is fast enough to keep up with the
            rate of incoming images when using the GrabStrategy_OneByOne grab strategy.
        
        

            Visibility: Expert

        */
        Pylon::IIntegerEx& NumQueuedBuffers;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The number of grab result buffers in the output queue that are ready for retrieval - Applies to: InstantCamera


            Visibility: Expert

        */
        Pylon::IIntegerEx& NumReadyBuffers;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief The size of the grab result buffer output queue - Applies to: InstantCamera


            Visibility: Expert

        */
        Pylon::IIntegerEx& OutputQueueSize;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief If larger than 0, a static chunk node map pool is used instead of dynamic chunk node map creation - Applies to: InstantCamera


            Visibility: Guru

        */
        Pylon::IIntegerEx& StaticChunkNodeMapPoolSize;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CInstantCameraParams_Params_v6_2_0(CInstantCameraParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CInstantCameraParams_Params_v6_2_0& operator=(CInstantCameraParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for Instant Camera

    The parameter class is used by the \c Pylon::CInstantCamera class.
    The code sample \ref sample_Grab shows the usage by setting the MaxNumBuffer parameter.
    */
    class CInstantCameraParams_Params : public CInstantCameraParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CInstantCameraParams_Params( void )
        {
        }

        //! Destructor
        ~CInstantCameraParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CInstantCameraParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_InstantCameraParams

#endif // BASLER_PYLON_INSTANTCAMERAPARAMS_H
