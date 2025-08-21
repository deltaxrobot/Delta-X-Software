//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains a class that can be used as a generic output observer for data processing recipes.
*/

#pragma once

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylondataprocessing/IOutputObserver.h>
#include <pylondataprocessing/Recipe.h>

/*!
 * \namespace Pylon::DataProcessing
 * \brief The DataProcessing namespace
 */
namespace Pylon
{
    namespace DataProcessing
    {
        /*!
        \struct SGenericOutputObserverResult

        \brief
            A container for recipe output data
        */
        struct SGenericOutputObserverResult
        {
            CUpdate Update;                 //!< The update the output belongs to.
            intptr_t UserProvidedID = 0;    //!< The user-provided ID belonging to the update.
            CVariantContainer Container;    //!< The output data of the recipe.
            intptr_t RecipeContext;         //!< The context of the recipe that can be set using \c CRecipe::SetRecipeContext.
        };

        /*!
        \class CGenericOutputObserver

        \brief
            A simple Recipe Output Observer that collects recipe outputs in a queue.
        */
        class PYLONDATAPROCESSING_API CGenericOutputObserver : public IOutputObserver
        {
        public:
            /*!
             \brief
                 Creates a \c CGenericOutputObserver object.

             \error
                 Doesn't throw C++ exceptions.
            */
            CGenericOutputObserver();

            /*!
             \brief
                 Destroys a \c CGenericOutputObserver object and resets the wait object provided by GetWaitObject().

             \error
                 Doesn't throw C++ exceptions.
            */
            virtual ~CGenericOutputObserver();

            /*!
             \brief
                 Returns a WaitObject that is in Signaled state if the queue is not empty and in Reset state if it is empty.

             \return
                 \c WaitObject of the GenericOutputObserver.

             \error
                 Doesn't throw C++ exceptions.

             \threading
                 This method is thread safe.
            */
            const WaitObject& GetWaitObject() const;

            /*!
             \brief
                Retrieves the oldest CVariantContainer from the recipe output in the queue.
                The SGenericOutputObserverResult containing the CVariantContainer will be removed from the queue.

             \return
                \c The oldest CVariantContainer in the queue or an empty variant container if the queue is empty.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is thread safe.
            */
            CVariantContainer RetrieveResult();

            /*!
             \brief
                Retrieves the oldest SGenericOutputObserverResult from the recipe output in the queue.
                The SGenericOutputObserverResult will be removed from the queue.

            \return
                \c The oldest SGenericOutputObserverResult in the queue or an SGenericOutputObserverResult with an invalid update and empty CVariantContainer if the queue is empty.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is thread safe.
            */
            SGenericOutputObserverResult RetrieveFullResult();

            /*!
             \brief
                Gets the number of SGenericOutputObserverResults in the queue.

            \return
                \c The number of elements in the queue.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is thread safe.
             */
            size_t GetNumResults() const;

            /*!
             \brief
                Removes all CVariantContainers from the queue.

             \error
                Doesn't throw C++ exceptions.

             \threading
                This method is thread safe.
             */
            void Clear();

        private:
            void OutputDataPush(CRecipe& recipe, CVariantContainer valueContainer, const CUpdate& update, intptr_t userProvidedId) override;

            class CGenericOutputObserverImpl;
            CGenericOutputObserverImpl* m_pImpl = nullptr;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
