//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a class that wraps a callable (function pointer or functor) to be used as an event observer of a \c CRecipe.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/IEventObserver.h>

#include <functional>

namespace Pylon
{
    namespace DataProcessing
    {
        class CRecipe;
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
            A class that wraps a callable (function pointer or functor) to be used as an event observer of a \c CRecipe.

         \threading
            The observer, and therefore the callable, is called from multiple internal threads of the \c CRecipe.
        */
        class CCallableEventObserver : public IEventObserver
        {
        public:
            /*!
             \brief
                Constructs an event observer with a given callable.

                The callable must be invocable with the following signature:
                void (CRecipe& recipe, const CEventData* pEvents, size_t numEvents)

                Example:
             \code
                auto myLambda = [](CRecipe& recipe, const CEventData* pEvents, size_t numEvents)
                {
                    //...
                };

                CCallableEventObserver myObserver(myLambda);
                CRecipe recipe;
                recipe.RegisterEventObserver(&myObserver);
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
            CCallableEventObserver(T&& callable, bool autoDelete = false)
                : m_function(std::forward<T>(callable))
                , m_autoDelete(autoDelete)
            {
                if (static_cast<bool>(m_function) == false)
                {
                    throw INVALID_ARGUMENT_EXCEPTION("Invalid callable passed.");
                }
            }

            virtual ~CCallableEventObserver() = default;

            /*!
             \brief
                This method is called when the graph of the \c CRecipe detects an event, e.g., an error change of a vtool.

             \param[in]  recipe          The recipe that produced the output.
             \param[in]  pEvents         List of event infos as plain C array.
             \param[in]  numEvents       Number of entries in that list.

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            void OnEventSignaled(CRecipe& recipe, const CEventData* pEvents, size_t numEvents) override
            {
                m_function(recipe, pEvents, numEvents);
            }

            /*!
             \brief
                This method is called when the event observer is deregistered from the recipe.
                It can be used to delete the event observer by overloading the method. The
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
            CCallableEventObserver() = delete;

            const std::function<void(CRecipe&, const CEventData*, size_t)>  m_function;
            const bool                                                      m_autoDelete;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
