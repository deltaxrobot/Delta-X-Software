//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains structs describing region entry layouts.
*/

#pragma once

#include <pylon/stdinclude.h>

#pragma pack(push, 1)

namespace Pylon
{
    namespace DataProcessing
    {
        /*! \brief Entry for the run-length encoded pixels of a region.
            Region entries must be sorted line-wise starting with line 0 and then column-wise
            starting with column 0.
        */
        struct SRegionEntryRLE32
        {
            int32_t StartX; //!< \brief The horizontal start of the entry (may be identical to horizontal end).
            int32_t EndX;   //!< \brief The horizontal end of the entry (may be identical to horizontal start).
            int32_t Y;      //!< \brief The vertical position of the entry.
        };
    }
}

#pragma pack(pop)
