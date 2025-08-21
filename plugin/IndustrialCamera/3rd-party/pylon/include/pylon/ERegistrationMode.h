//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2024 Basler AG
//  http://www.baslerweb.com
// \note include InstantCamera.h
//------------------------------------------------------------------------------
/*!
\file
\brief Contains item registration type for instant camera.
*/

#pragma once 

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /// Defines how to register an item.
    enum ERegistrationMode
    {
        RegistrationMode_Append,        //!< The item is appended to the list of registered items.
        RegistrationMode_ReplaceAll     //!< The item replaces all other registered items.
    };

    /**
     * @}
     */

}