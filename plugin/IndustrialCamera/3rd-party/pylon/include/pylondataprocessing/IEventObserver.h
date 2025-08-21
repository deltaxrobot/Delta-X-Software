//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  TvdM
//------------------------------------------------------------------------------
/*!
\file
\brief Contains an interface that can be used to receive event data from a \c CRecipe.
*/

#pragma once

#include <pylon/stdinclude.h>
#include <pylondataprocessing/PylonDataProcessing.h>

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
            Data associated with an event inside the recipe. Currently, only errors are supported.
         */
        struct PYLONDATAPROCESSING_API CEventData
        {
            /*!
               \brief
                  Type of event. Currently, only errors are supported.
            */
            enum EEventType
            {
                EventType_Error = 1,     //!< An error (e.g., of a vtool) is signaled as set (new error).
                EventType_ErrorReset = 2 //!< An error (e.g., of a vtool) is signaled as reset (removed error).
            } EventType;

            /*!
              \brief
                 Descriptive text, e.g., error message.
             */
            String_t Description;

            /*!
            \brief
               Fully-qualified name of the signaled event, e.g., more detailed type of error.
            */
            String_t EventClass;

            /*!
            \brief
               Fully-qualified name of the owner who signaled the event, e.g., name of the vTool.
            */
            String_t EventSourceName;
        };

        /*!
         \brief
            An interface that can be used to receive event data from a \c CRecipe.

         \threading
            This interface is called from multiple internal threads of the \c CRecipe.
        */
        class PYLONDATAPROCESSING_API IEventObserver
        {
        public:
            virtual ~IEventObserver() = 0;

            /*!
             \brief
                This method is called when the graph of the \c CRecipe detects an event, e.g., an error change of a vtool.

             \param[in]  recipe          The recipe that produced the output.
             \param[in]  pEvents         List of event infos as plain C array.
             \param[in]  numEvents       Number of entries in that list.

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            virtual void OnEventSignaled(CRecipe& recipe, const CEventData* pEvents, size_t numEvents) = 0;

            /*!
             \brief
                This method is called when the event observer is deregistered from the recipe. It can be used to delete the event observer by overloading the method. The default implementation of
                this method does nothing.

             \param[in]  recipe          The recipe that the observer is deregistered from.

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            virtual void OnDeregistered(CRecipe& recipe);
        };

        // Implementation for destructor must be out of class
        inline IEventObserver::~IEventObserver()
        {
        }

        // Implementation for method must be out of class
        inline void IEventObserver::OnDeregistered(CRecipe& recipe)
        {
            PYLON_UNUSED(&recipe);
        }
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
