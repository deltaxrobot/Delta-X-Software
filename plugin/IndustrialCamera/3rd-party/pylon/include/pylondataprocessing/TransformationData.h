//------------------------------------------------------------------------------
//  Basler Data Processing SDK
//  Copyright (c) 2023-2024 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
    \file
    \brief  Contains a transformation data class.
*/

#pragma once

#include <pylondataprocessing/PylonDataProcessing.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <pylon/stdinclude.h>

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
        \class  CTransformationData
        \brief  Describes a transformation data class that represents a mathematical matrix with a specific number of columns and rows.

        \threading
            The CTransformationData class isn't thread-safe.
        */
        class PYLONDATAPROCESSING_API CTransformationData
        {
        public:
            /*!
            \brief Creates invalid transformation data.
    
            \post
            <ul>
            <li> IsValid() will return false.
            <li> GetColumnCount() will return 0.
            <li> GetRowCount() will return 0.
            <li> GetEntry(size_t column, size_t row) will throw an exception.
            <li> SetEntry(size_t column, size_t row, size_t value) will throw an exception.
            </ul>
    
            \error Doesn't throw C++ exceptions.
            */
            CTransformationData();

            /*!
            \brief Creates valid transformation data with the specified number of columns and rows.

            \param[in] columns The number of columns that the new transformation data should have (must be higher than 0).
            \param[in] rows The number of rows that the new transformation data should have (must be higher than 0).

            \pre
            <ul>
            <li>Argument columns must be higher than 0.</li>
            <li>Argument rows must be higher than 0.</li>
            </ul>

            \post
            <ul>
            <li> IsValid() will return true.
            <li> All entries will be reset to 0.0.
            </ul>

            \error Throws an exception if the preconditions aren't met.
            */
            CTransformationData(size_t columns, size_t rows);


            /*!
            \brief  Copies the transformation data properties and values from the source transformation data.
    
            \param[in] source The source transformation data.
    
            \error Doesn't throw C++ exceptions.
            */
            CTransformationData(const CTransformationData& source);

            /*!
            \brief  Move constructs the transformation data properties and values from the source transformation data.

            \param[in] source The source transformation data (will be invalid after the call).

            \error Doesn't throw C++ exceptions.
            */
            CTransformationData(CTransformationData&& source);


            /*!
            \brief Destroys a transformation data object.
    
            \error Doesn't throw C++ exceptions.
            */
            ~CTransformationData();


            /*!
            \brief  Copies the transformation data properties and values from the source transformation data.
    
            \param[in] source The source transformation data.

            \error Doesn't throw C++ exceptions.
            */
            CTransformationData& operator=(const CTransformationData& source);

            /*!
            \brief  Moves the transformation data properties and values from the source transformation data.

            \param[in] source The source transformation data (will be invalid after the call).

            \error Doesn't throw C++ exceptions.
            */
            CTransformationData& operator=(CTransformationData&& source);

            /*!
            \brief Resets the transformation data using the specified number of columns and rows.

            \param[in] columns The number of columns that the transformation data should have (must be higher than 0).
            \param[in] rows The number of rows that the transformation data should have (must be higher than 0).

            \pre
            <ul>
            <li>Argument columns must be higher than 0.</li>
            <li>Argument rows must be higher than 0.</li>
            </ul>

            \post
            <ul>
            <li> IsValid() will return true.
            <li> All entries will be reset to 0.0.
            </ul>

            \error Throws an exception if the preconditions aren't met.
            */
            void Reset(size_t columns, size_t rows);

            /*!
            \brief Can be used to check whether the transformation data is valid.

            \return Returns false if the transformation data is invalid.

            \error Doesn't throw C++ exceptions.
            */
            bool IsValid() const;

            /*!
            \brief Get the number of columns of the transformation data.

            \return Returns the number of columns or 0 if the transformation data is invalid.

            \error Doesn't throw C++ exceptions.
            */
            size_t GetColumnCount() const;

            /*!
            \brief Get the number of rows of the transformation data.

            \return Returns the number of rows or 0 if the transformation data is invalid.

            \error Doesn't throw C++ exceptions.
            */
            size_t GetRowCount() const;

            /*!
            \brief Get an entry at a specific position of the transformation data.

            \param[in] column The column of the entry to retrieve (must be lower than number of columns).
            \param[in] row The row of the entry to retrieve (must be lower than number of rows).

            \pre
            <ul>
            <li>Transformation data must be valid.</li>
            <li>Argument column must be lower than number of columns.</li>
            <li>Argument row must be lower than number of rows.</li>
            </ul>

            \return Returns the entry retrieved at the specified position.

            \error Throws an exception if the preconditions aren't met.
            */
            double GetEntry(size_t column, size_t row) const;

            /*!
            \brief Set an entry at a specific position in the transformation data.

            \param[in] column The column of the entry to set (must be lower than number of columns).
            \param[in] row The row of the entry to set (must be lower than number of rows).
            \param[in] value The new value to set the entry to.

            \pre
            <ul>
            <li>Transformation data must be valid.</li>
            <li>Argument column must be lower than number of columns.</li>
            <li>Argument row must be lower than number of rows.</li>
            </ul>

            \error Throws an exception if the preconditions aren't met.
            */
            void SetEntry(size_t column, size_t row, double value);

        private:
            // Internal use only.
            class Impl;

            Impl* m_pImpl;
        };
    }
}

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
