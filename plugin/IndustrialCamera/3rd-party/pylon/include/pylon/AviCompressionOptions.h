//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2011-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains compression options declaration for the AviWriter class.
*/
#ifndef INCLUDED_AVICOMPRESSIONOPTIONS_H_6841242
#define INCLUDED_AVICOMPRESSIONOPTIONS_H_6841242

#include <pylon/Platform.h>
#include <pylon/stdinclude.h>

#ifdef PYLON_WIN_BUILD

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif
#include <vfw.h>
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    /** \addtogroup Pylon_ImageHandlingSupport
     * @{
     */

    ///Wraps the AVI compression options of the Video for Window API
    struct SAviCompressionOptions
    {

        /*!
        \brief Create the compression options structure.

            To use compression set up the AVICOMPRESSOPTIONS structure.
            You can use the dialog provided by the Video for Windows API to do this by setting \c optionalShowDialog to true.
            Alternatively, fill the AVICOMPRESSOPTIONS structure with the four character code identifying the codec
            and the parameter settings of the codec.
            For more information, see the MSDN documentation of the Video for Windows API and the documentation of the codec you are using.

            \param[in]   optionalShowDialog Optionally show the Compression Options dialog box.
                                            The dialog allows to set the compression parameters.
                                            See the Video for Windows API AviSaveOptions() MSDN documentation.
            \param[in]   optionalHParentWindow  Optional handle to the parent window for the Compression Options dialog box.
                                                See the Video for Windows API AviSaveOptions() MSDN documentation.
        */
        SAviCompressionOptions( bool optionalShowDialog = false, HWND optionalHParentWindow = NULL )
            : hParentWindow( optionalHParentWindow )
            , showDialog( optionalShowDialog )
            , userDialogReturnOk( false )
            , autoKeyFrameInsertionRate( 20 )
        {
            ::ZeroMemory( &compressionOptions, sizeof( compressionOptions ) );
        }

        /*!
        \brief Create the compression options structure. Preset some compression options.

            To use compression set up the AVICOMPRESSOPTIONS structure.
            You can use the dialog provided by the Video for Windows API to do this by setting \c optionalShowDialog to true.
            Alternatively, fill the AVICOMPRESSOPTIONS structure with the four character code identifying the codec
            and the parameter settings of the codec.
            For more information, see the MSDN documentation of the Video for Windows API and the documentation of the codec you are using.

            \param[in]   fourCharacterCode  The four character code identifying the codec to use for compression.
            \param[in]   optionalShowDialog Optionally show the Compression Options dialog box.
                                            The dialog allows to set the compression parameters.
                                            See the Video for Windows API AviSaveOptions() MSDN documentation.
            \param[in]   optionalHParentWindow  Optional handle to the parent window for the Compression Options dialog box.
                                                See the Video for Windows API AviSaveOptions() MSDN documentation.
        */
        SAviCompressionOptions( const char* fourCharacterCode, bool optionalShowDialog = false, HWND optionalHParentWindow = NULL )
            : hParentWindow( optionalHParentWindow )
            , showDialog( optionalShowDialog )
            , userDialogReturnOk( false )
            , autoKeyFrameInsertionRate( 20 )
        {
            ::ZeroMemory( &compressionOptions, sizeof( compressionOptions ) );

            //Set compression.
            compressionOptions.dwFlags = AVICOMPRESSF_VALID;

            //Handle the case if the code passes has fewer than four characters.
            String_t fourCharacterCodeLocal( fourCharacterCode );
            fourCharacterCodeLocal += "    ";
            fourCharacterCodeLocal.resize( 4 );

            //Set four character code.
            compressionOptions.fccHandler = mmioFOURCC( fourCharacterCodeLocal[0], fourCharacterCodeLocal[1], fourCharacterCodeLocal[2], fourCharacterCodeLocal[3] );
        }

        HWND hParentWindow; ///< Optional handle to the parent window for the Compression Options dialog box. See the Video for Windows API AviSaveOptions() MSDN documentation.
        bool showDialog; ///< Optionally show Compression Options dialog box. See the Video for Windows API AviSaveOptions() MSDN documentation.
        bool userDialogReturnOk; ///< Is set to true in the call to the CAviWriter::Open() method if the user pressed OK in the dialog. The compression is not set up if cancel has been pressed.
        LONG autoKeyFrameInsertionRate; ///< Indicates to insert a key frame every nth image when KeyFrameSelection_Auto is used.
        AVICOMPRESSOPTIONS compressionOptions; ///< The AVICOMPRESSOPTIONS structure needs to be set up with the four character code identifying the codec and the parameter settings of the codec.
                                               ///< For more information, see the MSDN documentation of the Video for Windows API and the documentation of the codec you are using.
    };

    /**
     * @}
     */
}

#else

//No AVI support for Linux.

#endif


#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_AVICOMPRESSIONOPTIONS_H_6841242 */
