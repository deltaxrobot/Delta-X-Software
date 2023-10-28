//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2007-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------
/*!
\file
\brief This header is for backward compatibility. Please use BaslerCameraLinkDeviceInfo.h instead
*/
#pragma once

#include "BaslerCameraLinkDeviceInfo.h"

namespace Pylon
{
    // aliases until classes are renamed properly
    typedef CBaslerCameraLinkDeviceInfo CPylonCLSerDeviceInfo;
}
