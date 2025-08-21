//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2022-2024 Basler AG
//  http://www.baslerweb.com
//  Author:  DV
//-----------------------------------------------------------------------------

#pragma once

#include <pylon/Platform.h>
#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/Container.h>



namespace Pylon
{
    /*!
    \class  CStaticDefectPixelCorrection
    \brief  Provides utility functions to use Static Defect Pixel Correction on certain ace 2 cameras.
    */
    class PYLONUTILITY_API CStaticDefectPixelCorrection
    {
    public:
        /// Type of list.
        enum EListType
        {
            ListType_Factory,              //!< A Factory list is computed when the camera is made and can't be changed by the user.
            ListType_User                  //!< A User list can be updated by the user. It is empty initially.
        };


        /*!
        \brief Gets the defect pixel list from the camera.

        The camera stores all defect pixels in a sorted list.
        For more details, consult the camera's documentation.

        \param[in] pNodeMap The nodemap of the camera.
        \param[out] pixelList List of defect pixels read from camera.
        \param[in] listType The type of list to read.

        \return Returns true if the list was read successfully. Otherwise, false is returned.
        \error Can throw exceptions if the communication with the camera fails.
        */
        static bool GetDefectPixelList( GenApi::INodeMap* pNodeMap, StaticDefectPixelList_t& pixelList, EListType listType = ListType_User );


        /*!
        \brief Sets the defect pixel list in the camera.

        The camera stores all defect pixels in a sorted list.
        The list will be normalized, see NormalizePixelList, before it is written to the camera.
        For more details, consult the camera's documentation.

        \param[in] pNodeMap The nodemap of the camera.
        \param[in] pixelList A list of defect pixels.
        \param[in] listType The type of list to write.

        \return Returns true if the list was written successfully. Otherwise, false is returned.
        \error Can throw exceptions if the communication with the camera fails.
        */
        static bool SetDefectPixelList( GenApi::INodeMap* pNodeMap, StaticDefectPixelList_t& pixelList, EListType listType = ListType_User );


        /*!
        \brief Sort and erase duplicates of a defect pixel list.

        Normalizing the list is optional. The list will be normalized automatically when SetDefectPixelList is called.

        \param[in] pNodeMap : The nodemap of the camera.
        \param[in,out] pixelList : The pixel list to normalize. The normalized pixel list will be returned.

        \return True if the normalization runs correctly. Otherwise, false is returned.
        \exception May throw a RuntimeException if the camera doesn't support user-specific defect pixel lists or if there are too many entries in the pixel list.
        */
        static bool NormalizePixelList( GenApi::INodeMap* pNodeMap, StaticDefectPixelList_t& pixelList );
    };
}
