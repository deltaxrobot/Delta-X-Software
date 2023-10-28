//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2018-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for Video Writer

The parameter class is used by the \c Pylon::CVideoWriter class.
The \c Pylon::CVideoWriter can be used to create video files in the MP4 format. The \ref sample_Utility_GrabVideo code sample shows the use of the Video Writer class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_VIDEOWRITERPARAMS_H
#define BASLER_PYLON_VIDEOWRITERPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_VideoWriterParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for CompressionMode
    enum CompressionModeEnums
    {
        CompressionMode_Bitrate,  //!< The resulting stream has a constant bit rate
        CompressionMode_Quality  //!< The resulting stream has a constant quality
    };


    
    
    //**************************************************************************************************
    // Parameter class CVideoWriterParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for Video Writer

    The parameter class is used by the \c Pylon::CVideoWriter class.
    The \c Pylon::CVideoWriter can be used to create video files in the MP4 format. The \ref sample_Utility_GrabVideo code sample shows the use of the Video Writer class.
    */
    class PYLONBASE_API CVideoWriterParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CVideoWriterParams_Params_v6_2_0( void );

        //! Destructor
        ~CVideoWriterParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CVideoWriterParams_Params_v6_2_0_Data;
        CVideoWriterParams_Params_v6_2_0_Data* m_pCVideoWriterParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: RecordingOptions
        //@{
        /*!
            \brief Bit rate of the resulting compressed stream


            Visibility: Beginner

        */
        Pylon::IIntegerEx& Bitrate;

        //@}


        //! \name Categories: Statistics
        //@{
        /*!
            \brief Bytes written to file since starting the recording


            Visibility: Beginner

        */
        Pylon::IIntegerEx& BytesWritten;

        //@}


        //! \name Categories: RecordingOptions
        //@{
        /*!
            \brief Sets the compression mode

            Sets the compression mode. You can choose whether to keep the bit rate or the quality of the resulting video stream constant.

            Visibility: Beginner

        */
        Pylon::IEnumParameterT<CompressionModeEnums>& CompressionMode;

        //@}


        //! \name Categories: Statistics
        //@{
        /*!
            \brief Number of frames written since starting the recording


            Visibility: Beginner

        */
        Pylon::IIntegerEx& FrameCount;

        //@}


        //! \name Categories: ImageParameters
        //@{
        /*!
            \brief Height of the image (in pixels)


            Visibility: Invisible

        */
        Pylon::IIntegerEx& Height;

        //@}


        //! \name Categories: RecordingOptions
        //@{
        /*!
            \brief Frame rate (in Hertz) of the video to be recorded


            Visibility: Beginner

        */
        Pylon::IFloatEx& PlaybackFrameRate;

        //@}


        //! \name Categories: RecordingOptions
        //@{
        /*!
            \brief Quality of the resulting compressed stream

            Quality of the resulting compressed stream. The quality has a direct influence on the resulting bit rate. The optimal bit rate is calculated based on the input values height, width, and playback frame rate (WIDTH * HEIGHT * PLAYBACKFRAMERATE * 0.25). This is then normalized to the quality value range 1-100, where 100 corresponds to the optimum bit rate and 1 to the lowest bit rate.

            Visibility: Beginner

        */
        Pylon::IFloatEx& Quality;

        //@}


        //! \name Categories: RecordingOptions
        //@{
        /*!
            \brief Number of threads used for recording the video


            Visibility: Expert

        */
        Pylon::IIntegerEx& ThreadCount;

        //@}


        //! \name Categories: ImageParameters
        //@{
        /*!
            \brief Width of the image (in pixels)


            Visibility: Invisible

        */
        Pylon::IIntegerEx& Width;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CVideoWriterParams_Params_v6_2_0(CVideoWriterParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CVideoWriterParams_Params_v6_2_0& operator=(CVideoWriterParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for Video Writer

    The parameter class is used by the \c Pylon::CVideoWriter class.
    The \c Pylon::CVideoWriter can be used to create video files in the MP4 format. The \ref sample_Utility_GrabVideo code sample shows the use of the Video Writer class.
    */
    class CVideoWriterParams_Params : public CVideoWriterParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CVideoWriterParams_Params( void )
        {
        }

        //! Destructor
        ~CVideoWriterParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CVideoWriterParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_VideoWriterParams

#endif // BASLER_PYLON_VIDEOWRITERPARAMS_H
