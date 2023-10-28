//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2009-2021 Basler AG
//  http://www.baslerweb.com
//  Author: Italo Anzioso
//-----------------------------------------------------------------------------
/*!
    \file   FeaturePersistence.h
    \brief  Pylon::CFeaturePersistence class with static helper functions for loading
    and saving camera features.
    \date   2007-09-11
*/

#ifndef __PYLON_FeaturePersistence_H_090218_090218_IS_INCLUDED__
#define __PYLON_FeaturePersistence_H_090218_090218_IS_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif

#include <pylon/Platform.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <GenICamFwd.h>
#include <pylon/stdinclude.h>   // Pylon::String_t
#include <pylon/PylonUtility.h> // defines PYLONUTILITY_API

namespace Pylon
{
    /*! \brief Utility class for saving and restoring camera features to and from a file or string.

    \note When saving features, the behavior of cameras supporting sequencers depends on the
    current setting of the "SequenceEnable" (some GigE models) or
    "SequencerConfigurationMode" (USB only) features respectively.

    Only if the sequencer is in configuration mode, are the sequence sets exported.
    Otherwise, the camera features are exported without sequence sets.

    */
    class PYLONUTILITY_API CFeaturePersistence
    {

    public:

        /*! \brief Loads the features from the file to the node map.

            \param[in] FileName Name of the file that contains the node map values.
            \param[in] pNodeMap Pointer to the node map
            \param[in] validate If validate==true, all node values will be validated.
            In case of an error, a GenICam::RuntimeException will be thrown

            \error Throws an exception if loading fails.
        */
        static void Load( const String_t& FileName,
                          GENAPI_NAMESPACE::INodeMap* pNodeMap,
                          bool validate = true
                          );

      /*! \brief Saves the node map to the file.

          Sequence sets of a camera are automatically saved if SequenceEnable or
          SequencerConfigurationMode is enabled.

          \param[in] FileName  Name of the file that contains the node map values
          \param[in] pNodeMap Pointer to the node map

          \error Throws an exception if saving fails.

      */
        static void Save( const String_t& FileName,
                          GENAPI_NAMESPACE::INodeMap* pNodeMap
                          );
        /*!
            \brief Loads the features from the string to the node map.

            \param[in] Features String containing the node map values.
            \param[in] pNodeMap Pointer to the node map.
            \param[in] validate If validate==true, all node values will be validated.
            In case of an error, a GenICam::RuntimeException will be thrown.

            \error Throws an exception if loading fails.
            */
        static void LoadFromString( const String_t& Features,
                                    GENAPI_NAMESPACE::INodeMap* pNodeMap,
                                    bool validate = true
                                    );

                /*! \brief Saves the node map to the string.
                    Sequence sets of a camera are automatically saved, if SequenceEnable or
                    SequencerConfigurationMode is enabled.

                    \param[out] Features String containing the node map values
                    \param[in] pNodeMap Pointer to the node map

                    \error Throws an exception if saving fails.
                    */
        static void SaveToString( String_t& Features,
                                  GENAPI_NAMESPACE::INodeMap* pNodeMap
                                  );

    private:
        CFeaturePersistence( void );
        ~CFeaturePersistence( void );

    };

}   // Pylon Namespace

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif //__PYLON_FeaturePersistence_H_090218_090218_IS_INCLUDED__
