/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2009-2021 Basler AG
    http://www.baslerweb.com
    Author:  AH, TK
-----------------------------------------------------------------------------*/

/**
    \file
    \brief Error codes for GenApi C bindings.
*/

#ifndef GENAPICERROR_H_INCLUDED
#define GENAPICERROR_H_INCLUDED

/*
 * TODO: Define a more elaborate numbering scheme
 * TODO: Map to HRESULTS when library is built for usage with type library
 */

#define GENAPIC_RESULT HRESULT

/**
* \defgroup errorcodes Error&nbsp;Codes
* \brief Error codes returned by any of the \pylon_C API functions.
*
* These error codes can be returned from any of the \pylon_C API functions.\n
* To get a textual representation for the error code you can call GenApiGetLastErrorMessage().\n
* To get a detailed error description you can call GenApiGetLastErrorDetail(). The string returned will contain the specific reason why the call has failed.
* \note If a function returns an error, you must call GenApiGetLastErrorMessage() and/or GenApiGetLastErrorDetail() directly after you received the error.
* Calling other functions will either reset or overwrite the error text.
*
* @{
*/

#define GENAPI_E_OK                         ((GENAPIC_RESULT) 0)           /**< Operation completed successfully. */
#define GENAPI_E_FAIL                       ((GENAPIC_RESULT) 0xC2000001)  /**< Unspecified error occurred. Call GenApiGetLastErrorDetail() for more information about the error. */
#define GENAPI_E_INVALID_ARG                ((GENAPIC_RESULT) 0xC2000002)  /**< Function called with invalid argument. */
#define GENAPI_E_INSUFFICIENT_BUFFER        ((GENAPIC_RESULT) 0xC2000003)  /**< Buffer size passed is less than required. */
#define GENAPI_E_INVALID_NODEMAPHANDLE      ((GENAPIC_RESULT) 0xC2000004)  /**< An invalid node map handle has been passed. */
#define GENAPI_E_NODE_NOT_FOUND             ((GENAPIC_RESULT) 0xC2000005)  /**< Specified node not found in node map. */
#define GENAPI_E_INVALID_NODEHANDLE         ((GENAPIC_RESULT) 0xC2000006)  /**< An invalid node handle has been passed. */
#define GENAPI_E_RESULT_RANGE_EXCEEDED      ((GENAPIC_RESULT) 0xC2000007)  /**< A 64 bit result will be truncated if returned as a 32 bit value. */
#define GENAPI_E_LIMITS_EXCEEDED            ((GENAPIC_RESULT) 0xC2000008)  /**< The value exceeds the valid range. */
#define GENAPI_E_PROPERTY_ERROR             ((GENAPIC_RESULT) 0xC2000009)  /**< Generic GenICam property error occurred. Call GenApiGetLastErrorDetail() for more information about the error. */
#define GENAPI_E_TIMEOUT                    ((GENAPIC_RESULT) 0xC200000A)  /**< Timeout expired. */
#define GENAPI_E_TYPE_ERROR                 ((GENAPIC_RESULT) 0xC200000B)  /**< Expression has wrong type. */
#define GENAPI_E_INDEX_ERROR                ((GENAPIC_RESULT) 0xC200000C)  /**< An index is out of range. */
/*                                                            0xC200000D        left out intentionally */
#define GENAPI_E_OBJECT_ILLEGAL_STATE       ((GENAPIC_RESULT) 0xC200000E)  /**< Object state illegal for operation. Call GenApiGetLastErrorDetail() for more information about the error.*/
#define GENAPI_E_INVALID_NODECALLBACKHANDLE ((GENAPIC_RESULT) 0xC200000F)  /**< An invalid callback handle has been passed. */
#define GENAPI_E_LOGICAL_ERROR              ((GENAPIC_RESULT) 0xC2000010)  /**< Program logic error. Call GenApiGetLastErrorDetail() for more information about the error. */
#define GENAPI_E_INVALID_FILEHANDLE         ((GENAPIC_RESULT) 0xC2000011)  /**< An invalid file handle has been passed. */
/**
* @}
*/


#endif
