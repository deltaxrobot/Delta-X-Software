//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the acquisition modes
*/

#pragma once

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
            Lists the acquisition modes that can be used with vTools.
        **/
        enum EAcquisitionMode
        {
             AcquisitionMode_Unchanged      = 0, /*!< With this mode all Camera and Image Loading vTools will keep their individual acquisition modes and the recipe is started like that. */
             AcquisitionMode_SingleFrame    = 1, /*!< With this mode all Camera and Image Loading vTools will be switched to single shot (overriding their individual acquisition modes) while the recipe is started. */
             AcquisitionMode_Continuous     = 2, /*!< With this mode all Camera and Image Loading vTools will be switched to continuous shot (overriding their individual acquisition modes) while the recipe is started. */
        };
    }
}
