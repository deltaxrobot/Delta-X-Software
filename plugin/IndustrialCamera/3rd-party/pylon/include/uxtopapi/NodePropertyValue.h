#pragma once

#include <uxtopapi/UxTopDll.h>

#pragma pack(push, 8)

namespace topapi
{

    /// Value type.
    enum EValueType
    {
          // ValueType must not exceed 7 bit
        ValueType_Empty = 0,    //!< Denotes an empty value.
        ValueType_Int32 = 1,  //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_UInt32 = 2, //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_Int64 = 3,  //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_UInt64 = 4, //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_Double = 5, //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_String = 6, //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h

        ValueType_ArrayInt32 = (ValueType_Int32 | 0x80),   //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_ArrayUInt32 = (ValueType_UInt32 | 0x80), //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_ArrayInt64 = (ValueType_Int64 | 0x80),   //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_ArrayUInt64 = (ValueType_UInt64 | 0x80), //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_ArrayDouble = (ValueType_Double | 0x80), //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
        ValueType_ArrayString = (ValueType_String | 0x80) //!< these must match NODEPROP_TYPE_ values in NodePropertyKeys.h
    };


    /// Property value of a node.
    struct NodePropertyValue
    {
        EValueType vt; ///< value type
        /// value
        union
        {
            int32_t         Int32;          ///< Value of type int32_t
            uint32_t        UInt32;         ///< Value of type uint32_t
            int64_t         Int64;          ///< Value of type int64_t
            uint64_t        UInt64;         ///< Value of type uint64_t
            double          Double;         ///< Value of type double
            wchar_t* pString;        ///< Wide character string value

            int32_t* pArrayInt32;    ///< int32_t array
            uint32_t* pArrayUInt32;   ///< uint32_t array
            int64_t* pArrayInt64;    ///< int64_t array
            uint64_t* pArrayUInt64;   ///< uint64_t array
            double* pArrayDouble;   ///< double array
            wchar_t** pArrayString;   ///< Wide character string array
        } v;

        /// Constructor for an empty node property value
        UX_TOPAPI NodePropertyValue();

        /**
        \brief Copy constructor
        \param right Node property value to copy.
        */
        UX_TOPAPI NodePropertyValue( const NodePropertyValue& right );

        // type specific c'tors

        /**
        \brief Constructor
        \param val Value of type int32_t.
        */
        UX_TOPAPI NodePropertyValue( int32_t val );

        /**
        \brief Constructor
        \param val Value of type uint32_t.
        */
        UX_TOPAPI NodePropertyValue( uint32_t val );

        /**
        \brief Constructor
        \param val Value of type int64_t.
        */
        UX_TOPAPI NodePropertyValue( int64_t val );

        /**
        \brief Constructor
        \param val Value of type uint64_t.
        */
        UX_TOPAPI NodePropertyValue( uint64_t val );

        /**
        \brief Constructor
        \param val Value of type double.
        */
        UX_TOPAPI NodePropertyValue( double val );

        /**
        \brief Constructor
        \param pszw Wide character string.
        */
        UX_TOPAPI NodePropertyValue( const wchar_t* pszw );

        /**
        \brief Constructor
        \param pInt32 Array of int32_t.
        \param numElements Number of elements of aray pInt32 points to.
        */
        UX_TOPAPI NodePropertyValue( const int32_t* pInt32, size_t numElements );

        /**
        \brief Constructor
        \param pUInt32 Array of uint32_t.
        \param numElements Number of elements of aray pUInt32 points to.
        */
        UX_TOPAPI NodePropertyValue( const uint32_t* pUInt32, size_t numElements );

        /**
        \brief Constructor
        \param pInt64 Array of int64_t.
        \param numElements Number of elements of aray pInt64 points to.
        */
        UX_TOPAPI NodePropertyValue( const int64_t* pInt64, size_t numElements );

        /**
        \brief Constructor
        \param pUInt64 Array of uint64_t.
        \param numElements Number of elements of aray pUInt64 points to.
        */
        UX_TOPAPI NodePropertyValue( const uint64_t* pUInt64, size_t numElements );

        /**
        \brief Constructor
        \param pDouble Array of double.
        \param numElements Number of elements of aray pDouble points to.
        */
        UX_TOPAPI NodePropertyValue( const double* pDouble, size_t numElements );

        /**
        \brief Constructor
        \param ppString Array of wide character strings (more precise: array of pointers).
        \param numElements Number of elements of aray pDouble points to.
        */
        UX_TOPAPI NodePropertyValue( const wchar_t* const* ppString, size_t numElements );

        /// dtor will call Clear()
        UX_TOPAPI ~NodePropertyValue();

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( const NodePropertyValue& );

        // assignment

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( int32_t valInt32 );

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( uint32_t valUInt32 );

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( int64_t );

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( uint64_t );

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( double );

        /// Assignment operator
        UX_TOPAPI NodePropertyValue& operator = ( const wchar_t* );

        /// Assignment operator
        UX_TOPAPI bool Assign( const NodePropertyValue& );

        /// Assignment operator
        UX_TOPAPI bool Assign( int32_t );

        /// Assignment operator
        UX_TOPAPI bool Assign( uint32_t );

        /// Assignment operator
        UX_TOPAPI bool Assign( int64_t );

        /// Assignment operator
        UX_TOPAPI bool Assign( uint64_t );

        /// Assignment operator
        UX_TOPAPI bool Assign( double );

        /// Assignment operator
        UX_TOPAPI bool Assign( const wchar_t* );

        /// Assignment operator
        UX_TOPAPI bool Assign( const int32_t*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool Assign( const uint32_t*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool Assign( const int64_t*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool Assign( const uint64_t*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool Assign( const double*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool Assign( const wchar_t* const*, size_t numElements );

        /// Assignment operator
        UX_TOPAPI bool operator == ( const NodePropertyValue& other ) const;

        /// Assignment operator
        UX_TOPAPI bool operator != ( const NodePropertyValue& other ) const;

        /// compare one value against another
        UX_TOPAPI int  Compare( const NodePropertyValue& other ) const;

        /// Returns true if node property value is empty, false otherwise.
        UX_TOPAPI bool IsEmpty() const;

        /// Returns true if the object could extract a size_t value(s)
        UX_TOPAPI bool IsSizeT() const;

        /// Extracts a size_t object.
        UX_TOPAPI size_t GetAsSizeT() const;

        /// Extracts a size_t array object.
        UX_TOPAPI size_t* GetAsSizeTArray() const;

        // array helpers

        /// Returns true if node property value is an array, false otherwise.
        UX_TOPAPI bool IsArray() const;

        /// Returns 0 if node property value is not an array, returns the number of elements if node property value is an array.
        UX_TOPAPI size_t GetNumElements() const;

        /// clear value or free memory depending on type
        UX_TOPAPI void Clear();

        /// Allocate memory so user can fill the value directly
        UX_TOPAPI bool AllocateString( size_t numChars );
    };
} // namespace topapi

#pragma pack(pop)
