/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2012-2021 Basler AG
    http://www.baslerweb.com
-----------------------------------------------------------------------------*/
#ifndef GENAPICENUMS_H_INCLUDED
#define GENAPICENUMS_H_INCLUDED

#include <genapic/GenApiCDefines.h>

/**
 *  \file
 *  \brief GenApi enumeration types.
 *
 *  Definitions of enumerated types used by GenApi C functions.
 */

/**
  * \addtogroup genapi GenApi Interface
 * @{
 */

/**
 * \brief Node type.
 */

typedef enum
{
    IntegerNode,                /**< \brief Node represents an integer-valued parameter. */
    BooleanNode,                /**< \brief Node represents a boolean (true/false) parameter. */
    FloatNode,                  /**< \brief Node represents a floating point-valued parameter. */
    CommandNode,                /**< \brief Node can trigger a command. */
    StringNode,                 /**< \brief Node represents a string-valued parameter. */
    EnumerationNode,            /**< \brief Node represents an enumeration-valued parameter. */
    EnumEntryNode,              /**< \brief Node represents an 'enumeration entry' parameter. */
    Category,                   /**< \brief Node for grouping parameters in a category. */
    _UnknownNodeType = -1       /**< \brief Node type invalid. */
} EGenApiNodeType;

/**
 * \brief Access mode of a node.
 */

typedef enum
{
    NI,                         /**< \brief Not implemented. */
    NA,                         /**< \brief Not available. */
    WO,                         /**< \brief Write Only.*/
    RO,                         /**< \brief Read Only. */
    RW,                         /**< \brief Read and Write. */
    _UndefinedAccesMode = -1    /**< \brief Access mode invalid. */
} EGenApiAccessMode;

/**
 * \brief Node name spaces.
 */

typedef enum
{
    Custom,                     /**< \brief Name resides in custom name space. */
    Standard,                   /**< \brief Name resides in one of the standard name spaces. */
    _UndefinedNameSpace = -1    /**< \brief Name space invalid. */
} EGenApiNameSpace;

/**
 * \brief Node visibility.
 */

typedef enum
{
    Beginner = 0,               /**< \brief Visible to everyone. */
    Expert = 1,                 /**< \brief Visible to experts or gurus only. */
    Guru = 2,                   /**< \brief Visible to gurus only. */
    Invisible = 3,              /**< \brief Not visible at all. */
    _UndefinedVisibility = -1   /**< \brief Visibility invalid. */
} EGenApiVisibility;

/**
 * \brief Node caching modes.
 */

typedef enum
{
    NoCache,                    /**< \brief Do not use cache. */
    WriteThrough,               /**< \brief Write to cache and register. */
    WriteAround,                /**< \brief Write to register, write to cache on read. */
    _UndefinedCachingMode = -1  /**< \brief Caching mode invalid. */
} EGenApiCachingMode;

/**
 * \brief Node representation.
 */

typedef enum
{
    Linear,                     /**< \brief Slider with linear behavior. */
    Logarithmic,                /**< \brief Slider with logarithmic behavior. */
    Boolean,                    /**< \brief Checkbox. */
    PureNumber,                 /**< \brief Decimal number in an edit control. */
    HexNumber,                  /**< \brief Hex number in an edit control. */
    _UndefinedRepresentation = -1   /**< \brief Representation invalid. */
} EGenApiRepresentation;

/**
 * \brief File access modes.
 */

typedef enum
{
    GenApiFileReadAccess,       /**< \brief For specifying file read access on file open. */
    GenApiFileWriteAccess       /**< \brief For specifying file write access on file open. */
} EGenApiFileAccessMode;

/**
  * @}
  */

#endif
