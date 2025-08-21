#pragma once

#include <stdint.h>
#include <uxtopapi/NodePropertyValue.h>
#include <uxtopapi/Topology.h>

#if !defined(interface)
#   define interface   struct
#   define TOPOEX_INTERFACE_DEFINED__
#endif

namespace topapi
{

    /// Interface to write to a property collection
    interface INodePropertiesWritable : public INodeProperties
    {
        /// Sets a property value.
        virtual void                SetPropertyValue( PROPKEY, const NodePropertyValue& ) = 0;
        /// Deletes a property from the collection.
        virtual bool                DeleteProperty( PROPKEY ) = 0;
        /// Clears the complete collection.
        virtual bool                DeleteAllProperties() = 0;

        virtual                     ~INodePropertiesWritable( void )
        {
        };
    };

    /// Interface to write to a node.
    interface INodeWritable : public INode
    {
        /// Returns a pointer to the properties collection of this node.
        virtual INodePropertiesWritable* GetProperties() = 0;

        /// Sets the descriptive short text or name of the node.
        virtual void                        SetCaption( const wchar_t* ) = 0;

        /// Sets the descriptive short text or name of the node.
        virtual void                        SetIDString( const wchar_t* ) = 0;

        /// Sets the kind of the node. See ENodeClass for possible values.
        virtual ENodeClass                  SetNodeClass( ENodeClass ) = 0;

        /// Sets the node unique identifier of the parent node.
        virtual NUID                        SetParentNodeUID( NUID ) = 0;

        /// Sets the node unique identifier of the child nodes.
        virtual void                        SetChildNodeUIDs( const NUID* pNodeUIDs, size_t numElements ) = 0;

        virtual                             ~INodeWritable( void )
        {
        };
    };

} // namespace topapi

#if defined(TOPOEX_INTERFACE_DEFINED__)
#   undef interface
#   undef TOPOEX_INTERFACE_DEFINED__
#endif
