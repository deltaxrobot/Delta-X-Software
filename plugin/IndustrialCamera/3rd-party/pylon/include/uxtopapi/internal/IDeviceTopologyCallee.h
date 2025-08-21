//-----------------------------------------------------------------------------
//  Copyright (c) 2012-2024 Basler AG
//-----------------------------------------------------------------------------
#pragma once

#include <uxtopapi/NodePropertyKeys.h>
#include <uxtopapi/NodePropertyValue.h>
#include <uxtopapi/Topology.h>

#if !defined(interface)
#   define interface   struct
#   define TOPOCALLEE_INTERFACE_DEFINED__
#endif

namespace topapi
{
    interface IDeviceTopologyCallee
    {
        virtual NUID CallbackAddNode( NUID parentNuid, ENodeClass nodeClass ) = 0;
        virtual bool CallbackUpdateNode( NUID nuid, ENodeClass nodeClass ) = 0;
        virtual bool CallbackRemoveNode( NUID nuid ) = 0; // entfernt Knoten und Unterknoten

        virtual bool CallbackAddProperty( NUID nuid, PROPKEY propId, const NodePropertyValue& nodePropertyValue ) = 0;
        virtual bool CallbackUpdateProperty( NUID nuid, PROPKEY propId, const NodePropertyValue& nodePropertyValue ) = 0;
        virtual bool CallbackRemoveProperty( NUID nuid, PROPKEY propId ) = 0;


        virtual bool BeginOperation( void ) = 0;
        virtual bool FinishOperation( bool successful ) = 0;
    };
}

#if defined(TOPOCALLEE_INTERFACE_DEFINED__)
#   undef interface
#   undef TOPOCALLEE_INTERFACE_DEFINED__
#endif
