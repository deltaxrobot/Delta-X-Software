//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains the name classes of the parameter collection interface.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>

#ifdef _MSC_VER
#pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

namespace Pylon
{
    namespace DataProcessing
    {
        /*
         Collection of classes to determine which type of parameter to get. Serves as a type info to the argument of the Get function of IParameterCollection.
        */

        /*!
         \brief
            Defines a generic parameter name.
        */
        struct ParameterName
        {
            ParameterName(const String_t& str)
                : m_str(str)
            {
            }

            operator String_t() const
            {
                return m_str;
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c ParameterName with concatenated parameter names.
            */
            const ParameterName operator||(const ParameterName& rhs) const
            {
                return ParameterName(m_str + String_t("|") + rhs.m_str);
            }

        private:
            String_t m_str;
        };

        /*!
         \brief
            Defines an integer parameter name by combining the parameter name string and the parameter type information.
        */
        struct IntegerParameterName : public ParameterName
        {
            IntegerParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c IntegerParameterName with concatenated parameter names.
            */
            const IntegerParameterName operator||(const IntegerParameterName& rhs) const
            {
                return IntegerParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief
            Defines a Boolean parameter name by combining the parameter name string and the parameter type information.
        */
        struct BooleanParameterName : public ParameterName
        {
            BooleanParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c BooleanParameterName with concatenated parameter names.
            */
            const BooleanParameterName operator||(const BooleanParameterName& rhs) const
            {
                return BooleanParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief
            Defines a float parameter name by combining the parameter name string and the parameter type information.
        */
        struct FloatParameterName : public ParameterName
        {
            FloatParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c FloatParameterName with concatenated parameter names.
            */
            const FloatParameterName operator||(const FloatParameterName& rhs) const
            {
                return FloatParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief
            Defines an enum parameter name by combining the parameter name string and the parameter type information.
        */
        struct EnumParameterName : public ParameterName
        {
            EnumParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c EnumParameterName with concatenated parameter names.
            */
            const EnumParameterName operator||(const EnumParameterName& rhs) const
            {
                return EnumParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief Defines a string parameter name by combining the parameter name string and the parameter type information.
        */
        struct StringParameterName : public ParameterName
        {
            StringParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c StringParameterName with concatenated parameter names.
            */
            const StringParameterName operator||(const StringParameterName& rhs) const
            {
                return StringParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief Defines a command parameter name by combining the parameter name string and the parameter type information.
        */
        struct CommandParameterName : public ParameterName
        {
            CommandParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c CommandParameterName with concatenated parameter names.
            */
            const CommandParameterName operator||(const CommandParameterName& rhs) const
            {
                return CommandParameterName(*this + String_t("|") + rhs);
            }
        };

        /*!
         \brief
            Defines an array parameter name by combining the parameter name string and the parameter type information.
        */
        struct ArrayParameterName : public ParameterName
        {
            ArrayParameterName(const String_t& str)
                : ParameterName(str)
            {
            }

            /*!
             \brief
                Provides support for parameter concatenation.

             \param[in] rhs The parameter to concatenate.

             \return
                Returns a new \c ArrayParameterName with concatenated parameter names.
            */
            const ArrayParameterName operator||(const ArrayParameterName& rhs) const
            {
                return ArrayParameterName(*this + String_t("|") + rhs);
            }
        };
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
