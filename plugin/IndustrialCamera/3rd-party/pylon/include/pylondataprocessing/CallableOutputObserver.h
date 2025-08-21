//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a class that wraps a callable (function pointer or functor) to be used as an output observer of a \c CRecipe.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/VariantContainer.h>
#include <pylondataprocessing/IOutputObserver.h>

#include <functional>
#include <utility>

namespace Pylon
{
    namespace DataProcessing
    {
        class CRecipe;
        class CUpdate;
    }
}

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */
namespace Pylon
{
    namespace DataProcessing
    {
        /*!
         \brief
            A class that wraps a callable (function pointer or functor) to be used as an output observer of a \c CRecipe.

         \threading
            The observer, and therefore the callable, is called from multiple internal threads of the \c CRecipe.
        */
        class CCallableOutputObserver : public IOutputObserver
        {
        public:
            /*!
             \brief
                Constructs an output observer with a given callable.

                The callable must be invocable with the following signature:
                void (CRecipe& recipe, CVariantContainer value, const CUpdate& update, intptr_t userProvidedId)

                Example:
            \code
                auto myLambda = [](CRecipe& recipe, CVariantContainer value, const CUpdate& update, intptr_t userProvidedId)
                {
                    //...
                };

                CCallableOutputObserver myObserver(myLambda);
                CRecipe recipe;
                recipe.RegisterAllOutputsObserver(&myObserver, RegistrationMode_Append);
            \endcode

             \param[in]  callable       The callable to invoke.
             \param[in]  autoDelete     If true, the object will be deleted automatically when it is unregistered from the recipe.

             \pre
                <ul>
                    <li>The callable must be valid (e.g., not a nullptr)</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.
            */
            template <class T>
            CCallableOutputObserver(T&& callable, bool autoDelete = false)
                : m_function(std::forward<T>(callable))
                , m_autoDelete(autoDelete)
            {
                if (static_cast<bool>(m_function) == false)
                {
                    throw INVALID_ARGUMENT_EXCEPTION("Invalid callable passed.");
                }
            }

            virtual ~CCallableOutputObserver() = default;

            /*!
             \brief
                This method is called when an output of the \c CRecipe pushes data out.

             \param[in]  recipe          The recipe that produced the output.
             \param[in]  value           A variant container containing the output data.
             \param[in]  update          The corresponding update.
             \param[in]  userProvidedId  This ID is passed to distinguish between different events.
                                         This ID has been passed when calling \c CRecipe::RegisterOutputObserver().

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            void OutputDataPush(CRecipe& recipe, CVariantContainer value, const CUpdate& update, intptr_t userProvidedId) override
            {
                m_function(recipe, std::move(value), update, userProvidedId);
            }

            /*!
             \brief
                This method is called when the output observer is deregistered from the recipe.
                It can be used to delete the output observer by overloading the method. The
                default implementation of this method does nothing.

             \param[in]  recipe          The recipe that the observer is deregistered from.

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            void OnDeregistered(CRecipe& recipe) override
            {
                PYLON_UNUSED(&recipe);

                if (m_autoDelete == true)
                {
                    delete this;
                }
            };

        private:
            CCallableOutputObserver() = delete;

            const std::function<void(CRecipe&, CVariantContainer, const CUpdate&, intptr_t)>    m_function;
            const bool                                                                          m_autoDelete;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
