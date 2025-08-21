//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2024 Basler AG
//  http://www.baslerweb.com
// \note include InstantCamera.h
//------------------------------------------------------------------------------
/*!
\file
\brief Contains cleanup type enum for instant camera.
*/

#pragma once 

namespace Pylon
{
     /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /// Defines who deletes a passed object if it is not needed anymore.
    enum ECleanup
    {
        Cleanup_None,                 //!< The caller is responsible for deleting the passed object. The object needs to be detached or deregistered before deletion.
        Cleanup_Delete                //!< The passed object is deleted if it is not needed anymore.
    };

    /**
     * @}
     */

}