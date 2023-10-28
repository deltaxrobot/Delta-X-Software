//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for pylon stream grabbers

The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALSTREAMPARAMS_H
#define BASLER_PYLON_UNIVERSALSTREAMPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalStreamParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for AccessMode
    enum AccessModeEnums
    {
        AccessMode_Control,  //!< The application has control access to the device - Applies to: GigE and blaze
        AccessMode_Exclusive,  //!< The application has exclusive access to the device - Applies to: GigE and blaze
        AccessMode_Monitor,  //!< The application has monitoring, i e , read-only, access to the device - Applies to: GigE and blaze
        AccessMode_NotInitialized  //!< Access to the device has not been initialized - Applies to: GigE and blaze
    };

    //! Valid values for PixelPerClockCycle
    enum PixelPerClockCycleEnums
    {
        PixelPerClockCycle_One,  //!< During each clock cycle, the device transmits data for one pixel - Applies to: BCON
        PixelPerClockCycle_Two  //!< During each clock cycle, the device transmits data for two pixels - Applies to: BCON
    };

    //! Valid values for Status
    enum StatusEnums
    {
        Status_Closed,  //!< The stream grabber is closed - Applies to: GigE
        Status_Locked,  //!< The stream grabber is locked - Applies to: GigE
        Status_NotInitialized,  //!< The stream grabber is not initialized - Applies to: GigE
        Status_Open  //!< The stream grabber is open - Applies to: GigE
    };

    //! Valid values for StreamBufferHandlingMode
    enum StreamBufferHandlingModeEnums
    {
        StreamBufferHandlingMode_NewestOnly,  //!< The application always gets the latest completed buffer (i e , the newest) - Applies to: CoaXPress and blaze
        StreamBufferHandlingMode_OldestFirst,  //!< The application always gets the buffer from the head of the output buffer queue (i e , the oldest available) - Applies to: CoaXPress and blaze
        StreamBufferHandlingMode_OldestFirstOverwrite  //!< The application always gets the buffer from the head of the output buffer queue (i e , the oldest available) - Applies to: CoaXPress and blaze
    };

    //! Valid values for StreamType
    enum StreamTypeEnums
    {
        StreamType_CL,  //!< The data stream uses the Camera Link transport layer - Applies to: CoaXPress
        StreamType_CLHS,  //!< The data stream uses the Camera Link HS transport layer - Applies to: CoaXPress
        StreamType_CXP,  //!< The data stream uses the CoaXPress transport layer - Applies to: CoaXPress
        StreamType_Custom,  //!< The data stream uses a custom transport layer - Applies to: CoaXPress
        StreamType_GEV,  //!< The data stream uses the GigE Vision transport layer - Applies to: CoaXPress
        StreamType_Mixed,  //!< Different interface modules of the GenTL Producer are of different types - Applies to: CoaXPress
        StreamType_U3V  //!< The data stream uses the USB3 Vision transport layer - Applies to: CoaXPress
    };

    //! Valid values for TransmissionType
    enum TransmissionTypeEnums
    {
        TransmissionType_LimitedBroadcast,  //!< The stream data is sent to all devices in the local area network (255 255 255 255) - Applies to: GigE
        TransmissionType_Multicast,  //!< The stream data is sent to selected devices in the local network   - Applies to: GigE
        TransmissionType_SubnetDirectedBroadcast,  //!< The stream data is sent to all devices in the same subnet as the camera - Applies to: GigE
        TransmissionType_Unicast,  //!< The stream data is sent to a single device in the local network - Applies to: GigE and blaze
        TransmissionType_UseCameraConfig  //!< The stream transmission configuration is read from the camera - Applies to: GigE and blaze
    };

    //! Valid values for Type
    enum TypeEnums
    {
        Type_NoDriverAvailable,  //!< No suitable driver is installed - Applies to: GigE and blaze
        Type_SocketDriver,  //!< The socket driver is used - Applies to: GigE and blaze
        Type_WindowsFilterDriver,  //!< The pylon GigE Vision Filter Driver is used - Applies to: GigE and blaze
        Type_WindowsIntelPerformanceDriver  //!< The pylon GigE Vision Performance Driver is used - Applies to: GigE and blaze
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalStreamParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for pylon stream grabbers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalStreamParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalStreamParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalStreamParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalStreamParams_Params_v6_2_0_Data;
        CUniversalStreamParams_Params_v6_2_0_Data* m_pCUniversalStreamParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Debug
        //@{
        /*!
            \brief Indicates the mode of access the current application has to the device - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AccessMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<AccessModeEnums>& AccessMode;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables negotiation of the packet size to find the largest possible packet size - Applies to: GigE

            Enables negotiation of the packet size to find the largest possible packet size. Using large packets reduces the overhead for transferring images. The maximum packet size depends on the network hardware and its configuration.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=AutoPacketSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& AutoPacketSize;

        //@}


        //! \name Categories: GrabberSettings
        //@{
        /*!
            \brief Clock frequency on the host side in Hertz - Applies to: BCON

            Clock frequency on the host side in Hertz. This parameter is linked with the BconClockFrequency camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ClockFrequency" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ClockFrequency;

        //@}


        //! \name Categories: IPConfig
        //@{
        /*!
            \brief IP address to which the stream grabber sends all stream data - Applies to: GigE and blaze


            Visibility: Expert

            Selected by: TransmissionType

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DestinationAddr" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& DestinationAddr;

        //@}


        //! \name Categories: IPConfig
        //@{
        /*!
            \brief Port to which the stream grabber sends all stream data - Applies to: GigE and blaze

            Port to which the stream grabber sends all stream data. If the parameter is set to zero, pylon automatically selects an unused port.

            Visibility: Expert

            Selected by: TransmissionType

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=DestinationPort" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& DestinationPort;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Enables the packet resend mechanism - Applies to: GigE and blaze

            Enables the packet resend mechanism. The pylon GigE Vision Filter Driver and the GigE Vision Performance Driver use different packet resend mechanisms.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=EnableResend" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& EnableResend;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Maximum time in milliseconds to receive all packets of a frame - Applies to: GigE and blaze

            Maximum time in milliseconds to receive all packets of a frame. The timer starts when the first packet has been received. If the transmission is not completed within the given time, the corresponding frame is delivered with the status 'Failed'.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=FrameRetention" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& FrameRetention;

        //@}


        //! \name Categories: GrabberSettings
        //@{
        /*!
            \brief Height of the image ROI on the host side - Applies to: BCON

            Height of the image ROI on the host side. This parameter is linked with the Height camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Height" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Height;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Maximum size (in bytes) of a buffer used for grabbing images - Applies to: BCON, GigE, USB and blaze

            Maximum size (in bytes) of a buffer used for grabbing images. A grab application must set this parameter before grabbing starts.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxBufferSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxBufferSize;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Maximum number of buffers that can be used simultaneously for grabbing images - Applies to: BCON, GigE, USB and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxNumBuffer" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxNumBuffer;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum USB data transfer size in bytes - Applies to: USB

            Maximum USB data transfer size in bytes. The default value is appropriate for most applications. Decreasing the value may increase the CPU load. USB host adapter drivers may require decreasing the value if the application fails to receive the image stream. The maximum value also depends on the operating system.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaxTransferSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaxTransferSize;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Maximum number of resend requests per missing packet - Applies to: GigE and blaze

            Maximum number of resend requests per missing packet. Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=MaximumNumberResendRequests" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& MaximumNumberResendRequests;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of USB request blocks (URBs) to be enqueued simultaneously - Applies to: USB

            Maximum number of USB request blocks (URBs) to be enqueued simultaneously. Increasing this value may improve stability and reduce jitter, but requires more resources on the host computer.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=NumMaxQueuedUrbs" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& NumMaxQueuedUrbs;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Timeout period in milliseconds between two packets within one frame - Applies to: GigE and blaze

            Timeout period in milliseconds between two packets within one frame. The timeout is reset each time a packet is received. If the timeout expires, e.g., no packet was received during the given period, the packet resend mechanism takes effect. For more information, see the Enable Resends parameter.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PacketTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PacketTimeout;

        //@}


        //! \name Categories: BufferHandlingControl and GrabberSettings
        //@{
        /*!
            \brief Size of the payload in bytes - Applies to: BCON and CoaXPress

            Size of the payload in bytes. This is the total number of bytes of the image data payload produced by the frame grabber. This value is computed by the frame grabber implementation. The pylon stream grabber needs to be open to be able to compute the payload size.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PayloadSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PayloadSize;

        //@}


        //! \name Categories: GrabberSettings
        //@{
        /*!
            \brief Pixel format on the host side - Applies to: BCON

            Pixel format on the host side. This parameter is linked with the Pixel Format camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelFormatValue" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& PixelFormatValue;

        //@}


        //! \name Categories: GrabberSettings
        //@{
        /*!
            \brief Sets the number of pixels per clock cycle on the host side - Applies to: BCON

            Sets the number of pixels per clock cycle on the host side. This parameter is linked with the Pixels per Clock Cycle camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=PixelPerClockCycle" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<PixelPerClockCycleEnums>& PixelPerClockCycle;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Thread priority of the receive thread - Applies to: GigE

            Thread priority of the receive thread. Only available if the socket driver is used. To assign the priority, the Receive Thread Priority Override parameter must be set to true.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReceiveThreadPriority" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ReceiveThreadPriority;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Enables assigning a custom priority to the thread which receives incoming stream packets - Applies to: GigE

            Enables assigning a custom priority to the thread which receives incoming stream packets. Only available if the socket driver is used. To assign the priority, use the Receive Thread Priority parameter.

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReceiveThreadPriorityOverride" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& ReceiveThreadPriorityOverride;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Size (in frames) of the receive window in which the stream grabber looks for missing packets - Applies to: GigE and blaze

            Size (in frames) of the receive window in which the stream grabber looks for missing packets. Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ReceiveWindowSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ReceiveWindowSize;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Amount of packet resend requests to be batched, i e , sent together - Applies to: GigE and blaze

            Amount of packet resend requests to be batched, i.e., sent together. The parameter value is set in percent of the amount of frames between the resend request threshold and the start of the receive window. Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResendRequestBatching" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ResendRequestBatching;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Time to wait (in milliseconds) between sending a resend request and considering the request as lost - Applies to: GigE and blaze

            Time to wait (in milliseconds) between sending a resend request and considering the request as lost. Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResendRequestResponseTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ResendRequestResponseTimeout;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Threshold after which resend requests are initiated - Applies to: GigE and blaze

            Threshold after which resend requests are initiated. The parameter value is set in percent of the receive window size (Receive Window Size parameter). Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResendRequestThreshold" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ResendRequestThreshold;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Time to wait (in milliseconds) between detecting a missing packet and sending a resend request - Applies to: GigE and blaze

            Time to wait (in milliseconds) between detecting a missing packet and sending a resend request. Only available if the pylon GigE Vision Performance Driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=ResendTimeout" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& ResendTimeout;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Socket buffer size in kilobytes - Applies to: GigE and blaze

            Socket buffer size in kilobytes. Only available if the socket driver is used. 

            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=SocketBufferSize" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& SocketBufferSize;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of frames lost because there were no buffers in the queue - Applies to: GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Buffer_Underrun_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Buffer_Underrun_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief GigE cameras: Number of buffers with at least one failed packet  A packet is considered failed if its status is not 'success'  Other cameras: Number of buffers that returned with an error status   - Applies to: BCON, GigE, USB and blaze

            GigE cameras: Number of buffers with at least one failed packet. A packet is considered failed if its status is not 'success'. Other cameras: Number of buffers that returned an error. 

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Failed_Buffer_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Failed_Buffer_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of failed packets - Applies to: GigE and blaze

            Number of failed packets, i.e., the number of packets whose status is not 'success'.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Failed_Packet_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Failed_Packet_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Last grabbed block ID - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Block_Id" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Last_Block_Id;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Status code of the last failed buffer - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Failed_Buffer_Status" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Last_Failed_Buffer_Status;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Status code of the last failed buffer - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Last_Failed_Buffer_Status_Text" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& Statistic_Last_Failed_Buffer_Status_Text;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of corrupt or lost frames between successfully grabbed images - Applies to: BCON and USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Missed_Frame_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Missed_Frame_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of out-of-memory errors - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Out_Of_Memory_Error_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Out_Of_Memory_Error_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of packets requested by packet resend commands - Applies to: GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Resend_Packet_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Resend_Packet_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of emitted packet resend commands sent - Applies to: GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Resend_Request_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Resend_Request_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of stream resynchronizations - Applies to: USB


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Resynchronization_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Resynchronization_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief GigE cameras: Number of frames received  Other cameras: Number of buffers processed - Applies to: BCON, GigE, USB and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Total_Buffer_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Total_Buffer_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Number of packets received - Applies to: GigE and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Statistic_Total_Packet_Count" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Statistic_Total_Packet_Count;

        //@}


        //! \name Categories: Debug
        //@{
        /*!
            \brief Indicates the current status of the stream grabber - Applies to: GigE


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Status" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<StatusEnums>& Status;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Minimum number of buffers to announce to enable selected buffer handling mode - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamAnnounceBufferMinimum" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamAnnounceBufferMinimum;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of announced (known) buffers on this stream - Applies to: CoaXPress and blaze

            Number of announced (known) buffers on this stream. This value is volatile. It may change if additional buffers are announced and/or buffers are revoked by the GenTL Consumer.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamAnnouncedBufferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamAnnouncedBufferCount;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Alignment size in bytes of the buffers passed to DSAnnounceBuffer - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamBufferAlignment" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamBufferAlignment;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Sets the buffer handling mode of this data stream - Applies to: CoaXPress and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamBufferHandlingMode" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<StreamBufferHandlingModeEnums>& StreamBufferHandlingMode;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Maximum number of chunks to be expected in a buffer - Applies to: CoaXPress

            Maximum number of chunks to be expected in a buffer (can be used to allocate the array for the DSGetBufferChunkData function).

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamChunkCountMaximum" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamChunkCountMaximum;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of delivered frames since last acquisition start - Applies to: CoaXPress and blaze

            Number of delivered frames since last acquisition start. It isn't reset until the stream is closed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamDeliveredFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamDeliveredFrameCount;

        //@}


        //! \name Categories: StreamInformation
        //@{
        /*!
            \brief Device-wide unique ID of the data stream - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamID" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IStringEx& StreamID;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of buffers in the input buffer pool plus the buffers currently being filled - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamInputBufferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamInputBufferCount;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Indicates whether the acquisition engine is started or not - Applies to: CoaXPress and blaze

            Indicates whether the acquisition engine is started or not. This is independent of the acquisition status of the remote device.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamIsGrabbing" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IBooleanEx& StreamIsGrabbing;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of lost frames due to queue underrun - Applies to: CoaXPress and blaze

            Number of lost frames due to queue underrun. This number is initialized with zero at the time the stream is opened and incremented every time data couldn't be acquired because there was no buffer in the input buffer pool. It isn't reset until the stream is closed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamLostFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamLostFrameCount;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of buffers in the output buffer queue - Applies to: CoaXPress and blaze


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamOutputBufferCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamOutputBufferCount;

        //@}


        //! \name Categories: BufferHandlingControl
        //@{
        /*!
            \brief Number of frames started in the acquisition engine - Applies to: CoaXPress and blaze

            Number of frames started in the acquisition engine. This number is incremented every time a new buffer is started and then filled regardless of whether the buffer is later delivered to the user or discarded for any reason. This number is initialized with 0 at at the time the stream is opened. It isn't reset until the stream is closed.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamStartedFrameCount" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& StreamStartedFrameCount;

        //@}


        //! \name Categories: StreamInformation
        //@{
        /*!
            \brief Sets the transport layer of the data stream - Applies to: CoaXPress


            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=StreamType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<StreamTypeEnums>& StreamType;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Priority of the thread that handles USB requests from the stream interface - Applies to: USB


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TransferLoopThreadPriority" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TransferLoopThreadPriority;

        //@}


        //! \name Categories: IPConfig
        //@{
        /*!
            \brief Sets how stream data is transferred within the network - Applies to: GigE and blaze

            Sets how stream data is transferred within the network. The stream grabber can send the stream data to one specific device or to multiple devices in the network.

            Visibility: Expert

            Selecting Parameters: DestinationAddr and DestinationPort

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TransmissionType" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TransmissionTypeEnums>& TransmissionType;

        //@}


        //! \name Categories: ExtendedStreamControl and Root
        //@{
        /*!
            \brief Sets the driver type to be used by the stream grabber - Applies to: GigE and blaze


            Visibility: Beginner

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Type" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IEnumParameterT<TypeEnums>& Type;

        //@}


        //! \name Categories: Debug
        //@{
        /*!
            \brief Indicates whether the socket driver is currently available - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TypeIsSocketDriverAvailable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TypeIsSocketDriverAvailable;

        //@}


        //! \name Categories: Debug
        //@{
        /*!
            \brief Indicates whether the pylon GigE Vision Filter Driver is currently available - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TypeIsWindowsFilterDriverAvailable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TypeIsWindowsFilterDriverAvailable;

        //@}


        //! \name Categories: Debug
        //@{
        /*!
            \brief Indicates whether the pylon GigE Vision Performance Driver is currently available - Applies to: GigE and blaze


            Visibility: Guru

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=TypeIsWindowsIntelPerformanceDriverAvailable" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& TypeIsWindowsIntelPerformanceDriverAvailable;

        //@}


        //! \name Categories: GrabberSettings
        //@{
        /*!
            \brief Width of the image ROI on the host side - Applies to: BCON

            Width of the image ROI on the host side. This parameter is linked with the Width camera parameter. If the camera parameter changes, the host parameter changes accordingly, but not vice versa. The host parameter should not be set to a value different from the camera parameter.

            Visibility: Expert

            The <a href="https://docs.baslerweb.com/?rhcsh=1&rhmapid=Width" target="_blank">Basler Product Documentation</a> may provide more information.
        */
        Pylon::IIntegerEx& Width;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalStreamParams_Params_v6_2_0(CUniversalStreamParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalStreamParams_Params_v6_2_0& operator=(CUniversalStreamParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for pylon stream grabbers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class CUniversalStreamParams_Params : public CUniversalStreamParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalStreamParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalStreamParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalStreamParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalStreamParams

#endif // BASLER_PYLON_UNIVERSALSTREAMPARAMS_H
