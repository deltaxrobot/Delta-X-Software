//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2021-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  RN
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the queue modes
*/

#pragma once

#include <pylondataprocessing/PylonDataProcessing.h>

/*!
 * \namespace Pylon
 * \brief The Pylon namespace
 */
namespace Pylon
{
    /*!
     * \namespace Pylon::DataProcessing
     * \brief The DataProcessing namespace
     */
    namespace DataProcessing
    {
         /*!
         \brief
            Lists the queue modes.
        **/
        enum EQueueMode
         {
             QueueMode_Unlimited    = 0, /*!< With this mode the queue can contain an unlimited amount of items. */
             QueueMode_DropOldest   = 1, /*!< With this mode the oldest items will be dropped if the maximum number of queued items would be exceeded otherwise. */
             QueueMode_DropNewest   = 2, /*!< With this mode the newest items will be dropped if the maximum number of queued items would be exceeded otherwise. */
             QueueMode_Blocking     = 3  /*!< With this mode no items are dropped but if the maximum number of queued items is reached no additional items can be put into the queue. */
        };
    }
}
