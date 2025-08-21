//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
\file
\brief Contains an interface that can be used to receive output data from a \c CRecipe.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/VariantContainer.h>

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
            An interface that can be used to receive output data from a \c CRecipe.

         \threading
            This interface is called from multiple internal threads of the \c CRecipe.
        */
        class PYLONDATAPROCESSING_API IOutputObserver
        {
        public:
            virtual ~IOutputObserver() = 0;

            /*!
             \brief
                This method is called when an output of the \c CRecipe pushes data out.

             \param[in]  recipe          The recipe that produced the output.
             \param[in]  value           A variant container containing the output data.
             \param[in]  update          The corresponding update.
             \param[in]  userProvidedId  This ID is passed to distinguish between different events.
                                         This ID has been passed when calling \c CRecipe::RegisterOutputObserver().

             \error
                C++ exceptions thrown by this method are caught and ignored.
            */
            virtual void OutputDataPush(CRecipe& recipe, CVariantContainer value, const CUpdate& update, intptr_t userProvidedId) = 0;

            /*!
             \brief
                This method is called when the output observer is deregistered from the recipe. It can be used to delete the output observer by overloading the method.

             \param[in]  recipe          The recipe that the observer is deregistered from.

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            virtual void OnDeregistered(CRecipe& recipe);
        };

        // Implementation for destructor must be out of class
        inline IOutputObserver::~IOutputObserver()
        {
        }

        // Implementation for method must be out of class
        inline void IOutputObserver::OnDeregistered(CRecipe& recipe)
        {
            PYLON_UNUSED(&recipe);
        }
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
