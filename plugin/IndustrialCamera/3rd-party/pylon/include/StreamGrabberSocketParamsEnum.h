/**
 * \file
 * \brief StreamGrabberSocket parameter enumeration.
 *
 * \Copyright (c) 2006-2024 Basler AG
 *
 * \author Urs Helmig
 *
 * \workfile $Workfile:$
 * \folder   $Folder:$
 * \project  $Project:$
 * \revision $Revision: 1.6 $
 * \modified $Author: $ $Modtime:$
 * \checkin  $Date:  $
 */

#ifndef STREAMGRABBER_SOCKET_PARAMSENUM_H__INCLUDED
#define STREAMGRABBER_SOCKET_PARAMSENUM_H__INCLUDED


/**
 * Stream Parameter IDs.
 */
typedef enum _STREAMGRABBER_SOCKET_PARAMETER_ID
{

/**
* Enable Resend.
* Enables the emission of GigE Vision packet resend requests belonging to the underlying stream.
* Type: ULONG.
* Default: 1.
* Access: RW.
*/
    STREAMGRABBER_SOCKET_PARAMETER_ENABLE_RESEND,

    /**
    * Packet Timeout [ms].
    * The time to wait if no packages are received before a loss is detected.
    * Type: ULONG.
    * Default: 20.
    * Access: RW.
    */
    STREAMGRABBER_SOCKET_PARAMETER_PACKET_TIMEOUT_MS,

    /**
    * Maximum Frame Retention Time [ms].
    * The maximum time the delivery of an incomplete frame is deferred before it may be delived uncomplete.
    * Type: ULONG.
    * Default: 200.
    * Access: RW.
    */
    STREAMGRABBER_SOCKET_PARAMETER_FRAME_RETENTION_MS,

    /**
    * SocketBufferSize
    * Socket buffer size in kB
    *
    * Type: UINT32
    * Default: 2048.
    * Access: RW.
    */
    STREAMGRABBER_SOCKET_PARAMETER_SOCKET_BUFFER_SIZE,

    /**
    * Receive Thread ID.
    * Get the thread id of associated receive thread.
    * Type: HANDLE(W32) or pthread_t(Linux).
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_GET_RECVTHREAD_ID,

    /**
    * Total Buffer Count.
    * Counts the number of received frames.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_BUFFER_TOTAL,

    /**
    * Failed Buffer Count.
    * Counts the number of buffers with status != success.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_BUFFER_FAILED,

    /**
    * Buffer Underrun Count.
    * Counts the number of frames lost because there were no buffers queued to the driver.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_BUFFER_UNDERRUNS,

    /**
    * Total Packet Count.
    * Counts the number of received packets.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_PACKETS_TOTAL,

    /**
    * Failed Packet Count.
    * Counts the number of received packets with status != success.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_PACKETS_FAILED,

    /**
    * Resend Request Count.
    * Counts the number of emitted PACKETRESEND commands.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_RESEND_REQUESTS,

    /**
    * Resend Packet Count.
    * Counts the number of packets requested by resend packet commands.
    * Type: ULONG.
    * Default: .
    * Access: R.
    */
    STREAMGRABBER_SOCKET_PARAMETER_COUNTER_RESEND_PACKETS,

    /**
    * Maximum Number Resends.
    * Enables the emission of GigE Vision packet resend requests belonging to the underlying stream.
    * Type: ULONG.
    * Default: 1.
    * Access: RW.
    */
    STREAMGRABBER_SOCKET_PARAMETER_MAXIMUM_NUMBER_RESEND_REQUESTS_PER_PACKET,    

} STREAMGRABBERSOCKET_PARAMETER_ID;


#endif // STREAMGRABBER_SOCKET_PARAMSENUM_H__INCLUDED
