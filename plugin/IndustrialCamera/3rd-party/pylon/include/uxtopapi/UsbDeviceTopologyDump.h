//-----------------------------------------------------------------------------
//  Copyright (c) 2012-2024 Basler AG
//-----------------------------------------------------------------------------
#pragma once
#include <uxtopapi/UxTopApi.h>
#include <uxtopapi/Topology.h>
#include "uxapi/uxstatus.h"
#include <uxtopapi/MapPropKey.h>

namespace topapi
{
    /// Callee, AddWChars is called during dump.
    class IUsbDeviceTopologyDumpCallee
    {
    public:
        /// Destructor
        virtual ~IUsbDeviceTopologyDumpCallee()
        {
        };

               /**
               \brief This member function is called during dump of topology.
               \param pWChars Pointer to buffer which constains wide character string in case of success.
               \param numWChars Number of characters written to the buffer.
               \return Returns UX_OK in case of success.
               */
        virtual UXSTATUS AddWChars( const wchar_t* pWChars, size_t numWChars ) = 0;
    };

    /// Contains actual implementation.
    class CUsbDeviceTopologyDumpImpl;

    /// Dump of USB device topology.
    class UX_TOPAPI CUsbDeviceTopologyDump
    {
    public:
        /// Constructor. The description for node property keys will be dumped.
        CUsbDeviceTopologyDump();

        /**
        \brief Constructor.
        \param dumpDescription If true, a short description for each property will be dumped.
        */
        CUsbDeviceTopologyDump( bool dumpDescription );

        /// Destructor.
        virtual ~CUsbDeviceTopologyDump();

        /**
        \brief Performs a dump of the topology tree given by a root node.
        \param rootNode The root node of the topology tree.
        \param callee A user defined callee which handles the output.
        */
        UXSTATUS Dump(
            const INode& rootNode,
            IUsbDeviceTopologyDumpCallee& callee );

        /**
        \brief Performs a dump of the topology tree given by a root node.
        \param rootNode The root node of the topology tree.
        \param filename The filename of the Unicode file the dump is written to. An existing file will be overwritten.

        Performs a dump of the topology tree given by a root node.
        The output is written to a Unicode file. A Unicode BOM (Byte Order Mark) is written at the beginning of the file.
        An existing file will be overwritten.
        */
        UXSTATUS Dump(
            const INode& rootNode,
            const wchar_t* filename );   // Name of a Unicode file (will be overwritten) which contains Unicode.

       /**
       \brief Writes a string representation of node property value to a buffer. This function is not necessary for a dump.
       \param nodePropertyValue Node property value.
       \param pPropKeyFormat Defines the format. This parameter can be NULL.
       \param pBuffer The buffer were the wide character string is copied to.
       \param bufferNumWChars The size of the buffer in wide characters. The number of wide characters needed for string conversion is set. If the buffer is to small, UX_E_INSUFFICIENT_BUFFER is returned.
       \return Returns UX_E_FATAL in case of an error, UX_E_INSUFFICIENT_BUFFER in case of an insufficient buffer, UX_E_INVALID_PARAMETER in case of bufferNumWChars is big enough but pBuffer is NULL, UX_OK otherwise.
       */
        static UXSTATUS NodePropertyValueToWString(
            const NodePropertyValue& nodePropertyValue,
            const PropKeyFormat_t* pPropKeyFormat,
            wchar_t* pBuffer,
            size_t& bufferNumWChars );

        /**
        \brief Writes a string representation of an item of a node property value (which holds an array) to a buffer. This function is not necessary for a dump.
        \param nodePropertyValue Node property value.
        \param index The index of the array item.
        \param pPropKeyFormat Defines the format. This parameter can be NULL.
        \param pBuffer The buffer were the wide character string is copied to.
        \param bufferNumWChars The size of the buffer in wide characters. The number of wide characters needed for string conversion is set. If the buffer is to small, UX_E_INSUFFICIENT_BUFFER is returned.
        \return Returns UX_E_INVALID_PARAMETER if node property value is not an array or index is out of range.
                Returns UX_E_FATAL in case of an error, UX_E_INSUFFICIENT_BUFFER in case of an insufficient buffer, UX_E_INVALID_PARAMETER in case of bufferNumWChars is big enough but pBuffer is NULL, UX_OK otherwise.
        */
        static UXSTATUS NodePropertyValueToWString(
            const NodePropertyValue& nodePropertyValue,
            size_t index,
            const PropKeyFormat_t* pPropKeyFormat,
            wchar_t* pBuffer,
            size_t& bufferNumWChars );

    private:
        CUsbDeviceTopologyDumpImpl* m_pUsbDeviceTopologyDumpImpl;   ///< Pointer to implementation.
    };
}
