//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains a smart pointer that holds a reference to grab result data.
*/

#ifndef INCLUDED_GRABRESULTPTR_H_4356898
#define INCLUDED_GRABRESULTPTR_H_4356898

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/GrabResultData.h>
#include <pylon/Image.h>

namespace Pylon
{
    namespace PylonPrivate
    {
        class CGrabResultDataConverter;
    }

    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /*!
    \class  CGrabResultPtr
    \brief  A smart pointer holding a reference to grab result data.

    This class is used for distributing the grab result data of a camera. It controls
    the reuse and lifetime of the referenced buffer. When all smart pointers referencing
    a buffer go out of scope the referenced buffer is reused or destroyed.
    The data and the held buffer are still valid after the camera object it originated from
    has been destroyed.
    \attention The grabbing will stop with an input queue underrun, when the grab results are
    never released, e.g. when put into a container.

    The CGrabResultPtr class provides a cast operator that allows passing the grab result directly to functions or methods
    that take an const IImage& as parameter, e.g. image saving functions or image format converter methods.

    \attention The returned reference to IImage is only valid as long the CGrabResultPtr object it came from is not destroyed.

    \threading Instances of CGrabResultPtr referencing the same grab result can be used from any thread context.
    */
    class PYLONBASE_API CGrabResultPtr
    {
    public:
        /*!
        \brief Creates a smart pointer.
        \post No grab result is referenced.
        */
        CGrabResultPtr();


        /*!
        \brief Creates a copy of a smart pointer.

        \param[in] rhs Another smart pointer, source of the result data to reference.

        The data itself is not copied.

        \post
        <ul>
        <li>Another reference to the grab result of the source is held if it references a grab result.
        <li>No grab result is referenced if the source does not reference a grab result.
        </ul>

        \error
            Still valid after error.
        */
        CGrabResultPtr( const CGrabResultPtr& rhs );


        /*!
        \brief Assignment of a smart pointer.

        \param[in] rhs Another smart pointer, source of the result data to reference.

        The data itself is not copied.

        \post
        <ul>
        <li>The currently referenced data is released.
        <li>Another reference to the grab result of the source is held if it references a grab result.
        <li>No grab result is referenced if the source does not reference a grab result.
        </ul>

        \error
            Still valid after error.
        */
        CGrabResultPtr& operator = ( const CGrabResultPtr& rhs );


        /*!
        \brief Destroys the smart pointer.

        \post The currently referenced data is released.

        \error
            Does not throw C++ exceptions.
        */
        ~CGrabResultPtr();


        /*!
        \brief Allows accessing the referenced data.

        \return The pointer to the grab result data.

        \pre The pointer must reference a grab result.
        IsValid() or the overloaded bool operator can be used to check whether data is referenced.

        \error
            Still valid after error. Throws an exception when no data is referenced.
        */
        CGrabResultData* operator->() const;


        /*!
        \brief Check whether data is referenced.

        \return True if data is referenced.

        \error
            Does not throw C++ exceptions.
        */
        bool IsValid() const;


        /*!
        \brief Check whether data is referenced.

        \return IsValid().

        The overloaded bool operator can be used to check whether data is referenced.
        Example:
        \code
        if ( grabResult)
        {
            grabResult->GetStatus();
        }
        \endcode

        \error
            Does not throw C++ exceptions.
        */
        operator bool() const;


        /*!
        \brief The currently referenced data is released.

        \post The currently referenced data is released.

        \error
            Still valid after error.
        */
        void Release();


        /*!
        \brief Provides an IImage interface to the grab result.

        This cast operator allows passing the grab result to saving functions or image format converter.
        The returned image is invalid if the grab was not successful, see CGrabResultData::GrabSucceeded().

        \attention The returned reference is only valid as long the grab result ptr is not destroyed.

        \error
            Still valid after error.
        */
        operator IImage& () const;


        /*!
        \brief Indicates that the held grab result data and buffer is only referenced by this grab result.

        \return Returns true if the held grab result data and buffer is only referenced by this grab result. Returns false if the grab result is invalid.

        \error
            Does not throw C++ exceptions.
        */
        bool IsUnique() const;


        /// Internal use only.
        class CGrabResultPtrImpl;
        CGrabResultPtr& operator = ( const CGrabResultPtrImpl& rhs );
    private:
        /// Internal use only.
        friend class PylonPrivate::CGrabResultDataConverter;
        CGrabResultData* GetPtr() const;
        mutable CGrabResultPtrImpl* m_pImpl;
        CGrabResultData* m_pGrabResultData;
    };

    /**
     * @}
     */
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_GRABRESULTPTR_H_4356898 */
