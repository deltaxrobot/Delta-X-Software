//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2008-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/** \file
\brief Maps GenICam/GenApi types to pylon namespace
*/

#pragma once

#include <Base/GCNamespace.h>
#include <Base/GCTypes.h>
#include <Base/GCString.h>
#include <Base/GCStringVector.h>
#include <Base/GCException.h>

#include <GenApi/GenApiNamespace.h>
#include <GenApi/Synch.h>

#include <pylon/Platform.h> // for PYLON_PACKING

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    /// Pylon's string definition
    typedef GENICAM_NAMESPACE::gcstring String_t;

    /// Pylon's string list definition
    typedef GENICAM_NAMESPACE::gcstring_vector StringList_t;

    // pull genicam exceptions into the pylon namespace
    // we provide mappings so the user can use the Pylon namespace and don't have to think about
    // whether to use GenApi or GENICAM_NAMESPACE namespace

    using GENICAM_NAMESPACE::GenericException;
    using GENICAM_NAMESPACE::BadAllocException;
    using GENICAM_NAMESPACE::InvalidArgumentException;
    using GENICAM_NAMESPACE::OutOfRangeException;
    using GENICAM_NAMESPACE::PropertyException;
    using GENICAM_NAMESPACE::RuntimeException;
    using GENICAM_NAMESPACE::LogicalErrorException;
    using GENICAM_NAMESPACE::AccessException;
    using GENICAM_NAMESPACE::TimeoutException;
    using GENICAM_NAMESPACE::DynamicCastException;

    // locks
    using GENAPI_NAMESPACE::CLock;
    using GENAPI_NAMESPACE::AutoLock;

    // INodeMap, INode etc. are not mapped


// this is only used for documentation purpose
#ifdef DOXYGEN_INVOKED
    /**
    \brief pylon exception class

    This is pylons exception class. It is also used as a base class for all other pylon exceptions.
    To catch all pylon and genicam exceptions it is sufficient to catch GenericException.
    */
    class GenericException
    {
    public:
        /// Constructs an exception
        GenericException( const char* pDescription, const char* pSourceFileName, unsigned int SourceLine );
        /// Returns error description
        virtual const char* GetDescription() const throw();
        /// Returns the filename of the file where the exception was thrown
        virtual const char* GetSourceFileName() const throw();
        /// Returns the line number of the file where the exception was thrown
        virtual unsigned int GetSourceLine() const throw();
        /// Returns a descriptive text of the exception
        virtual const char* what() const throw();
    };

    /// Exception thrown if memory could not be allocated
    DECLARE_PYLON_EXCEPTION( BadAllocException );

    /// Exception thrown if an argument passed is invalid
    DECLARE_PYLON_EXCEPTION( InvalidArgumentException );

    /// Exception thrown if an argument is out of range
    DECLARE_PYLON_EXCEPTION( OutOfRangeException );

    /// Exception thrown if a property access fails
    DECLARE_PYLON_EXCEPTION( PropertyException );

    /// Exception thrown if a runtime error occurs
    DECLARE_PYLON_EXCEPTION( RuntimeException );

    /// Exception thrown to indicate logical errors in program flow
    DECLARE_PYLON_EXCEPTION( LogicalErrorException );

    /// Exception thrown to indicate an access error. (i.E. A when trying to set a read-only value)
    DECLARE_PYLON_EXCEPTION( AccessException );

    /// Exception thrown when a timeout has elapsed.
    DECLARE_PYLON_EXCEPTION( TimeoutException );

    /// Exception thrown to indicate a dynamic cast has failed. Usually this means a value is not of expected type.
    DECLARE_PYLON_EXCEPTION( DynamicCastException );

    /**
    \brief A simple recursive lock class.
    \sa AutoLock
    */
    class CLock
    {
    public:
        /// Constructs a lock object. The lock is not initially locked.
        CLock();
        ~CLock();

        /// Tries to acquire the lock. If the lock currently locked by another thread the function returns immediately and returns false.
        bool TryLock();

        /// Acquires the lock. If the lock is currently held by another thread the function waits until the other thread releases the lock.
        void Lock();

        /// Releases the lock.
        void Unlock();
    };

    /**
    \brief A scoped lock class to acquire and release a CLock upon creation and destruction

    Use this class to created scoped lock.
    To acquire the lock just create a CAutoLock object. When the object will be destroyed it will automatically release the lock.
    \code
int SampleFunction(Pylon::CLock & lock)
{
    // acquire lock
    Pylon::AutoLock scopedLock(lock);

    // perform operation requiring lock to be held here

    return 1;

    // lock will be released automatically when scopedLock goes out of scope and is destroyed
}
    \endcode
    \sa CLock
    */
    class AutoLock
    {
        /// Locks the CLock object passed in the parameter lock
        AutoLock( CLock& lock );
        /// Releases the CLock object passed in the constructor
        ~AutoLock();
    };

#endif

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
