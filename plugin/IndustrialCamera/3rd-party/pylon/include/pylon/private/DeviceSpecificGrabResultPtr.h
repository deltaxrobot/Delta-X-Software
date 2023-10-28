//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Andreas Gau
//-----------------------------------------------------------------------------
/*!
\file
\brief Contains a smart pointer that holds a reference to device specific grab result data.
*/

#ifndef INCLUDED_DEVICESPECIFICGRABRESULTPTR_H_9329951
#define INCLUDED_DEVICESPECIFICGRABRESULTPTR_H_9329951

#include <pylon/GrabResultPtr.h>

#define PYLON_DEFINE_DEVICE_SPECIFIC_GRAB_RESULT_PTR(ClassName, ResultDataName) \
    class ClassName : public CDeviceSpecificGrabResultPtr<ResultDataName> \
    { \
    public: \
        /*!
            \copybrief Pylon::CGrabResultPtr::CGrabResultPtr()
            \copydetails Pylon::CGrabResultPtr::CGrabResultPtr()
        */ \
            ClassName() \
        { \
        } \
        /*!
            \copybrief Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
            \copydetails Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
        */ \
            ClassName( const CGrabResultPtr& rhs ) \
            : CDeviceSpecificGrabResultPtr<ResultDataName>( rhs ) \
        { \
        } \
        /*!
            \copybrief Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
            \copydetails Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
        */ \
            ClassName( const ClassName& rhs ) \
            : CDeviceSpecificGrabResultPtr<ResultDataName>( rhs ) \
        { \
        } \
        /*!
            \copybrief Pylon::CGrabResultPtr::~CGrabResultPtr
            \copydetails Pylon::CGrabResultPtr::~CGrabResultPtr
        */ \
            virtual ~ClassName() \
        { \
        } \
    };


    namespace Pylon
    {

        namespace PylonPrivate
        {
            // Internal use only. This is subject to change without notice.
            class CGrabResultDataConverter
            {
            public:
                // Internal use only. This is subject to change without notice.
                template <typename GrabResultDataT>
                static void Convert( GrabResultDataT*& ptr, CGrabResultPtr& target, const CGrabResultPtr& source )
                {
                    ptr = dynamic_cast<GrabResultDataT*>(source.GetPtr());
                    if (ptr)
                    {
                        target = source;
                    }
                }
            };
        }

        /*!
             \brief Implementation Detail: Header only implementation class for creating device specific grab result ptrs.
             \copydetails Pylon::CGrabResultPtr
        */
        template <typename GrabResultDataT>
        class CDeviceSpecificGrabResultPtr
        {
        public:
            /*!
                \copybrief Pylon::CGrabResultPtr::CGrabResultPtr
                \copydetails Pylon::CGrabResultPtr::CGrabResultPtr
            */
            CDeviceSpecificGrabResultPtr();


            /*!
            \brief Creates a copy of a smart pointer.

            \param[in] rhs Another smart pointer, source of the result data to reference.
            The data itself is not copied.

            \post
            <ul>
            <li>Another reference to the grab result of the source is held if it references a grab result.
            <li>No grab result is referenced if the source does not reference a grab result or if the result data is not convertible.
            </ul>

            \error
                Still valid after error.
            */
            CDeviceSpecificGrabResultPtr( const CGrabResultPtr& rhs );


            /*!
            \brief Assignment of a smart pointer.

            \param[in] rhs Another smart pointer, source of the result data to reference.

            The data itself is not copied.

            \post
            <ul>
            <li>The currently referenced data is released.
            <li>Another reference to the grab result of the source is held if it references a grab result.
            <li>No grab result is referenced if the source does not reference a grab result or if the result data is not convertible.
            </ul>

            \error
                Still valid after error.
            */
            CDeviceSpecificGrabResultPtr<GrabResultDataT>& operator = ( const CGrabResultPtr& rhs );


            /*!
                \copybrief Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
                \copydetails Pylon::CGrabResultPtr::CGrabResultPtr( const CGrabResultPtr& rhs)
            */
            CDeviceSpecificGrabResultPtr( const CDeviceSpecificGrabResultPtr<GrabResultDataT>& rhs );


            /*!
                \copybrief Pylon::CGrabResultPtr::operator=( const CGrabResultPtr& rhs)
                \copydetails Pylon::CGrabResultPtr::operator=( const CGrabResultPtr& rhs)
            */
            CDeviceSpecificGrabResultPtr<GrabResultDataT>& operator = ( const CDeviceSpecificGrabResultPtr<GrabResultDataT>& rhs );


            /*!
                \copybrief Pylon::CGrabResultPtr::~CGrabResultPtr
                \copydetails Pylon::CGrabResultPtr::~CGrabResultPtr
            */
            virtual ~CDeviceSpecificGrabResultPtr();


            /*!
                \copybrief Pylon::CGrabResultPtr::operator->()
                \copydetails Pylon::CGrabResultPtr::operator->()
            */
            GrabResultDataT* operator->() const;


            /*!
                \copybrief Pylon::CGrabResultPtr::IsValid
                \copydetails Pylon::CGrabResultPtr::IsValid
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
            */
            operator CGrabResultPtr() const;


            /*!
            \brief Provides an IImage interface to the grab result.

            This cast operator allows passing the grab result to saving functions or image format converter.
            The returned image is invalid if the grab was not successful. See CGrabResultData::GrabSucceeded().

            \attention The returned reference is only valid as long the grab result ptr is not destroyed.

            \error
                Still valid after error.
            */
            operator IImage& () const;


            /*!
            \brief Indicates that the held grab result data and buffer are only referenced by this grab result.

            \return Returns true if the held grab result data and buffer are only referenced by this grab result. Returns false if the grab result is invalid.

            \error
                Does not throw C++ exceptions.
            */
            bool IsUnique() const;


            /*!
                \copybrief Pylon::CGrabResultPtr::Release
                \copydetails Pylon::CGrabResultPtr::Release
            */
            void Release();

        private:
            GrabResultDataT* m_pGrabResultData;
            CGrabResultPtr m_gptr;
        };






        // Implementation ----------------------------------------------------------

        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::CDeviceSpecificGrabResultPtr()
            : m_pGrabResultData( 0 )
        {
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::CDeviceSpecificGrabResultPtr( const CGrabResultPtr& rhs )
        {
            PylonPrivate::CGrabResultDataConverter::Convert<GrabResultDataT>( m_pGrabResultData, m_gptr, rhs );
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>& CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator = ( const CGrabResultPtr& rhs )
        {
            PylonPrivate::CGrabResultDataConverter::Convert<GrabResultDataT>( m_pGrabResultData, m_gptr, rhs );
            return *this;
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::CDeviceSpecificGrabResultPtr( const CDeviceSpecificGrabResultPtr<GrabResultDataT>& rhs )
            : m_pGrabResultData( rhs.m_pGrabResultData )
            , m_gptr( rhs.m_gptr )
        {
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>& CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator = ( const CDeviceSpecificGrabResultPtr<GrabResultDataT>& rhs )
        {
            if (this != &rhs) // self-assignment check
            {
                m_pGrabResultData = rhs.m_pGrabResultData;
                m_gptr = rhs.m_gptr;
            }
            return *this;
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::~CDeviceSpecificGrabResultPtr()
        {
        }


        template <typename GrabResultDataT>
        GrabResultDataT* CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator->() const
        {
            if (!IsValid())
            {
                throw RUNTIME_EXCEPTION( "No grab result data is referenced. Cannot access NULL pointer." );
            }
            return m_pGrabResultData;
        }


        template <typename GrabResultDataT>
        bool CDeviceSpecificGrabResultPtr<GrabResultDataT>::IsValid() const
        {
            return m_pGrabResultData != NULL;
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator bool() const
        {
            return IsValid();
        }


        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator CGrabResultPtr() const
        {
            return m_gptr;
        }

        template <typename GrabResultDataT>
        CDeviceSpecificGrabResultPtr<GrabResultDataT>::operator IImage& () const
        {
            return m_gptr;
        }

        template <typename GrabResultDataT>
        bool CDeviceSpecificGrabResultPtr<GrabResultDataT>::IsUnique() const
        {
            return m_gptr.IsUnique();
        }

        template <typename GrabResultDataT>
        void CDeviceSpecificGrabResultPtr<GrabResultDataT>::Release()
        {
            m_pGrabResultData = NULL;
            m_gptr.Release();
        }
    }

#endif /* INCLUDED_DEVICESPECIFICGRABRESULTPTR_H_9329951 */
