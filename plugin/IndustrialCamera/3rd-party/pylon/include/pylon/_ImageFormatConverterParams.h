//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for Image Format Converter

The parameter class is used by the \c Pylon::CImageFormatConverter class.
The \c Pylon::CImageFormatConverter creates new images by converting a source image to a different format.
Once the format converter is configured it can convert almost all image formats supported by Basler camera devices.
The \ref sample_Utility_ImageFormatConverter code sample shows the use of the Image Format Converter class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_IMAGEFORMATCONVERTERPARAMS_H
#define BASLER_PYLON_IMAGEFORMATCONVERTERPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_ImageFormatConverterParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for InconvertibleEdgeHandling
    enum InconvertibleEdgeHandlingEnums
    {
        InconvertibleEdgeHandling_Clip,  //!< Rows and columns that can't be converted are removed from the output image - Applies to: ImageFormatConverter
        InconvertibleEdgeHandling_Extend,  //!< Rows and columns that can't be converted are filled by extrapolating image data from neighboring rows and columns - Applies to: ImageFormatConverter
        InconvertibleEdgeHandling_SetZero  //!< Rows and columns that can't be converted are set to zero - Applies to: ImageFormatConverter
    };

    //! Valid values for MonoConversionMethod
    enum MonoConversionMethodEnums
    {
        MonoConversionMethod_Gamma,  //!< When converting images, Gamma conversion is used - Applies to: ImageFormatConverter
        MonoConversionMethod_Truncate  //!< When converting images, image data is shifted - Applies to: ImageFormatConverter
    };

    //! Valid values for OutputBitAlignment
    enum OutputBitAlignmentEnums
    {
        OutputBitAlignment_LsbAligned,  //!< Image data is aligned with the least significant bit - Applies to: ImageFormatConverter
        OutputBitAlignment_MsbAligned  //!< The data is aligned at the most significant bit - Applies to: ImageFormatConverter
    };

    //! Valid values for OutputOrientation
    enum OutputOrientationEnums
    {
        OutputOrientation_BottomUp,  //!< The last row of the image is located at the start of the image buffer - Applies to: ImageFormatConverter
        OutputOrientation_TopDown,  //!< The first row of the image is located at the start of the image buffer - Applies to: ImageFormatConverter
        OutputOrientation_Unchanged  //!< The orientation of the image remains the same - Applies to: ImageFormatConverter
    };


    
    
    //**************************************************************************************************
    // Parameter class CImageFormatConverterParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for Image Format Converter

    The parameter class is used by the \c Pylon::CImageFormatConverter class.
    The \c Pylon::CImageFormatConverter creates new images by converting a source image to a different format.
    Once the format converter is configured it can convert almost all image formats supported by Basler camera devices.
    The \ref sample_Utility_ImageFormatConverter code sample shows the use of the Image Format Converter class.
    */
    class PYLONBASE_API CImageFormatConverterParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CImageFormatConverterParams_Params_v6_2_0( void );

        //! Destructor
        ~CImageFormatConverterParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CImageFormatConverterParams_Params_v6_2_0_Data;
        CImageFormatConverterParams_Params_v6_2_0_Data* m_pCImageFormatConverterParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: MonoConversion
        //@{
        /*!
            \brief Additional shifting value used for converting monochrome images - Applies to: ImageFormatConverter

            Additional shifting value used for converting monochrome images. Only effective if the Mono Conversion Method parameter is set to Truncate. If the parameter value isn't zero, the image data is converted using a lookup table. Shifted values exceeding the maximum output value boundary are set to the maximum allowed value. Negative values are treated as right-shifted values.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& AdditionalLeftShift;

        //@}


        //! \name Categories: MonoConversion
        //@{
        /*!
            \brief Gamma value for converting monochrome images - Applies to: ImageFormatConverter

            Gamma value for converting monochrome images. The image data is converted using a lookup table.

            Visibility: Beginner

        */
        Pylon::IFloatEx& Gamma;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets how to handle rows and columns that can't be converted - Applies to: ImageFormatConverter


            Visibility: Beginner

        */
        Pylon::IEnumParameterT<InconvertibleEdgeHandlingEnums>& InconvertibleEdgeHandling;

        //@}


        //! \name Categories: MonoConversion
        //@{
        /*!
            \brief Sets the conversion method for monochrome images - Applies to: ImageFormatConverter


            Visibility: Beginner

        */
        Pylon::IEnumParameterT<MonoConversionMethodEnums>& MonoConversionMethod;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets the alignment of the bits in the target pixel type - Applies to: ImageFormatConverter

            Sets the alignment of the bits in the target pixel type if the target bit depth is greater than the source bit depth, e.g., if you are converting from a 10-bit to a 16-bit format.

            Visibility: Beginner

        */
        Pylon::IEnumParameterT<OutputBitAlignmentEnums>& OutputBitAlignment;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Sets the vertical orientation of the output image in the buffer - Applies to: ImageFormatConverter


            Visibility: Beginner

        */
        Pylon::IEnumParameterT<OutputOrientationEnums>& OutputOrientation;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Number of additional data bytes at the end of each line - Applies to: ImageFormatConverter

            Number of additional data bytes at the end of each line. These bytes are set to zero during the conversion.

            Visibility: Beginner

        */
        Pylon::IIntegerEx& OutputPaddingX;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CImageFormatConverterParams_Params_v6_2_0(CImageFormatConverterParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CImageFormatConverterParams_Params_v6_2_0& operator=(CImageFormatConverterParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for Image Format Converter

    The parameter class is used by the \c Pylon::CImageFormatConverter class.
    The \c Pylon::CImageFormatConverter creates new images by converting a source image to a different format.
    Once the format converter is configured it can convert almost all image formats supported by Basler camera devices.
    The \ref sample_Utility_ImageFormatConverter code sample shows the use of the Image Format Converter class.
    */
    class CImageFormatConverterParams_Params : public CImageFormatConverterParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CImageFormatConverterParams_Params( void )
        {
        }

        //! Destructor
        ~CImageFormatConverterParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CImageFormatConverterParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_ImageFormatConverterParams

#endif // BASLER_PYLON_IMAGEFORMATCONVERTERPARAMS_H
