//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AH
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of Transport layer information object
*/

#ifndef __TLINFO_H__
#define __TLINFO_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>
#include <pylon/Info.h>

namespace Pylon
{
    namespace Key
    {
        ///Identifies the filename of the GenTL producer [GenTL consumer only].
        const char* const FileNameKey = "FileName";
        ///Identifies the InfoID of the GenTL producer [GenTL consumer only].
        const char* const InfoIDKey = "InfoID";
        ///Identifies the filename of the GenTL producer.
        const char* const VersionKey = "Version";
    } // namespace Key

    /**
        \ingroup Pylon_TransportLayer
        \brief Class used for storing the result of the transport
               layer enumeration process.

    Enumerating the available Transport Layer objects returns a list of
    CTlInfo objects (Pylon::TlInfoList_t). A CTlInfo object holds information
    about the enumerated transport layer.
    */
    class PYLONBASE_API CTlInfo : public CInfoBase
    {
    public:
        ///Retrieves the filename of the GenTL producer [GenTL consumer only].
        ///This property is identified by Key::FileNameKey.
        String_t GetFileName() const;
        ///Sets the above property.
        CTlInfo& SetFileName( const String_t& value );
        ///Returns true if the above property is available.
        bool IsFileNameAvailable() const;

        ///Retrieves the InfoID of the GenTL producer [GenTL consumer only].
        ///This property is identified by Key::VendorNameKey.
        String_t GetInfoID() const;
        ///Sets the above property.
        CTlInfo& SetInfoID( const String_t& value );
        ///Returns true if the above property is available.
        bool IsInfoIDAvailable() const;

        ///Retrieves the model name of the data producer
        ///This property is identified by Key::ModelNameKey.
        String_t GetModelName() const;
        ///Sets the above property.
        CTlInfo& SetModelName( const String_t& value );
        ///Returns true if the above property is available.
        bool IsModelNameAvailable() const;

        ///Retrieves the version of the transport layer.
        ///This property is identified by Key::VersionKey.
        String_t GetVersion() const;
        ///Sets the above property.
        CTlInfo& SetVersion( const String_t& value );
        ///Returns true if the above property is available.
        bool IsVersionAvailable() const;
    };
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* __TLINFO_H__ */
