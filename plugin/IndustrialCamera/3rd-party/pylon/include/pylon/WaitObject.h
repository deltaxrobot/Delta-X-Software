//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Urs Helmig
//-----------------------------------------------------------------------------
/*!
\file
\brief    Declaration of WaitObject classes
*/
#ifndef __WAITOBJECT_H__
#define __WAITOBJECT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */


#include <pylon/stdinclude.h>
#include <pylon/PylonBase.h>


#if defined (PYLON_UNIX_BUILD)
struct _WaitObjectPosix_t;
#endif


namespace Pylon
{
    // -------------------------------------------------------------------------
    // enum EWaitExResult
    // ----------------------------------------------------------------------
    /*!
    \brief The return value of the Pylon::WaitObject::WaitEx() and Pylon::WaitObjectEx::WaitEx() methods
    \ingroup PYLON_PUBLIC
    */
    // ----------------------------------------------------------------------
    enum EWaitExResult
    {
        waitex_timeout = 0,   //!< The time-out interval elapsed
        waitex_signaled = 1,  //!< The wait operation completed successfully
        waitex_abandoned = 2, //!< Windows only (see MSDN for more information)
        waitex_alerted = -1   //!< The wait was interrupted (Windows: queued APC or I/O completion routine; UNIX: signal)
    };

#if defined(PYLON_WIN_BUILD)
    typedef HANDLE WaitObject_t;
#elif defined(PYLON_UNIX_BUILD)
    typedef struct _WaitObjectPosix_t* WaitObject_t;
#endif


#if defined (PYLON_UNIX_BUILD)

    // -------------------------------------------------------------------------
    // enum ready_mask_t
    // ----------------------------------------------------------------------
    /*!
    \brief File descriptor ready mask

    Return value of the Pylon::WaitObject::GetReadyMask() method. Indicates to which type of file descriptor set a wait object's file descriptor
    is to be added when using the file descriptor as input for the select() or poll() function.

    Example: When the ready_read bit of a wait object's GetReadyMask() value is set, add the wait object's file descriptor to the read file descriptor set.


    \ingroup PYLON_PUBLIC
    */
    // ----------------------------------------------------------------------
    enum ready_mask_t
    {
        ready_none = 0x00,    //!< The file descriptor is not valid
        ready_read = 0x01,    //!< The file desriptor is to be added to a read file descriptor set
        ready_write = 0x02,   //!< The file descriptor is to be added to a write file descriptor set
        ready_except = 0x04   //!< The file descriptor is to be added to a exception file descriptor set
    };
#endif

    // ----------------------------------------------------------------------
    const unsigned int waitForever = 0xFFFFFFFF;

#if defined (PYLON_UNIX_BUILD)
#   ifndef INFINITE
#       define INFINITE waitForever
#   endif
#endif

    // ----------------------------------------------------------------------
    /*!
    \brief A platform independent wait object.

    Wait objects are used by the Pylon::IStreamGrabber and Pylon::IEventGrabber interfaces to provide a platform independent mechanism for
    allowing an application to wait for data buffers to be filled.

    For the Windows version of pylon, WaitObjects are wrappers for Win32 objects that can be used with \c WaitForSingleObject() and \c WaitForMultipleObjects().

    For the Linux version of pylon, WaitObjects are implemented based on file descriptors. The wait operation is implemented using the \c poll()  function.

    Although the class provides a default constructor, the default constructor doesn't create a "usable" wait objects  wrapping a handle resp. file descriptor.
    Valid instances of Pylon::WaitObject cannot be created by the application, instead the pylon libraries return fully created wait objects.
    The Pylon::WaitObjectEx class can be used to create wait objects that can be controlled by the application.

    The Pylon::WaitObject class provides access to the wrapped handle resp. file descriptor. This allows to use  to allow use pylon wait objects as input for
    "native" APIs like \c WaitForMultipleObjects() (Windows),  and \c poll() (Linux).

    Multiple Pylon::WaitObjects can be put in the Pylon::WaitObjects container class allowing to wait "simultaneously" for multiple events.


    \ingroup PYLON_PUBLIC
    */
    // ----------------------------------------------------------------------
    class PYLONBASE_API WaitObject
    {
        // -------------------------------
        // Platform independent
        // -------------------------------
    public:
        /// Constructs an "empty" wait object, i.e., the wait object is not attached to a platform dependent wait object (IsValid() == false)
        /** The Pylon::WaitObjectEx class can be used to create wait objects controllable by an application. */
        WaitObject();
        /// Destructor
        virtual ~WaitObject();
        /// Copy constructor (duplicates the wrapped handle/file descriptor)
        WaitObject( const WaitObject& );
        /// Assignment operator (duplicates the wrapped handle/file descriptor)
        WaitObject& operator=( const WaitObject& );

        /// Suspend calling thread for specified time.
        /**
        \param ms wait time in ms
        */
        static void Sleep( unsigned long ms );

    public:
        /// Checks if the wait object is valid.
        /**
        Don't call the  Wait methods() for an invalid wait object. Wait objects returned by the pylon libraries are valid.
        \return true if the object contains a valid handle/file descriptor
        */
        bool IsValid() const;

    public:
        /// Wait for the object to be signaled
        /**
        \param timeout timeout in ms
        \return false when the timeout has been expired, true when the waiting was successful before
        the timeout has been expired.
        */
        bool Wait( unsigned int timeout ) const;

        /// Wait for the object to be signaled  (interruptible)
        /**

        \param timeout timeout in ms
        \param bAlertable    When the bAlertable parameter is set to true, the function waits until either the timeout elapses, the object enters
        the signaled state, or the wait operation has been interrupted.
        For Windows, the wait operation is interrupted by queued APCs or I/O completion routines.
        For Linux, the wait operation can be interrupted by signals.

        \return The returned Pylon::EWaitExResult  value indicates the result of the wait operation.

        */
        EWaitExResult WaitEx( unsigned int timeout, bool bAlertable ) const;


        // -------------------------------
        // Windows-specific stuff
        // -------------------------------
    public:
        /// Constructor taking existing handle (duplicate=false -> take ownership like std:auto_ptr)
        /** This method allows to wrap an existing windows handle that can be used with the \c WaitForSingleObject() and
        \c WaitForMultipleObjects methods. */
        WaitObject( WaitObject_t h, bool duplicate = true );


#if defined(PYLON_WIN_BUILD)
        /// conversion operator
        /** \return the native Win32 handle wrapped by the WaitObject. (Not supported by pylon4Linux) */
        operator WaitObject_t() const;

    protected:
        WaitObject_t Duplicate( WaitObject_t h ) const;

    protected:
        WaitObject_t m_Native;
#endif


#if defined (PYLON_UNIX_BUILD)

        /// Invalidates the internal wait object.
        void Destroy();

    protected:

        WaitObject_t m_pWaitObjectPosix;

        // -------------------------------
        // Linux specific stuff
        // -------------------------------
    public:

        /// Getter for file descriptor
        /** \return the file descriptor wrapped by the WaitObject. When the file descriptor is added to the file descriptor set indicated by the
        GetReadyMask() method, the \c select() or poll() function can be used to wait for pylon and non-pylon events simultaneously.
        */
        int GetFd( void ) const;

        /// Indicates to what kind of file descriptor set the wrapped file descriptor must be put for usage with the \c select() or poll() function.
        ready_mask_t GetReadyMask() const;

        /// conversion operator
        /** \return the internal wait object handle. (Not supported by pylon4Windows) */
        operator struct _WaitObjectPosix_t* () const;

        /// Accessor to internal wait object (not supported by pylon for Windows)
        WaitObject_t& GetWaitObject();
#endif

    };


    // ----------------------------------------------------------------------
    /*!
    \brief A wait object that the user may signal
    \ingroup PYLON_PUBLIC
    */
    // ----------------------------------------------------------------------
    class PYLONBASE_API WaitObjectEx : public WaitObject
    {
        // -------------------------------
        // Platform independent
        // -------------------------------
    public:
        /// Creates an event object (manual reset event)
        static WaitObjectEx Create( bool initiallySignalled = false );


        /// Constructs an "empty" wait object, i.e., the wait object is not attached to a platform dependent wait object (IsValid() == false)
        /** Use the static WaitObjectEx::Create() method to create instances of the WaitObjectEx class instead. */
        WaitObjectEx();

        /// Destroys the waitobject
        virtual ~WaitObjectEx()
        {
        }
    public:
        /// Set the object to signaled state
        void Signal();
        /// Reset the object to unsignaled state
        void Reset();

    public:
        // -------------------------------
        // Windows and OSX specific stuff
        // -------------------------------
#if defined(PYLON_WIN_BUILD) || defined(PYLON_OSX_BUILD)
        /// Constructor using an existing windows handle (duplicate=false -> take ownership like std:auto_ptr)
        explicit WaitObjectEx( WaitObject_t h, bool duplicate = true );
#endif

        // -------------------------------
        // Linux specific stuff
        // -------------------------------
#if defined(PYLON_UNIX_BUILD)
        /// Constructor using an existing Linux file descriptor
        explicit WaitObjectEx( int fd );
#endif
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__WAITOBJECT_H__
