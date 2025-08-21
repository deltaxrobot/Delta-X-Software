//-----------------------------------------------------------------------------
//  Copyright (c) 2012-2024 Basler AG
//-----------------------------------------------------------------------------
/**
 * \file
 * \brief Header of the topology library.
 */

#pragma once

#include "UxTopDll.h"
#include <uxapi/UxTypes.h>
#include <uxapi/uxstatus.h>

#include <uxtopapi/Topology.h>

namespace topapi
{

    // ----------------------------------------------------------------------
    // CreateTopologyInstance()
    // ----------------------------------------------------------------------
    /**

        \brief Creates an instance of a Topology object.

        Creates an instance of a topology object representing the device topology and returns it in the output parameter.
        You must call DestroyTopologyInstance to free the object when you don't it anymore.

        \return Status of the operation.

    */
    UX_TOPAPI UXSTATUS UX_TOPCALL CreateTopologyInstance( topapi::ITopology** ppTopology );


    // ----------------------------------------------------------------------
    // DestroyTopologyInstance()
    // ----------------------------------------------------------------------
    /**

        \brief Frees an instance of a Topology object.

        Frees an instance of a topology object created by CreateTopologyInstance.
        You must call DestroyTopologyInstance to free the object when you don't it anymore.

        \return Status of the operation.

        \error
            No-Fail

    */
    UX_TOPAPI UXSTATUS UX_TOPCALL DestroyTopologyInstance( topapi::ITopology* pTopology );


    // ----------------------------------------------------------------------
    // FindNode
    // ----------------------------------------------------------------------
    /**

        \brief Finds a node by comparing the value of the propKeyToSearch with the value propValueToSearch.

        This function recursively walks the node tree starting at pStartNode and searches a node having the property value specified.
        If a node has been found the search is stopped and the pointer to that node is returned.

        \return returns the pointer to the node matching the property value. If no node is found NULL is returned.

    */
    UX_TOPAPI const INode* UX_TOPCALL FindNode( const INode* pStartNode, const PROPKEY propKeyToSearch, const NodePropertyValue& propValueToSearch );


    // ----------------------------------------------------------------------
    // GetNodePath
    // ----------------------------------------------------------------------
    /**

        \brief Returns the path to the node specified.

        This function determines the path to the node passed in pNode and copies it to the buffer passed pwszPath. The path is seperated

        \return Returns the number of characters copied to the output buffer. If the supplied buffer is not large enough the number of characters needed is returned.
                In case of an error 0 is returned

    */
    UX_TOPAPI size_t UX_TOPCALL GetNodePath( const INode* pNode, wchar_t separatorChar, wchar_t* pwszPath, const size_t NumChars );


    // ----------------------------------------------------------------------
    // CompareTopologies
    // ----------------------------------------------------------------------
    /**

        \brief Compares two topolgies recursively.



        \return Returns the number of characters copied to the output buffer. If the supplied buffer is not large enough the number of characters needed is returned.
                In case of an error 0 is returned

    */
    UX_TOPAPI bool UX_TOPCALL CompareTopologies( const INode* pStartNode1, const INode* pStartNode2, NodePropertyValue* NodesIn1ButNotIn2, NodePropertyValue* NodesIn2ButNotIn1 );


} // namespace topapi
