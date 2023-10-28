//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief    Declaration of methods to control the thread priority
*/
#ifndef __THREADPRIORITY_H__
#define __THREADPRIORITY_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include "PylonBase.h"


namespace Pylon
{

#if defined(PYLON_WIN_BUILD)
    /** \brief Typedef for a Win32 thread handle
    \ingroup PYLON_PUBLIC */
    typedef HANDLE THREADHANDLE;
#elif defined(PYLON_HAS_POSIX_THREADS)
    /** \brief Typedef for a pthreads thread handle */
    typedef pthread_t THREADHANDLE;
#else
#  error Platform not supported.
#endif

    /**
    \brief Queries the range of allowed thread priorities
    \ingroup PYLON_PUBLIC
    */
    void PYLONBASE_API GetRTThreadPriorityCapabilities( int& prioMin, int& prioMax );
    /**
    \brief Indicates the current thread priority of a thread
    \ingroup PYLON_PUBLIC
    */
    int PYLONBASE_API GetRTThreadPriority( THREADHANDLE thread );

    /**
    \brief Allows to set the realtime thread priority of a thread
    \ingroup PYLON_PUBLIC

    \if windows
    This method allows to raise a thread's priority into the range
    of "realtime" thread priorities. The methods can control each thread
    independently. This means that it it not necessary to raise the process to the
    "realtime" priority class, which would affect all thread of the process.

    If the process is not in the realtime priority class and if the process has the
    SE_INC_BASE_PRIORITY_NAME privilege, values from 15 to 31 can be set. If the
    privilege is not granted, only 15 can be set.

    If the process is in the realtime priority class,
    values from 16 to 31 can be set. No special permissions are required.

    To grant the privilege, use the Windows policy editor to enable the
    SE_INC_BASE_PRIORITY_NAME right (User Rights Assignment / Increase scheduling policy).
    Typically, all members of the Administrators group have the privilege enabled.

    Caution: Do not change the process priority class after setting the realtime thread priority.
    \endif

    \if linux
    Values greater than 0 set the thread's static priority and imply realtime scheduling
    (SCHED_RR scheduling policy). When setting the value 0, non-realtime scheduling is used.
    The thread's dynamic priority depends on the process' dynamic priority (nice scheduling).

    Setting realtime priorities requires certain permissions. The pylon install guide described
    how to grant an application the permissions to set realtime thread priorities.

    \endif

    \if osx
    Values greater than 0 set the thread's static priority and imply realtime scheduling
    (THREAD_TIME_CONSTRAINT_POLICY scheduling policy). When setting the value 0, non-realtime
    scheduling is used and the thread's static priority is set to the highest possible depends
    on the process dynamic priority (nice scheduling).

    \endif

    Typically a thread that receives image data should be set to realtime thread priorities
    to reduce jitter and delays. Be aware that such a realtime thread shouldn't perform time
    consuming tasks (like image processing). A realtime thread that is continuously working can
    cause the whole operating system to be blocked!
    */
    void PYLONBASE_API SetRTThreadPriority( THREADHANDLE thread, int priority );

    /**
    \brief Get current running thread handle.

    This wrapper method return the handle of the current running thread.
    */
    inline THREADHANDLE GetCurrentThreadHandle()
    {
#if defined(PYLON_WIN_BUILD)
        return ::GetCurrentThread();
#elif defined(PYLON_HAS_POSIX_THREADS)
        return pthread_self();
#else
#  error Platform not supported.
#endif
    }

    /**
    \brief Get current running thread id.

    This wrapper method return the id of the current running thread.
    */
    inline int GetCurrentThreadIdentifier()
    {
#if defined(PYLON_WIN_BUILD)
        return static_cast<int>(::GetCurrentThreadId());
#elif defined(PYLON_LINUX_BUILD)
        return static_cast<int>(pthread_self());
#elif defined(PYLON_HAS_POSIX_THREADS)
        return reinterpret_cast<long int>(pthread_self());
#else
#  error Platform not supported.
#endif
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__THREADPRIORITY_H__
