//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2009-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  JS
//-----------------------------------------------------------------------------
/*!
\file
\brief  Contains the VersionInfo class, which is a utility for comparing version numbers.
*/

#ifndef INCLUDED_PYLONVERSIONINFO_H_3453485
#define INCLUDED_PYLONVERSIONINFO_H_3453485

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/PylonBase.h>

namespace Pylon
{

    /**
    \class  VersionInfo
    \brief  Holds a four-part version number consisting of major.minor.subminor.build

    This class stores a four-part version number and provides comparison operators.
    If you use the constructor with one parameter, the version info object will be
    initialized with pylon base version numbers.

    You can also call the static getVersionString() method to retrieve
    a string containing the complete version separated by dots.
    */
    class VersionInfo
    {
    public:
        /// Constructs a version info object using pylon base version numbers.
        /// If checkBuild is set to false, the build number will not be used in comparison operators.
        explicit VersionInfo( bool checkBuild = false )
            : m_major( 0 )
            , m_minor( 0 )
            , m_subminor( 0 )
            , m_build( 0 )
            , m_checkBuild( checkBuild )
        {
            Pylon::GetPylonVersion( &m_major, &m_minor, &m_subminor, &m_build );
        }


        /// Constructs a version info object using the version number parts passed.
        VersionInfo( unsigned int major,
                     unsigned int minor,
                     unsigned int subminor )
            : m_major( major )
            , m_minor( minor )
            , m_subminor( subminor )
            , m_build( 0 )
            , m_checkBuild( false )
        {
        }


        /// Constructs a version info object using the version number parts passed.
        VersionInfo( unsigned int major,
                     unsigned int minor,
                     unsigned int subminor,
                     unsigned int build )
            : m_major( major )
            , m_minor( minor )
            , m_subminor( subminor )
            , m_build( build )
            , m_checkBuild( true )
        {
        }


        /// The VersionInfo destructor.
        ~VersionInfo( void )
        {
        }

    public:
        /// Returns the complete version number as a string.
        static const char* getVersionString()
        {
            return Pylon::GetPylonVersionString();
        }


        /// Returns the major version number.
        /// For version 2.1.3.1234 the value 2 would be returned.
        unsigned int getMajor() const
        {
            return m_major;
        }


        /// Returns the minor version number.
        /// For version 2.1.3.1234 the value 1 would be returned.
        unsigned int getMinor() const
        {
            return m_minor;
        }


        /// Returns the subminor version number.
        /// For version 2.1.3.1234 the value 3 would be returned.
        unsigned int getSubminor() const
        {
            return m_subminor;
        }


        /// Returns the build number.
        /// For version 2.1.3.1234 the value 1234 would be returned.
        unsigned int getBuild() const
        {
            return m_build;
        }

    public:
        /// Compares two version info objects.
        bool operator > ( const VersionInfo& rhs ) const
        {
            bool res = (m_major > rhs.m_major)
                || (m_major == rhs.m_major && m_minor > rhs.m_minor)
                || (m_major == rhs.m_major && m_minor == rhs.m_minor && m_subminor > rhs.m_subminor)
                || (m_major == rhs.m_major && m_minor == rhs.m_minor && m_subminor == rhs.m_subminor && m_checkBuild && m_build > rhs.m_build);

            return res;
        }


        /// Compares two version info objects.
        bool operator == ( const VersionInfo& rhs ) const
        {
            // use the reverse order to save some executiontime ;-)
            bool res( (m_checkBuild ? (m_build == rhs.m_build) : true)
                      && (m_subminor == rhs.m_subminor)
                      && (m_minor == rhs.m_minor)
                      && (m_major == rhs.m_major) );
            return res;
        }


        /// Compares two version info objects.
        bool operator >= ( const VersionInfo& rhs ) const
        {
            bool res = (*this > rhs) || (*this == rhs);
            return res;
        }


        /// Compares two version info objects.
        bool operator < ( const VersionInfo& rhs ) const
        {
            bool res = !(*this >= rhs);
            return res;
        }


        /// Compares two version info objects.
        bool operator != ( const VersionInfo& rhs ) const
        {
            bool res = !(*this == rhs);
            return res;
        }


        /// compares two version info objects.
        bool operator <= ( const VersionInfo& rhs ) const
        {
            bool res = !(*this > rhs);
            return res;
        }

    protected:
        unsigned int    m_major;
        unsigned int    m_minor;
        unsigned int    m_subminor;
        unsigned int    m_build;
        bool            m_checkBuild;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_PYLONVERSIONINFO_H_3453485 */
