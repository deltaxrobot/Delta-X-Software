#pragma once

//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/**
  * \file     PylonVersion.h
  * \ingroup  Miscellaneous Files
  *
  * \brief   Definition of the version info resource for the pylon project
  *
  */
//-----------------------------------------------------------------------------

// Set to 1/0 the following lines as appropriate.
#define PYLON_VERSION_PRERELEASE    0
#define PYLON_VERSION_PRIVATEBUILD  0

/* Nothing below this point has to be modified to adjust version data.
 *-------------------------------------------------------------------*/

#include <pylon/PylonVersionNumber.h>

#ifdef _DEBUG
#define PYLON_DEBUGSTRING " (debug)"
#else
#define PYLON_DEBUGSTRING ""
#endif

#ifndef PYLON_FILE_DESCRIPTION
#if defined(PYLON_DRV)
#define PYLON_FILE_DESCRIPTION(name) #name " Device Driver\0"
#elif defined(PYLON_CPL)
#define PYLON_FILE_DESCRIPTION(name) #name " Control Panel\0"
#elif defined(PYLON_EXE)
#define PYLON_FILE_DESCRIPTION(name) #name " Application\0"
#else
#define PYLON_FILE_DESCRIPTION(name) #name " Module\0"
#endif
#endif

#if PYLON_VERSION_PRIVATEBUILD
#define PYLON_FILE_FLAGS2 VS_FF_PRIVATEBUILD
#else
#define PYLON_FILE_FLAGS2 0
#endif

#ifdef _DEBUG
#define PYLON_FILE_FLAGS PYLON_FILE_FLAGS2|VS_FF_DEBUG
#elif PYLON_VERSION_PRERELEASE
#define PYLON_FILE_FLAGS PYLON_FILE_FLAGS2|VS_FF_PRERELEASE
#else
#define PYLON_FILE_FLAGS 0
#endif


#if defined(PYLON_DRV)
#define PYLON_FILETYPE VFT_DRV
#define PYLON_FILESUBTYPE VFT2_DRV_INSTALLABLE
#define PYLON_ORIGINAL_FILENAME(name) #name ".sys\0"
#elif defined(PYLON_CPL)
#define PYLON_FILETYPE VFT_DLL
#define PYLON_FILESUBTYPE VFT2_UNKNOWN
#define PYLON_ORIGINAL_FILENAME(name) #name ".cpl\0"
#elif defined(PYLON_EXE)
#define PYLON_FILETYPE VFT_APP
#define PYLON_FILESUBTYPE VFT2_UNKNOWN
#define PYLON_ORIGINAL_FILENAME(name) #name ".exe\0"
#else
#define PYLON_FILETYPE VFT_DLL
#define PYLON_FILESUBTYPE VFT2_UNKNOWN
#define PYLON_ORIGINAL_FILENAME(name) #name ".dll\0"
#endif

#ifndef PYLON_VERSIONSTRING_COMMENT
#define PYLON_VERSIONSTRING_COMMENT ""
#endif


#define PYLON_VERSION(name, priv) \
    LANGUAGE LANG_NEUTRAL, SUBLANG_NEUTRAL \
      VS_VERSION_INFO VERSIONINFO \
      FILEVERSION PYLON_VERSION_MAJOR, PYLON_VERSION_MINOR, PYLON_VERSION_SUBMINOR, PYLON_VERSION_BUILD \
      PRODUCTVERSION PYLON_VERSION_MAJOR, PYLON_VERSION_MINOR, PYLON_VERSION_SUBMINOR, PYLON_VERSION_BUILD \
      FILEFLAGSMASK VS_FFI_FILEFLAGSMASK \
      FILEFLAGS PYLON_FILE_FLAGS \
      FILEOS VOS_NT_WINDOWS32 \
      FILETYPE PYLON_FILETYPE \
      FILESUBTYPE PYLON_FILESUBTYPE \
    BEGIN \
        BLOCK "StringFileInfo" \
        BEGIN \
            BLOCK "000004b0" \
            BEGIN \
                VALUE "Comments", PYLON_VERSIONSTRING_COMMENT "\0" \
                VALUE "CompanyName", "Basler\0" \
                VALUE "FileDescription", PYLON_FILE_DESCRIPTION(name) "\0" \
                VALUE "FileVersion", PYLON_VERSIONSTRING_MAJOR "." PYLON_VERSIONSTRING_MINOR "." PYLON_VERSIONSTRING_SUBMINOR "." PYLON_VERSIONSTRING_BUILD PYLON_DEBUGSTRING "\0" \
                VALUE "InternalName", #name "\0" \
                VALUE "LegalCopyright", "Copyright (c) 2006-2021 Basler AG\0" \
                VALUE "LegalTrademarks", "\0" \
                VALUE "OLESelfRegister", "\0" \
                VALUE "OriginalFilename", PYLON_ORIGINAL_FILENAME(name) \
                VALUE "PrivateBuild", "\0" \
                VALUE "ProductName", "Basler pylon\0" \
                VALUE "ProductVersion", PYLON_VERSIONSTRING_MAJOR "." PYLON_VERSIONSTRING_MINOR "." PYLON_VERSIONSTRING_SUBMINOR "." PYLON_VERSIONSTRING_BUILD " " PYLON_VERSIONSTRING_EXTENSION PYLON_DEBUGSTRING "\0" \
                VALUE "SpecialBuild", #priv \
            END \
        END \
        BLOCK "VarFileInfo" \
        BEGIN \
            VALUE "Translation", 0x0000, 0x04b0 \
        END \
    END
