//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a class that wraps a callable (function pointer or functor) to be used as an update observer in a \c CRecipe.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/IUpdateObserver.h>

#include <functional>

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
            A class that wraps a callable (function pointer or functor) to be used as an update observer in a \c CRecipe.

         \threading
            The observer, and therefore the callable, is called from multiple internal threads of the \c CRecipe.
        */
        class CCallableUpdateObserver : public IUpdateObserver
        {
        public:
            /*!
             \brief
                Constructs an update observer with a given callable.

                The callable must be invocable with the following signature:
                void (CRecipe& recipe, const CUpdate& update, intptr_t userProvidedId)

                Example:
            \code
                auto myLambda = [](CRecipe& recipe, const CUpdate& update, intptr_t userProvidedId)
                {
                    //...
                };

                CallableOutputObserver myObserver(myLambda);
                CRecipe recipe;
                //...
                recipe.TriggerUpdateAsync("ExamplePin", CVariant("ExampleValue"), &myObserver);
            \endcode

             \param[in]  callable       The callable to invoke.
             \param[in]  autoDelete     If true, the object will be deleted automatically after the callable has been invoked.

             \pre
                <ul>
                    <li>The callable must be valid (e.g., not a nullptr)</li>
                </ul>

             \error
                Throws an exception if the preconditions aren't met.
            */
            template <class T>
            CCallableUpdateObserver(T&& callable, bool autoDelete = false)
                : m_function(std::forward<T>(callable))
                , m_autoDelete(autoDelete)
            {
                if (static_cast<bool>(m_function) == false)
                {
                    throw INVALID_ARGUMENT_EXCEPTION("Invalid callable passed.");
                }
            }

            virtual ~CCallableUpdateObserver() = default;

            /*!
             \brief
                This method is called when an update of a \c Pylon::DataProcessing::CRecipe has been processed completely.

             \note
                If this update has triggered further updates, depending on the vTools used in a recipe, the output data may not be available yet.

             \param[in]  recipe          The recipe that processed the update.
             \param[in]  update          The update that was processed completely.
             \param[in]  userProvidedId  This ID is passed to distinguish between different events.
                                         This ID has been passed when calling \c CRecipe::TriggerUpdateAsync() or \c CRecipe:TriggerUpdate().

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            void UpdateDone(CRecipe& recipe, const CUpdate& update, intptr_t userProvidedId) override
            {
                try
                {
                    m_function(recipe, update, userProvidedId);
                }
                catch(...)
                {
                    if (m_autoDelete == true)
                    {
                        delete this;
                    }

                    throw;
                }

                if (m_autoDelete == true)
                {
                    delete this;
                }
            }

        private:
            CCallableUpdateObserver() = delete;

            const std::function<void(CRecipe&, const CUpdate&, intptr_t)>   m_function;
            const bool                                                      m_autoDelete;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
