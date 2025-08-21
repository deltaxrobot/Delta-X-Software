//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
\file
\brief Contains the parameter collection interface.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylon/ArrayParameter.h>
#include <pylon/BooleanParameter.h>
#include <pylon/CommandParameter.h>
#include <pylon/EnumParameter.h>
#include <pylon/FloatParameter.h>
#include <pylon/IntegerParameter.h>
#include <pylon/StringParameter.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/ParameterNames.h>

#ifdef _MSC_VER
#pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    namespace DataProcessing
    {
        /*!
         \brief
            Interface to access the parameter collection.

         A parameter is accessed by its parameter name. The name is path-like. Example:
         \code
             IntegerParameterName("ImageFormatConverter1/@vTool/OuputPixelFormat")
         \endcode
         for an ImageFormatConverter vTool called ImageFormatConverter1 or
         \code
             FloatParameterName("Camera1/@CameraDevice/ExposureTime")
         \endcode
         for a Camera vTool called Camera1.

         The path consists of these elements: \<vTool Identifier\>/@<NodeMapName>/]/NodeName

         It is possible to join multiple possible parameter names of the same type
         using "|" as a separator:
         \code
             FloatParameterName("Camera1/@CameraDevice/ExposureTime|Camera1/@CameraDevice/ExposureTimeAbs")
         \endcode
         The first available parameter name is used when mutliple names are provided.
        */
        interface IParameterCollection
        {
        public:
            virtual ~IParameterCollection() = default;

            /*!
             \brief
                Returns a \c Pylon::CParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CParameter from the \c parameterName passed or an empty Pylon::CParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CParameter Get(const String_t& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CParameter from the \c parameterName passed or an empty Pylon::CParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CParameter Get(const ParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CIntegerParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CIntegerParameter from the \c parameterName passed or an empty Pylon::CIntegerParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CIntegerParameter Get(const IntegerParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CFloatParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CFloatParameter from the \c parameterName passed or an empty Pylon::CFloatParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CFloatParameter Get(const FloatParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CStringParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CStringParameter from the \c parameterName passed or an empty Pylon::CStringParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CStringParameter Get(const StringParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CBooleanParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CBooleanParameter from the \c parameterName passed or an empty Pylon::CBooleanParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CBooleanParameter Get(const BooleanParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CArrayParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CArrayParameter from the \c parameterName passed or an empty Pylon::CArrayParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CArrayParameter Get(const ArrayParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CCommandParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CCommandParameter from the \c parameterName passed or an empty Pylon::CCommandParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CCommandParameter Get(const CommandParameterName& parameterName) = 0;

            /*!
             \brief
                Returns a \c Pylon::CEnumParameter from the requested parameter name.

             \param[in] parameterName The name of the parameter.

             \return
                \c Pylon::CEnumParameter from the \c parameterName passed or an empty Pylon::CEnumParameter if \c parameterName is not contained.

             \error
                Doesn't throw C++ exceptions.
            */
            virtual CEnumParameter Get(const EnumParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the parameter is contained in the parameter collection.

             \param[in] parameterName The name of the parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const String_t& parameterName) = 0;

            /*!
             \brief
                Indicates whether the parameter is contained in the parameter collection.

             \param[in] parameterName The name of the parameter.

             \return
                \c true, if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const ParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the integer parameter is contained in the parameter collection.

             \param[in] parameterName The name of the integer parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const IntegerParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the boolean parameter is contained in the parameter collection.

             \param[in] parameterName The name of the boolean parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const BooleanParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the enum parameter is contained in the parameter collection.

             \param[in] parameterName The name of the enum parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const EnumParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the string parameter is contained in the parameter collection.

             \param[in] parameterName The name of the string parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const StringParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the float parameter is contained in the parameter collection.

             \param[in] parameterName The name of the float parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const FloatParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the array parameter is contained in the parameter collection.

             \param[in] parameterName The name of the port parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const ArrayParameterName& parameterName) = 0;

            /*!
             \brief
                Indicates whether the command parameter is contained in the parameter collection.

             \param[in] parameterName The name of the command parameter.

             \return
                \c true if a parameter with the \c parameterName passed is contained in the parameter collection, false otherwise.

             \throws
                Doesn't throw C++ exceptions.
            */
            virtual bool Contains(const CommandParameterName& parameterName) = 0;

            /*!
             \brief
                Gets a \c StringList_t with the names of all parameters in this parameter collection.

             \return
                \c StringList_t with the names of all parameters in this parameter collection.
            */
            virtual StringList_t GetAllParameterNames() = 0;
        };
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
