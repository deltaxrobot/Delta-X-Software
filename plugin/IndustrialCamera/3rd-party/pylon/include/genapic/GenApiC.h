/*-----------------------------------------------------------------------------
    Basler pylon C SDK
    Copyright (c) 2009-2021 Basler AG
    http://www.baslerweb.com
    Author: AH, TK
-----------------------------------------------------------------------------*/

/**
    \file
    \brief GenApi C bindings.
*/

#ifndef GENAPI_GENAPIC_H_
#define GENAPI_GENAPIC_H_

#include <stddef.h>

#include <genapic/GenApiCDefines.h>

#pragma pack(push, GENAPIC_PACKING)

#include <genapic/GenApiCTypes.h>
#include <genapic/GenApiCEnums.h>
#include <genapic/GenApiCError.h>

#define GENAPIC_DECLARE_HANDLE(name) struct name##_; typedef struct name##_ *name

/**
* \addtogroup genapi GenApi Interface
* @{
*/

/** \brief A value for invalid / uninitialized handles. */
#ifdef __cplusplus
#   define GENAPIC_INVALID_HANDLE ( 0 ) /* C++ won't allow to assign a void* to a typed pointer (HANDLE) */
#else
#   define GENAPIC_INVALID_HANDLE ( (void*)0 )
#endif

GENAPIC_DECLARE_HANDLE( NODE_HANDLE ); /**< \brief A handle for a node object. */
GENAPIC_DECLARE_HANDLE( NODEMAP_HANDLE ); /**< \brief A handle for a node map object. */
GENAPIC_DECLARE_HANDLE( GENAPI_FILE_HANDLE ); /**< \brief A handle for a GenApi file object. */
GENAPIC_DECLARE_HANDLE( NODE_CALLBACK_HANDLE ); /**< \brief A handle for a node callback object. */

/**
* @}
*/


#ifdef __cplusplus

// avoid namespace ambiguities between std::_Bool (from yvals.h) and ::_Bool (from GenApiCTypes.h)
#ifdef _MSC_VER
#   define _Bool ::_Bool
#   define PYLONC_BOOL_DEFINED
#endif

extern "C" {

#endif /* __cplusplus */

    typedef void GENAPIC_CC NodeCallbackFunction_t( NODE_HANDLE h );

    /*
    * ----------------------------------------------------------------------------
    * Error handling
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiGetLastErrorMessage( char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiGetLastErrorDetail( char* pBuf, size_t* pBufLen );


    /*
    * ----------------------------------------------------------------------------
    * Nodemap
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeMapGetNode( NODEMAP_HANDLE hMap, const char* pName, NODE_HANDLE* phNode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeMapGetNumNodes( NODEMAP_HANDLE hMap, size_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeMapGetNodeByIndex( NODEMAP_HANDLE hMap, size_t index, NODE_HANDLE* phNode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeMapPoll( NODEMAP_HANDLE hMap, int64_t timestamp );


    /*
    * ----------------------------------------------------------------------------
    * INode Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetAccessMode( NODE_HANDLE hNode, EGenApiAccessMode* pAccessMode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetName( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetNameSpace( NODE_HANDLE hNode, EGenApiNameSpace* pNamespace );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetVisibility( NODE_HANDLE hNode, EGenApiVisibility* pVisibility );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeInvalidateNode( NODE_HANDLE hNode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetCachingMode( NODE_HANDLE hNode, EGenApiCachingMode* pCachingMode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetToolTip( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetDescription( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetDisplayName( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetType( NODE_HANDLE hNode, EGenApiNodeType* pType );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetPollingTime( NODE_HANDLE hNode, int64_t* pPollingTime );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeRegisterCallback( NODE_HANDLE hNode, NodeCallbackFunction_t* pCbFunction, NODE_CALLBACK_HANDLE* phCb );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeDeregisterCallback( NODE_HANDLE hNode, NODE_CALLBACK_HANDLE hCb );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeImposeAccessMode( NODE_HANDLE hNode, EGenApiAccessMode imposedAccessMode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeImposeVisibility( NODE_HANDLE hNode, EGenApiVisibility imposedVisibility );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeIsImplemented( NODE_HANDLE hNode, _Bool* pResult );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeIsReadable( NODE_HANDLE hNode, _Bool* pResult );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeIsWritable( NODE_HANDLE hNode, _Bool* pResult );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeIsAvailable( NODE_HANDLE hNode, _Bool* pResult );


    /*
    * ----------------------------------------------------------------------------
    * IValue Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeToString( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeToStringEx( NODE_HANDLE hNode, _Bool verify, char* pBuf, size_t* pBufLen );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeFromStringEx( NODE_HANDLE hNode, _Bool verify, const char* pString );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeFromString( NODE_HANDLE hNode, const char* pString );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiNodeGetAlias( NODE_HANDLE hNode, NODE_HANDLE* phNode );


    /*
    * ----------------------------------------------------------------------------
    * IInteger Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerSetValue( NODE_HANDLE hNode, int64_t value );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerSetValueEx( NODE_HANDLE hNode, _Bool verify, int64_t value );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetValue( NODE_HANDLE hNode, int64_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetValueEx( NODE_HANDLE hNode, _Bool verify, int64_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetMin( NODE_HANDLE hNode, int64_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetMax( NODE_HANDLE hNode, int64_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetInc( NODE_HANDLE hNode, int64_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiIntegerGetRepresentation( NODE_HANDLE hNode, EGenApiRepresentation* pValue );


    /*
    * ----------------------------------------------------------------------------
    * IBoolean Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiBooleanSetValue( NODE_HANDLE hNode, _Bool value );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiBooleanGetValue( NODE_HANDLE hNode, _Bool* pValue );


    /*
    * ----------------------------------------------------------------------------
    * IFloat Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatSetValue( NODE_HANDLE hNode, double value );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatSetValueEx( NODE_HANDLE hNode, _Bool verify, double value );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetValue( NODE_HANDLE hNode, double* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetValueEx( NODE_HANDLE hNode, _Bool verify, double* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetMin( NODE_HANDLE hNode, double* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetMax( NODE_HANDLE hNode, double* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetRepresentation( NODE_HANDLE hNode, EGenApiRepresentation* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFloatGetUnit( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );


    /*
    * ----------------------------------------------------------------------------
    * ICommand Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiCommandExecute( NODE_HANDLE hNode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiCommandIsDone( NODE_HANDLE hNode, _Bool* pValue );


    /*
    * ----------------------------------------------------------------------------
    * IEnumeration Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiEnumerationGetNumEntries( NODE_HANDLE hNode, size_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiEnumerationGetEntryByIndex( NODE_HANDLE hNode, size_t index, NODE_HANDLE* pEntry );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiEnumerationGetEntryByName( NODE_HANDLE hNode, const char* pName, NODE_HANDLE* pEntry );


    /*
    * ----------------------------------------------------------------------------
    * IEnumEntry Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiEnumerationEntryGetValue( NODE_HANDLE hNode, int* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiEnumerationEntryGetSymbolic( NODE_HANDLE hNode, char* pBuf, size_t* pBufLen );


    /*
    * ----------------------------------------------------------------------------
    * ISelector Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiSelectorGetNumSelectingFeatures( NODE_HANDLE hNode, size_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiSelectorGetSelectingFeatureByIndex( NODE_HANDLE hNode, size_t index, NODE_HANDLE* phNode );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiSelectorGetNumSelectedFeatures( NODE_HANDLE hNode, size_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiSelectorGetSelectedFeatureByIndex( NODE_HANDLE hNode, size_t index, NODE_HANDLE* phNode );


    /*
    * ----------------------------------------------------------------------------
    * IRegister Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiRegisterGetValue( NODE_HANDLE hNode, void* pBuffer, size_t* pLength );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiRegisterSetValue( NODE_HANDLE hNode, const void* pBuffer, size_t length );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiRegisterGetLength( NODE_HANDLE hNode, size_t* pLength );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiRegisterGetAddress( NODE_HANDLE hNode, int64_t* pAddress );


    /*
    * ----------------------------------------------------------------------------
    * Category Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiCategoryGetNumFeatures( NODE_HANDLE hNode, size_t* pValue );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiCategoryGetFeatureByIndex( NODE_HANDLE hNode, size_t index, NODE_HANDLE* phEntry );


    /*
    * ----------------------------------------------------------------------------
    * IPort Nodes
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiPortRead( NODE_HANDLE hNode, void* pBuffer, int64_t Address, size_t Length );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiPortWrite( NODE_HANDLE hNode, const void* pBuffer, int64_t Address, size_t Length );


    /*
    * ----------------------------------------------------------------------------
    * DeviceFileStream
    * ----------------------------------------------------------------------------
    */
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFilesAreSupported( NODEMAP_HANDLE hMap, _Bool* pResult );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFileExists( NODEMAP_HANDLE hMap, const char* pFileName, _Bool* pResult );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFileOpen( NODEMAP_HANDLE hMap, const char* pFileName, EGenApiFileAccessMode accessMode, GENAPI_FILE_HANDLE* phFile );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFileRead( GENAPI_FILE_HANDLE hFile, void* pBuffer, size_t* pLength );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFileWrite( GENAPI_FILE_HANDLE hFile, const void* pBuffer, size_t length );
    GENAPIC_API GENAPIC_RESULT GENAPIC_CC GenApiFileClose( GENAPI_FILE_HANDLE hFile );

#ifdef __cplusplus
} /* extern "C" */

#ifdef PYLONC_BOOL_DEFINED
#   undef _Bool
#   undef PYLONC_BOOL_DEFINED
#endif

#endif /* __cplusplus */

#include <genapic/GenApiC32BitMethods.h>

#pragma pack(pop)

#endif
