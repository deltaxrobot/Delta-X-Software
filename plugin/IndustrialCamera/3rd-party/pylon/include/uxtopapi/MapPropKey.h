#pragma once

#include <uxtopapi/Topology.h>

namespace topapi
{
    class CMapPropKeyImpl;

    /**
    \brief Specifies the kind of formatting of property key values.
    For each property key, the format can be defined by a format string (see printf), a boolean value (then a format string and literals for true and false can be defined).
    Forthermore, it can be defined as an item of an an array or a boolean array. Then the format string has to contain a format specifier for the index which preceeds the format specifier of the value,
    e.g. L"[%d]:, %s" which results in an output "[0]: True" if the 0-th item of an array is false and L"True" is the literal for value true.
    */
    enum EPropKeyFormat
    {
        PropKeyFormat_FormatString = 0,     //!< A format string for one value.
        PropKeyFormat_Boolean = 1,          //!< A format string for one value (0 or 1)
        PropKeyFormat_ItemFormatString = 3, //!< Item of an array, the index and the value have to be provided.
        PropKeyFormat_ItemBoolean = 4       //!< Item of an array, the index and the value have to be provided.
    };

    /// Specifies the formatting of node property key values.
    struct UX_TOPAPI PropKeyFormat_t
    {
        EPropKeyFormat f;           ///< Kind of formatting.
        const wchar_t* pPrefix;        ///< A string which is added before the string representation of the value(s), e. g. L"(".
        const wchar_t* pSeparator;     ///< A string which serves as separator between items of an array, e. g. L", ".
        const wchar_t* pSuffix;        ///< A string which is added after the string representation of the value(s), e. g. L")".
        bool           bDecompose;     ///< If false, the string representation is resulting in a string without line breaks, if true, the items are wrapped and aligned.


        /// Union for different formattings.
        union
        {
            struct
            {
                const wchar_t* pReserved[3];
            } reserved;

            // PropKeyFormat_FormatString
            struct
            {
                const wchar_t* pString;
            } formatString;

            // PropKeyFormat_Boolean
            struct
            {
                const wchar_t* pString;
                const wchar_t* pFalse;
                const wchar_t* pTrue;
            } boolean;

            // PropKeyFormat_ItemFormatString
            struct
            {
                const wchar_t* pString;
            } itemFormatString;

            // PropKeyFormat_Boolean
            struct
            {
                const wchar_t* pString;
                const wchar_t* pFalse;
                const wchar_t* pTrue;
            } itemBoolean;

        } v;
    };

    /// Mapping from node property keys to name, description and format.
    class UX_TOPAPI CMapPropKey
    {
    public:
        ///
        CMapPropKey();

        /// Destructor.
        virtual ~CMapPropKey();

        /**
        \brief Returns a descriptive name of a property key.
        \param propKey The property key.
        */
        const wchar_t* GetName( PROPKEY propKey ) const;

        /**
        \brief Returns a description for a property key. It is is more detailed than the name of a property key.
        \param propKey The property key.
        */
        const wchar_t* GetDescription( PROPKEY propKey ) const;

        /**
        \brief Returns a format string for a property key.
        \param propKey The property key.
        */
        const PropKeyFormat_t* GetFormat( PROPKEY propKey ) const;

    private:
        CMapPropKeyImpl* m_mapPropKeyImpl;
    };
} // namespace topapi
