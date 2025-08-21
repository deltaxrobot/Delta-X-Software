//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  AG
//------------------------------------------------------------------------------
/*!
 \file

 \brief
    Contains an enumeration that lists the types of supported regions.
*/

#pragma once

#include <pylondataprocessing/PylonDataProcessing.h>
#include <pylondataprocessing/RegionEntry.h>

// Region type is not standard.
#define PYLON_REGIONTYPE_CUSTOM       (0x80000000)
// Sets the bit count of the region type. Internal use only.
#define PYLON_REGIONTYPE_BIT_COUNT(n) ((n) << 16u)

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
            Lists the types of supported regions.
        **/
        enum ERegionType
        {
            RegionType_Undefined    = -1,                                                                   //!< \brief This region type can be used as initial value until the actual region type is set.
            RegionType_RLE32        = PYLON_REGIONTYPE_BIT_COUNT(sizeof(SRegionEntryRLE32) * 8u) | 0x0001   //!< \brief This region type represents a region with 32-bit run-length encoded pixels. See
                                                                                                            //!<        Pylon::DataProcessing::SRegionEntryRLE32 for more information.
        };

        /*!
        \brief  Checks whether a given region type is valid.

        \param[in] regionType The region type to check.

        \return Returns true if the region type is valid or false otherwise.

        \error Doesn't throw C++ exceptions.
        */
        inline bool IsValidRegionType(ERegionType regionType)
        {
            switch(regionType)
            {
            case RegionType_RLE32:
                return true;

            default:
                break;
            }

            return false;
        }

        /*!
        \brief  Determines the element size in bits of a given region type.

        \param[in] regionType The region type to get the element size of.

        \pre
        <ul>
        <li> The region type must be valid.
        </ul>

        \return Returns the size of an element of a region type in bits.

        \error Throws an exception if the preconditions aren't met.
        */
        inline size_t BitPerRegionElement(ERegionType regionType)
        {
            switch(regionType)
            {
            case RegionType_RLE32:
                return (static_cast<size_t>(regionType) >> 16u) & 0xff;

            default:
                break;
            }

            throw INVALID_ARGUMENT_EXCEPTION("Invalid region type passed.");
        }

        /*!
        \brief  Determines the required data size of a region with a given region type and number of region elements.

        \param[in] regionType The region type to be used.
        \param[in] elementCount The number of region elements.

        \pre
        <ul>
        <li> The region type must be valid.
        </ul>

        \return Returns the required data size of a region with a given region type and number of region elements.

        \error Throws an exception if the preconditions aren't met.
        */
        inline size_t ComputeRegionSize(ERegionType regionType, size_t elementCount)
        {
            size_t bitPerRegionElement = BitPerRegionElement(regionType);

            // Compute region size in bytes and round up if not a multiple of 8 bits.
            return ((elementCount * bitPerRegionElement) + 7u) / 8u;
        }

        /*!
        \brief  Determines the number of region elements that fit in the given region size in bytes.

        \param[in] regionType The region type to be used.
        \param[in] regionSize The region size in bytes to compute the entry count from.

        \pre
        <ul>
        <li> The region type must be valid.
        </ul>

        \return The number of region elements that fit in the given region size in bytes.

        \error Throws an exception if the preconditions aren't met.
        */
        inline size_t ComputeRegionEntryCount(ERegionType regionType, size_t regionSize)
        {
            size_t bitPerRegionElement = BitPerRegionElement(regionType);

            // Compute region entry count and round down if it's not a perfect fit.
            return (regionSize * 8u) / static_cast<size_t>(bitPerRegionElement);
        }
    }
}
