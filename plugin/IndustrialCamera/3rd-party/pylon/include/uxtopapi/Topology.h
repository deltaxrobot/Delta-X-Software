#pragma once

#include <stdint.h>
#include <uxtopapi/NodePropertyValue.h>

#if !defined(interface)
#   define interface   struct
#   define TOPO_INTERFACE_DEFINED__
#endif

namespace topapi
{
    // TODO: must be moved somewhere else
    typedef size_t          NUID;                ///< Node unique identifier.
#define INVALID_NUID     ((topapi::NUID)0)       ///< Invalid node unique identifier.

    typedef uint32_t        PROPKEY;            ///< Type for a packed property id
#define INVALID_PROPKEY  ((topapi::PROPKEY)0)    ///< Invalid node property key.

    /// Node class.
    enum ENodeClass
    {
        NodeClass_Invalid = 0,                 //!< Marks an invalid/unintialized NodeClass
        NodeClass_Root = 1,                    //!< The root node of the device tree.
        NodeClass_HostController,              //!< Device is an USB host controller device.
        NodeClass_RootHub,                     //!< Device is a root hub device, this is a special hub device.
        NodeClass_Hub,                         //!< Device is a hub device.
        NodeClass_CompositeDevice,             //!< Device is a composite device.
        NodeClass_Audio,                       //!< Device is an audio device.
        NodeClass_CommunicationsAndCdcControl, //!< Device is a communications and CDC control device.
        NodeClass_HumanInterface,              //!< Device is a human interface device (HID).
        NodeClass_Physical,                    //!< Device is a physical device.
        NodeClass_Image,                       //!< Device is an image device.
        NodeClass_Printer,                     //!< Device is a printer device.
        NodeClass_MassStorage,                 //!< Device is a mass storage device.
        NodeClass_CdcData,                     //!< Device is a CDC data device.
        NodeClass_SmartCard,                   //!< Device is a smart card device.
        NodeClass_ContentSecurity,             //!< Device is a content security device.
        NodeClass_Video,                       //!< Device is a video device.
        NodeClass_PersonalHealthcare,          //!< Device is a personal healthcare device.
        NodeClass_AudioVideo,                  //!< Device is an audio/video device.
        NodeClass_Diagnostic,                  //!< Device is a diagnostic device.
        NodeClass_WirelessController,          //!< Device is a wireless controller device.
        NodeClass_Miscellaneous,               //!< Device is a miscellaneous device.
        NodeClass_ApplicationSpecific,         //!< Device is an application specific device.
        NodeClass_VendorSpecific,              //!< Device is a vendor specific device.
        NodeClass_Device,                      //!< Device is a sort of device which does not fit to any device category above.
        // Special meaning
        // Special meaning - human interface device
        NodeClass_Keyboard,                    //!< Device is a keyboard, this a special human interface device.
        NodeClass_Mouse,                       //!< Device is a mouse, this a special human interface device.
        // Special meaning - miscellaneous device
        NodeClass_U3V,                         //!< Device is an U3V device, this a special miscellaneous device.
        // Special meaning - mass storage device
        NodeClass_DiskDrive,
        NodeClass_CdRom,
        // Special meaning - vendor specific
        NodeClass_Ports
    };


    // ----------------------------------------------------------------------
    // topapi::INodeProperties
    // ----------------------------------------------------------------------
    /**
        \brief Interface to access the property-collection of a node.

        Interface to access the property-collection of a node.
        You can obtain a pointer to a INodeProperties by calling INode::GetProperties().

        When accessing properties make sure you always handle non existent properties correctly in you code.
        There a no properties which are guaranteed to exists in the collection.
    */
    interface INodeProperties
    {
        /// Get the number of properties in the collection
        virtual size_t                      GetNumProperties() const = 0;
        /// Fill an array of PropKeys.
        /// If numElements is large enough the function returns the number of properties actually copied to the buffer.
        /// If numElements is not large enough the function returns the number of elements needed.
        virtual size_t                      GetPropertyKeys( PROPKEY*, size_t numElements ) const = 0;
        /// Returns true if the specified PropKey exists in the collection.
        virtual bool                        HasProperty( PROPKEY ) const = 0;

        /// Get a property by index (useful for loops). If Index is out of bounds, NULL will be returned.
        virtual const NodePropertyValue* GetPropertyValueByIndex( size_t index ) const = 0;
        /// Get a property by property key. If the specified PropKey does not exist, NULL will be returned.
        virtual const NodePropertyValue* GetPropertyValue( PROPKEY ) const = 0;

        virtual ~INodeProperties()
        {
        };
    };


    // ----------------------------------------------------------------------
    // topapi::INode
    // ----------------------------------------------------------------------
    /**
        \brief Interface to access a node.

        Interface to access a node.
        You can obtain a pointer to a INode by calling ITopology::GetRootNode() or ITopology::GetSpecificNode().
        Call INode::GetChildNode() or INode::GetParentNode() to obtain a pointer to a child or parent of the node.

        The node class specifies the the kind of a node. See ENodeClass for possible values.
        The caption contains a text of the node. It is usually a name or short descripton of the node.
        To get more information about a node you can call INode::GetProperties() to access all properties, inclusive the caption, of the node.

    */
    interface INode
    {
        /// Returns the unique identifier of the node.
        virtual NUID            GetIdentifier() const = 0;

        /// Returns descriptive short text or name of the node. The description can also be retrieved from the properties collection.
        /// If the node doesn't have caption, a pointer to an empty string will be returned.
        virtual const wchar_t* GetCaption() const = 0;

        /// Returns an ID string which can be used to identify the node. The ID string can also be retrieved from the properties collection.
        virtual const wchar_t* GetIDString() const = 0;

        /// The kind of the node. See ENodeClass for possible values
        virtual ENodeClass      GetNodeClass() const = 0;

        /// Returns the user specified data. The node itself will not use or modify this value. This value can be set using INode::SetUserData().
        virtual void* GetUserData() const = 0;

        /// Sets the user specified data. The node itself will not use or modify this value. This value can be read using INode::GetUserData().
        virtual void* SetUserData( void* data ) = 0;

        /// Returns the number of child nodes. Use can use this value when calling INode::GetChildNode().
        virtual size_t          GetNumChildNodes() const = 0;

        /// Retrieve a child of the current node. make sure index is always less than the returnvalue of INode::GetNumChildNodes().
        /// If the index is out of bounds NULL will be returned.
        virtual INode* GetChildNode( size_t index ) const = 0;

        /// Retrieve the parent node of this node. If this is called on the root node, NULL will be returned.
        virtual INode* GetParentNode() const = 0;

        /// Returns a pointer to the properties collection of this node.
        virtual const INodeProperties* GetProperties() const = 0;

        virtual                 ~INode( void )
        {
        };
    };


    /// Defines how to initialize a database topology.
    enum EInitializeFlags
    {
        InitializeFlags_CreateNew = 1,       //!< Create a new topology and initialize with data from the local system. Any existing data will be overwritten.
        InitializeFlags_OpenExisting = 2,  //!< Open an existing file. pwszInitString parameter of ITopology::Initialize() must specify a valid file.
        InitializeFlags_CreateEmpty = 4,   //!< Create a new but empty topology. This flag is used internally.

        // the following values are bitflags (1,2,4,8,16,...) and should be tested by a bitwise and (&)
        InitializeFlags_AddUSB = 0x10000,  //!< Add USB topology nodes.
        // , InitializeFlags_AddGEV = 0x20000 //!< Add GEV topology nodes (not supported yet).

        InitializeFlags_AddAll = InitializeFlags_AddUSB, /* | InitializeFlags_AddGEV */ /// Add all topology nodes.

        // convenience flags
        InitializeFlags_CreateNewAndAddAll = (InitializeFlags_CreateNew | InitializeFlags_AddAll)
    };

    /// Reason for a call of a callback function.
    enum ECallbackReason
    {
        CallbackReason_DeviceArrived,
        CallbackReason_DeviceRemoved,
        CallbackReason_TopologyUpdated
    };


    /// Function pointer for device notification callbacks
    typedef void (*ChangeNotificationCallbackFuncPointer)(ECallbackReason, const INode*, void*);

    // ----------------------------------------------------------------------
    // topapi::ITopology
    // ----------------------------------------------------------------------
    /**
        \brief Interface to access USB Topology data.

        Interface to access USB Topology data. You can call ITopology::Initialize() to fill the fill to topology data from your current system.

        You can walk the topology hierarchy using the INode interface.

    */
    interface ITopology
    {
        /// Initializes a topology object with data. The pwszParameter specifies a filename to store the topology data in. If you pass NULL the data is stored in memory only.
        /// The initFlags parameter specifies the way the topology data is build. See EInitializeFlags for details.
        /// If you pass a valid filename in pwszInitString and specify InitailizeFlags_CreateNew in initFlags the file will be overwritten.
        virtual bool Initialize( const wchar_t* pwszInitString, EInitializeFlags initFlags ) = 0;
        /// Unintializes the topology object. In case the data is stored in a file (see ITopology::Initialize()) the file is closed, but not deleted.
        virtual bool Uninitialize() = 0;

        /// Reload all data in topology
        virtual bool Refresh() = 0;

        /// Returns a pointer to the one and only root node of the topology tree. In case there is no root node or Initialize hasn't been called NULL is returned.
        virtual INode* GetRootNode() const = 0;

        /// Returns a pointer to specific node specifier by a NUID. If specified node does not exist NULL will be returned.
        virtual INode* GetSpecificNode( NUID ) const = 0;

        /// query all nodes and return NUIDs matching. You can use GetSpecificNode to access the nodes found
        virtual bool FindNodes( ENodeClass* pNodeClass, const void** pUserData, const PROPKEY* pPropKeys, const NodePropertyValue* pPropValues, size_t cntProps, NodePropertyValue* pNodeUIDs ) const = 0;


        /// Get informed about device changes (not implemented (yet)
        virtual ChangeNotificationCallbackFuncPointer RegisterChangeNotificationCallback( ChangeNotificationCallbackFuncPointer, void* Context ) = 0;
        virtual bool DeregisterChangeNotificationCallback( ChangeNotificationCallbackFuncPointer ) = 0;

        virtual ~ITopology( void )
        {
        };
    };
} // namespace topapi

#if defined(TOPO_INTERFACE_DEFINED__)
#   undef interface
#   undef TOPO_INTERFACE_DEFINED__
#endif
