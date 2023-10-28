//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file
\brief    Pixeltypemapper for mapping GenICam pixel format enumerations to pylon pixel type enumeration
\ingroup  PYLON_PUBLIC
*/

#ifndef PYLON_PIXEL_TYPE_MAPPER_H_INCLUDED_
#define PYLON_PIXEL_TYPE_MAPPER_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenApi/IEnumerationT.h>
#include <pylon/PylonBase.h>
#include <pylon/PixelType.h>

namespace Pylon
{
    class CPixelTypeMapperImpl;

    /// Specifies the SFNC version.
    enum SFNCVersion
    {
        SFNCVersion_Invalid = 0,   //!< Invalid or unknown SFNC version 
        SFNCVersion_pre2_0  = 1,   //!< SFNC version prior to 2.0
        SFNCVersion_2_0     = 200  //!< SFNC version 2.0
        // if you ad entries here you must change GetStartIndexForSFNC accordingly
    };

    // -------------------------------------------------------------------------
    // class CPixelTypeMapper
    // -------------------------------------------------------------------------
    /*!
    \brief A simple pixeltypemapper (maps device specific pixelformats read from device-node map to pylon pixeltypes by their name).

    \ingroup  PYLON_PUBLIC

    Use this mapper to convert a device specifc Pylon::PixelFormat value to a Pylon::EPixelType used for PixelFormatConverters.
    When passing the symbolic name of the pixeltype you can use the static function CPixelTypeMapper::GetPylonPixelTypeByName().
    If you want to convert a nodeValue you must first create a CPixelTypeMapper instance and pass the constructor a pointer the PixelFormat node of the device
    you want the node value to be converted. Then call CPixelTypeMapper::GetPylonPixelTypeFromNodeValue() to get the corresponding Pylon::EPixelType.
    */
    class PYLONBASE_API CPixelTypeMapper
    {
    public:
        /// Create an empty mapper.
        /// Before calling any non-static function you must call SetPixelFormatEnumNode to initialize the mapper.
        CPixelTypeMapper( void );

        /// create and initialize a mapper by using the enum node passed.
        explicit CPixelTypeMapper( GENAPI_NAMESPACE::IEnumeration* pEnum );

        /// default d'tor
        virtual ~CPixelTypeMapper( void );

    public:

        /*! \brief  Checks the objects validity
            \return Returns true if the object is initialized properly.

            Essentially this function checks whether you've called SetPixelFormatEnumNode.
        */
        bool IsValid() const;

        /*! \brief Lazy initialization of the object.
            \param pEnum Pointer to the enumeration node containing the PixelFormats.

             Call this function initialize the mapper when using the default c'tor.
        */
        void SetPixelFormatEnumNode( GENAPI_NAMESPACE::IEnumeration* pEnum );

    public:
        /*! \brief Converts an enumeration node value to a Pylon::EPixelType enum

            \param nodeValue node value to convert. You can obtain this value by calling GENAPI_NAMESPACE::IEnumeration::GetIntValue.
            \return Returns the Pylon::EPixelType for a given pixelformat enum value defined in the Enum passed in c'tor

            Converts a enumeration node value to a Pylon::EPixelType enum.
            You must have initialized the mapper before you can call this function.
        */
        EPixelType GetPylonPixelTypeFromNodeValue( int64_t nodeValue ) const;

    public:
        /*! \brief Returns a Pylon::EPixelType for a given symbolic name.
            \param pszSymbolicName pointer to the symbolic name. Note: Symbolic names are case sensitive. You can obtain the symbolic name by calling GENAPI_NAMESPACE::IEnumEntry::GetSymbolic()
            \return Returns the Pylon_PixelType for a given symbolic name.

            Static version which does the lookup soley by symbolic string comparison.
            Passing "Mono16" will return Pylon::PixelType_Mono16. If the name is not found Pylon::PixelType_Undefined will be returned.
        */
        static EPixelType GetPylonPixelTypeByName( const char* pszSymbolicName );

        /*! \brief Returns a Pylon::EPixelType for a given symbolic name.
            \param symbolicName The symbolic name. Note: Symbolic names are case sensitive. You can obtain the symbolic name by calling GENAPI_NAMESPACE::IEnumEntry::GetSymbolic()
            \return Returns the Pylon_PixelType for a given symbolic name.

            Static version which does the lookup solely by symbolic string comparison.
            Passing "Mono16" will return Pylon::PixelType_Mono16. If the name is not found Pylon::PixelType_Undefined will be returned.
        */
        static EPixelType GetPylonPixelTypeByName( const String_t& symbolicName )
        {
            return GetPylonPixelTypeByName( symbolicName.c_str() );
        }

        /*! \brief Static function that returns a string representation of the given EPixelType.
            \param pixelType The pixel type to return the name for.
            \param sfncVer SFNC Version to use when doing the mapping. Some names have been changed in SFNC 2.0
            \return Returns the pointer to a null terminated string representing the symbolic name of the pixel type.

            Passing Pylon::PixelType_Mono16 will return "Mono16" will be returned. If the pixel type is not known an empty string is returned.

            \note The returned name cannot be used to parameterize the pixel format of a camera device, because the camera's pixel format name can be
                  different. The camera's pixel format name depends on the used standard feature naming convention (SFNC).
        */
        static const char* GetNameByPixelType( EPixelType pixelType, SFNCVersion sfncVer = SFNCVersion_pre2_0 );

    private:
        CPixelTypeMapperImpl* m_pImpl;
    };


    // -------------------------------------------------------------------------
    // class CCameraPixelTypeMapperT
    // -------------------------------------------------------------------------
    /*!
    \brief A camera specific pixeltypemapper (maps device specific pixelformats contained in the generated camera classes to pylon pixeltypes by their name).

    \ingroup  PYLON_PUBLIC

    Use this mapper to convert a PixelTypeEnums or ChunkPixelFormatEnums enum values to a Pylon_PixelType used for PixelTypeConverter creation.
    When passing the symbolic name of the pixeltype you can use the static version GetPylonPixelTypeByName. This function will do the lookup everytime you call it.
    The non-static member function GetPylonPixelTypeFromPixelFormatEnum uses caching to speed up subsequent calls.

    The template parameter EnumT is the enumeration type from the camera class (typically Basler_GigECamera::PixelFormatEnums for GigE cameras or Basler_IIDC1394CameraParams::PixelFormatEnums for 1394 cameras)
    */
    template <typename EnumT>
    class CCameraPixelTypeMapperT : protected CPixelTypeMapper
    {
    public:
        /// Create an empty mapper. Before calling any non-static function
        CCameraPixelTypeMapperT( void )
            : m_pEnumT( NULL )
        {
        }

        /// create a mapper by using the enum node passed.
        explicit CCameraPixelTypeMapperT( GENAPI_NAMESPACE::IEnumerationT<EnumT>* pEnumT )
            : m_pEnumT( NULL )
        {
            SetPixelFormatEnumNode( pEnumT );
        }

        virtual ~CCameraPixelTypeMapperT( void )
        {
            m_pEnumT = NULL;
        }

    public:

        /*! \brief  Checks the objects validity
            \return Returns true if the object is initialized properly.

            Essentially this function checks whether you've called SetPixelFormatEnumNode.
        */
        bool IsValid() const
        {
            return m_pEnumT != NULL && CPixelTypeMapper::IsValid();
        }


        /*! \brief Lazy initialization of the object.
            \param pEnumT Pointer to the enumeration node containing the PixelFormats.

            Call this function initialize the mapper when using the default c'tor.
        */
        void SetPixelFormatEnumNode( GENAPI_NAMESPACE::IEnumerationT<EnumT>* pEnumT )
        {
            // remember a reference to the EnumerationT node. Needed for enum->nodeValue lookup
            m_pEnumT = pEnumT;

            if (pEnumT != NULL)
            {
                CPixelTypeMapper::SetPixelFormatEnumNode( pEnumT );
            }
            else
            {
                CPixelTypeMapper::SetPixelFormatEnumNode( NULL );
            }
        }


    public:
        /*! \brief Converts a enumeration node value to a Pylon::EPixelType enum

            \param pixelFormatEnumValue enumeration value to convert. You obtain this value by calling GENAPI_NAMESPACE::IEnumerationT::GetValue.
            \return Returns the Pylon::EPixelType for a given pixelformat enum value defined in the enum node passed in c'tor

            Converts a enumeration node value to a Pylon::EPixelType enum.
            You must have initialized the mapper before you can call this function.
        */
        EPixelType GetPylonPixelTypeFromPixelFormatEnum( EnumT pixelFormatEnumValue ) const
        {
            if (!IsValid())
            {
                throw RUNTIME_EXCEPTION( "SetPixelFormatEnumNode not called." );
            }

            EPixelType pt = PixelType_Undefined;
            GENAPI_NAMESPACE::IEnumEntry* pE = m_pEnumT->GetEntry( pixelFormatEnumValue );
            if (pE != NULL)
            {
                pt = CPixelTypeMapper::GetPylonPixelTypeFromNodeValue( pE->GetValue() );
            }
            return pt;
        }

    public:
        /*! \copydoc CPixelTypeMapper::GetPylonPixelTypeByName(const char*)
        */
        static EPixelType GetPylonPixelTypeByName( const char* pszSymbolicName )
        {
            return CPixelTypeMapper::GetPylonPixelTypeByName( pszSymbolicName );
        }

        /*! \copydoc CPixelTypeMapper::GetPylonPixelTypeByName(const String_t&)
        */
        static EPixelType GetPylonPixelTypeByName( const String_t& symbolicName )
        {
            return CPixelTypeMapper::GetPylonPixelTypeByName( symbolicName.c_str() );
        }

        /*! \copydoc CPixelTypeMapper::GetNameByPixelType(EPixelType, SFNCVersion sfncVer = SFNCVersion_pre2_0)
        */
        static const char* GetNameByPixelType( EPixelType pixelType, SFNCVersion sfncVer = SFNCVersion_pre2_0 )
        {
            return CPixelTypeMapper::GetNameByPixelType( pixelType, sfncVer );
        }

    private:
        GENAPI_NAMESPACE::IEnumerationT<EnumT>* m_pEnumT;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif // #ifndef PYLON_PIXEL_TYPE_MAPPER_H_INCLUDED_
