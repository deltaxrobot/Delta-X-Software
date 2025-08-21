
//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2010-2024 Basler AG
//  http://www.baslerweb.com
// \note include InstantCamera.h
//------------------------------------------------------------------------------
/*!
\file
\brief Contains function timeout handling type for instant camera.
*/

#pragma once 

namespace Pylon
{
    /** \addtogroup Pylon_InstantCameraApiGeneric
     * @{
     */

    /// Defines how to handle a timeout for a method.
    enum ETimeoutHandling
    {
        TimeoutHandling_Return,           //!< The method returns on timeout. What data is returned can be found in the documentation of the method.
        TimeoutHandling_ThrowException    //!< An exception is thrown on timeout.
    };

    /**
     * @}
     */

}