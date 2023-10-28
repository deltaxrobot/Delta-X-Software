/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2012-2021 Basler AG
    http://www.baslerweb.com
-----------------------------------------------------------------------------*/
/*!
    \file
    \brief  Contains PylonAviCompressionOptions_t definition.
*/
#ifndef INCLUDED_PYLONAVICOMPRESSIONOPTIONS_H_6841242
#define INCLUDED_PYLONAVICOMPRESSIONOPTIONS_H_6841242

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable : 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif

#include <vfw.h>

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#include <pylonc/PylonCDefines.h>

#pragma pack(push, PYLONC_PACKING)

/** \addtogroup pylon pylon Interface
* @{
*/

/** \brief Wraps the AVI compression options of the Video for Window API. File PylonAviCompressionOptions.h has to be included.
*/
typedef struct tag_PylonAviCompressionOptions_t
{
    HWND hParentWindow;                     /*!< \brief Optional handle to the parent window for the Compression Options dialog box. See the Video for Windows API AviSaveOptions() MSDN documentation. */
    _Bool showDialog;                       /*!< \brief Optionally show Compression Options dialog box. See the Video for Windows API AviSaveOptions() MSDN documentation. */
    _Bool userDialogReturnOk;               /*!< \brief Is set to true in the call to the CAviWriter::Open() method if the user pressed OK in the dialog. The compression is not set up if cancel has been pressed. */
    LONG autoKeyFrameInsertionRate;         /*!< \brief Indicates to insert a key frame every nth image when KeyFrameSelection_Auto is used. */
    AVICOMPRESSOPTIONS compressionOptions;  /*!< \brief The AVICOMPRESSOPTIONS structure needs to be set up with the four character code identifying the codec and the parameter settings of the codec.
                                                        For more information, see the MSDN documentation of the Video for Windows API and the documentation of the codec you are using. */
} PylonAviCompressionOptions_t;

/**
* @}
*/

#pragma pack(pop, PYLONC_PACKING)

#endif /* INCLUDED_PYLONAVICOMPRESSIONOPTIONS_H_6841242 */
