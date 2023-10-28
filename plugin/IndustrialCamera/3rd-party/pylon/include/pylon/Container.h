//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of the DeviceInfoList_t, TLInfoList_t, and InterfaceInfoList_t classes
*/

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>
#include <pylon/DeviceInfo.h>
#include <pylon/TlInfo.h>
#include <pylon/InterfaceInfo.h>
#include <vector>


namespace Pylon
{
    // ---------------------------------------------------------------------------
    ///
    /// \brief STL std::vector like container class.
    /*!
    //  Based on the GenICam::gcstring_vector class.
    */
    // ---------------------------------------------------------------------------
    template <class T>
    class PYLONBASE_API TList
    {
    public:
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;

        // Nested types
        // ---------------------------------------------------------------------------
    public:

        // \brief Const iterator for the DeviceInfoList container.
        class PYLONBASE_API const_iterator
        {
            // iterator traits
            // ------------------------------------------------------------------------
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;
            // Ctor / Dtor
            // -------------------------------------------------------------------------
        public:
            const_iterator( T* pPtr = 0 );

            // Operators
            // -------------------------------------------------------------------------
        public:
            const T& operator *        ( void )                  const;
            const T* operator ->       ()                       const;
            const_iterator& operator ++       ( void );
            const_iterator          operator ++       ( int );
            const_iterator& operator --       ( void );
            const_iterator          operator --       ( int );
            const_iterator& operator +=       ( const intptr_t& iInc );
            const_iterator          operator +        ( intptr_t iInc )         const;
            const_iterator& operator -=       ( const intptr_t& iDec );
            intptr_t                operator -        ( const const_iterator& iter ) const;
            const_iterator          operator -        ( intptr_t iDec )         const;
            const T& operator []       ( intptr_t iIndex )       const;
            bool                    operator ==       ( const const_iterator& iter ) const;
            bool                    operator !=       ( const const_iterator& iter ) const;
            bool                    operator <        ( const const_iterator& iter ) const;
            bool                    operator >        ( const const_iterator& iter ) const;
            bool                    operator <=       ( const const_iterator& iter ) const;
            bool                    operator >=       ( const const_iterator& iter ) const;
            template <class U> PYLONBASE_API friend typename TList<T>::const_iterator operator +( intptr_t iInc, const typename TList<T>::const_iterator& iter );

            // Member
            // -------------------------------------------------------------------------
        protected:
            T* _ps;
        };

        class PYLONBASE_API iterator :
            public const_iterator
        {
        public:
            // iterator traits
            // -------------------------------------------------------------------------
            typedef std::random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef ptrdiff_t  difference_type;
            typedef T* pointer;
            typedef T& reference;
            // Ctor / Dtor
            // -------------------------------------------------------------------------
        public:
            iterator( T* pPtr = 0 );

            // Operators
            // -------------------------------------------------------------------------
        public:
            T& operator *        ( void )                  const;
            T* operator ->       ()                       const;
            iterator& operator ++       ( void );
            iterator                operator ++       ( int );
            iterator& operator --       ( void );
            iterator                operator --       ( int );
            iterator& operator +=       ( const intptr_t& iInc );
            iterator                operator +        ( intptr_t iInc )         const;
            iterator& operator -=       ( const intptr_t& iDec );
            intptr_t                operator -        ( const iterator& iter )  const;
            iterator                operator -        ( intptr_t iDec )         const;
            T& operator []       ( intptr_t iIndex )       const;
            template <class U> PYLONBASE_API friend typename TList<T>::iterator operator +( intptr_t iInc, const typename TList<T>::iterator& iter );
        };

        // Ctor / Dtor
        // ---------------------------------------------------------------------------
    public:
        TList( void );
        explicit                  TList( size_t uiSize );
        TList( const TList& obj );
        virtual                   ~TList( void );

        // Element access
        // ---------------------------------------------------------------------------
    public:
        virtual void              assign( size_t n, const T& val );
        virtual void              clear( void );
        virtual iterator          erase( iterator pos );
        virtual T& at( size_t uiIndex );
        virtual const T& at( size_t uiIndex )        const;
        virtual T& back( void );
        virtual const T& back( void )                  const;
        virtual iterator          begin( void );
        virtual const_iterator    begin( void )                  const;
        virtual size_t            capacity( void )                  const;
        virtual iterator          end( void );
        virtual const_iterator    end( void )                  const;
        virtual T& front( void );
        virtual const T& front( void )                  const;
        virtual size_t            max_size( void )                  const;
        virtual size_t            size( void )                  const;
        virtual iterator          insert( iterator pos, const T& val );
        virtual bool              empty( void )                  const;
        virtual void              pop_back( void );
        virtual void              push_back( const T& val );
        virtual void              resize( size_t uiSize );
        virtual void              reserve( size_t uiSize );

        // Do not use - only left in for backwards compatibility!
        virtual void              erase( size_t uiIndex );
        virtual void              insert( size_t uiIndex, const T& val );

// Operators
        // ---------------------------------------------------------------------------
    public:
        TList& operator =        ( const TList& obj );
        T& operator []       ( size_t uiIndex );
        const T& operator []       ( size_t uiIndex )        const;
        void                      operator delete   (void* pWhere);
        void* operator new      (size_t uiSize);

        // Member
        // ---------------------------------------------------------------------------
    private:
        typedef std::vector<T, std::allocator<T> > vector_t;
        vector_t* _pv;
    };


    // ---------------------------------------------------------------------------
    /// \brief Gets the sum of the given \a iInc and the given \a iter.
    ///
    /// \param[in] iInc Increment from which the sum is calculated.
    /// \param[in] iter Iterator from which the sum is calculated.
    /// \return Sum of iterator.
    // ---------------------------------------------------------------------------
    template<class T>
    typename TList<T>::iterator PYLONBASE_API operator +( intptr_t iInc, const typename TList<T>::iterator& iter );


#ifndef PYLONBASE_EXPORT_TEMPLATE
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4231 4910) // Nonstandard extension used : 'extern' before template explicit instantiation
#endif
    extern template class PYLONBASE_API TList<CDeviceInfo>;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif

    /////////////////////////////////////////////////////////////////////////////////////////
    //
    //   DeviceInfoList
    //
    /////////////////////////////////////////////////////////////////////////////////////////

    ///
    /// \brief STL std::vector like container for Pylon::CDeviceInfo objects.
    /*!
    // \ingroup Pylon_TransportLayer
    */
    // ---------------------------------------------------------------------------
    class PYLONBASE_API DeviceInfoList : public TList<CDeviceInfo>
    {
    public:
        DeviceInfoList( void );
        explicit DeviceInfoList( size_t uiSize );
        DeviceInfoList( const DeviceInfoList& obj );

        virtual ~DeviceInfoList( void );

    };

    /// \copybrief Pylon::DeviceInfoList
    /*! \copydoc Pylon::DeviceInfoList */
    typedef DeviceInfoList DeviceInfoList_t;

    /////////////////////////////////////////////////////////////////////////////////////////
    //
    //   TlInfoList
    //
    /////////////////////////////////////////////////////////////////////////////////////////

    // ---------------------------------------------------------------------------
    /*!
    // \brief STL std::vector like container for Pylon::CTlInfo objects.
    //
    // \ingroup Pylon_TransportLayer
    */
    // ---------------------------------------------------------------------------
    class PYLONBASE_API TlInfoList : public TList<CTlInfo>
    {
    public:
        TlInfoList( void );
        explicit TlInfoList( size_t uiSize );
        TlInfoList( const TlInfoList& obj );

        virtual ~TlInfoList( void );

    };

    /*!
    \copybrief Pylon::TlInfoList
    \copydoc Pylon::TlInfoList
    */
    typedef TlInfoList TlInfoList_t;


    /////////////////////////////////////////////////////////////////////////////////////////
    //
    //   InterfaceInfoList
    //
    /////////////////////////////////////////////////////////////////////////////////////////

    // ---------------------------------------------------------------------------
    /*!
    // \brief STL std::vector like container for Pylon::CInterfaceInfo objects.
    //
    */
    // ---------------------------------------------------------------------------
    class PYLONBASE_API InterfaceInfoList : public TList<CInterfaceInfo>
    {
    public:
        InterfaceInfoList( void );
        explicit InterfaceInfoList( size_t uiSize );
        InterfaceInfoList( const InterfaceInfoList& obj );

        virtual ~InterfaceInfoList( void );

    };

    /*!
    \copybrief Pylon::InterfaceInfoList
    \copydoc Pylon::InterfaceInfoList
    */
    typedef InterfaceInfoList InterfaceInfoList_t;

}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__CONTAINER_H__
