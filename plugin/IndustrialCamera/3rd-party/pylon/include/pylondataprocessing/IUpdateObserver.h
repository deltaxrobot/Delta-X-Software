//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an interface that can be used to get notified about the processing of updates.
*/

#pragma once

#include <pylon/stdinclude.h>

#include <pylondataprocessing/PylonDataProcessing.h>

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
            An interface that can be used to get notified about the processing of updates.

         \threading
            This interface is called from multiple internal threads of the \c Pylon::DataProcessing::CRecipe.
        */
        class PYLONDATAPROCESSING_API IUpdateObserver
        {
        public:
            virtual ~IUpdateObserver() = 0;

            /*!
             \brief
                This method is called when an update of a \c Pylon::DataProcessing::CRecipe has been processed completely.

             \note
                If this update has triggered further updates, depending on the vTools used in an recipe, the output data may not be available yet.

             \param[in]  recipe          The recipe that processed the update.
             \param[in]  update          The update that was processed completely.
             \param[in]  userProvidedId  This ID is passed to distinguish between different events.
                                         This ID has been passed when calling \c CRecipe::TriggerUpdateAsync() or \c CRecipe:TriggerUpdate().

             \error
                C++ Exceptions thrown by this method are caught and ignored.
            */
            virtual void UpdateDone(CRecipe& recipe, const CUpdate& update, intptr_t userProvidedId) = 0;
        };

        // Implementation for destructor must be out of class
        inline IUpdateObserver::~IUpdateObserver()
        {
        }
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif
