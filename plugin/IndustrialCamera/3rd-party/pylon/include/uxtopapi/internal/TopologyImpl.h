#pragma once

#include <uxtopapi/Topology.h>
#include <uxtopapi/internal/IDeviceTopologyCallee.h>

// for uxcallbacks
#include <uxapi/UxNotification.h>

#include <windows.h> // for criticalsectioon

namespace topapi
{
    class CSQLTopologyDS;
    class CNodeImpl;

    /////////////////////////////////////////////////////////////////
    // very simple critical section class
    class CCriticalSection
    {
    public:
        explicit CCriticalSection( unsigned int spinCount = 0 )
        {
            ::InitializeCriticalSectionAndSpinCount( &m_CS, static_cast<DWORD>(spinCount & DWORD( -1 )) );
        }

        ~CCriticalSection()
        {
            ::DeleteCriticalSection( &m_CS );
        }

        void Lock()
        {
            ::EnterCriticalSection( &m_CS );
        }

        void Unlock()
        {
            ::LeaveCriticalSection( &m_CS );
        }

    protected:
        CRITICAL_SECTION    m_CS;

    private:
        // no copying/assignment
        CCriticalSection( const CCriticalSection& );
        CCriticalSection& operator=( const CCriticalSection& );
    };


    /////////////////////////////////////////////////////////////////
    // automatic locking/unlocking
    class CAutoCriticalSection
    {
    public:
        explicit CAutoCriticalSection( CCriticalSection& cs )
            : m_pCS( &cs )
        {
            if (m_pCS != NULL)
            {
                m_pCS->Lock();
            }
        }

        ~CAutoCriticalSection()
        {
            Leave();
        }

        void Leave()
        {
            if (m_pCS != NULL)
            {
                m_pCS->Unlock();
                m_pCS = NULL;
            }
        }
    private:
        CCriticalSection* m_pCS;

    private:
        // no copying/assignment
        CAutoCriticalSection( const CAutoCriticalSection& );
        CAutoCriticalSection& operator=( const CAutoCriticalSection& );
    };


    /////////////////////////////////////////////////////////////////
    // Generic topology implementation.
    // Currently only USB topology is read. The InitFlags determine which topologies are added to the store
    class CTopologyImpl : public ITopology
        , public IDeviceTopologyCallee
    {
    public:
        /// Constructor
        CTopologyImpl( void );

        /// Destructor
        virtual ~CTopologyImpl( void );

    public:
        // ITopology interface

        /**
        \brief Initializes a topology object with data. The pwszInitString specifies a filename to store the topology data in. If you pass NULL the data is stored in memory only.
        \param pwszInitString The pwszInitString specifies a filename to store the topology data in.
        \param initFlags The initFlags parameter specifies the way the topology data is build. See EInitializeFlags for details. If you pass a valid filename in pwszInitString and specify InitailizeFlags_CreateNew in initFlags the file will be overwritten.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool Initialize( const wchar_t* pwszInitString, EInitializeFlags initFlags );

        /**
        \brief Unitialize topology
        \return Returns true in case of success, false otherwise.
        */
        virtual bool Uninitialize();

        /**
        \brief Reload all data in topology. When this function returns all existing nodes will be invalid!
        \return Returns true in case of success, false otherwise.
        */
        virtual bool Refresh();

        /**
        \brief Get the global root node.
        \return Returns a pointer to the global root node or NULL if no such node exists.
        */
        virtual INode* GetRootNode() const;

        /**
        \brief Get any node specified by UID
        \param nuid The node unique identifier.
        \return Returns a pointer to the node or NULL if no such node exists.
        */
        virtual INode* GetSpecificNode( NUID nuid ) const;

        /**
        \brief query all nodes and return NUIDs matching the criteria. You can use GetSpecificNode to access the nodes found.
        \param pNodeClass   Pointer to the NodeClass to match or NULL if any node class should match
        \param pUserData    Pointer to the UserData value to match or NULL if any UserData should match. If you want to match against a user data value of 0 you must pass a valid pointer pointer to void* containg the value 0.
        \param pPropKeys    An array of property keys or NULL if any property values should match.
        \param pPropValues  An array of PropertyValues to compare or NULL if any property values should match. You may not pass NodePropValues containing arrays.
        \param cntProps     Number of values in the pPropKeys and pPropValues arrays. If you pass NULL for pPropKeys or pPropValues you must set this to 0.
        \param pNodeUIDs    This NodePropertyValue will hold an array of NUID values.
        \return Returns true if operation completed successfully. To determine how many matches were found you must check number of elements in the pNodeUIDs output parameter.
        */
        virtual bool FindNodes( ENodeClass* pNodeClass, const void** pUserData, const PROPKEY* pPropKeys, const NodePropertyValue* pPropValues, size_t cntProps, NodePropertyValue* pNodeUIDs ) const;

        // get informed about device changes

        /** Register callback.
        \brief changeNotificationCallbackFuncPointer Callback to register.
        \brief Context A user defined context. Can be NULL.
        */
        virtual ChangeNotificationCallbackFuncPointer RegisterChangeNotificationCallback( topapi::ChangeNotificationCallbackFuncPointer changeNotificationCallbackFuncPointer, void* Context );

        /** Unregister callback.
        \brief changeNotificationCallbackFuncPointer Callback to un-register.
        */
        virtual bool DeregisterChangeNotificationCallback( topapi::ChangeNotificationCallbackFuncPointer changeNotificationCallbackFuncPointer );

    public:
        // IDeviceTopologyCallee interface

        /**
        \brief Adds a new node to the topology.
        \param parentNuid Node unique identifier of the parent node.
        \param nodeClass The node class of the new node.
        \return INVALID_NUID in case of failure, a valid unique idenfifier for the new node oherwise.
        */
        virtual NUID CallbackAddNode( NUID parentNuid, ENodeClass nodeClass );

        /**
        \brief Updates the node class of an existing node.
        \param nuid Node unique identifier of the node.
        \param nodeClass The node class.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool CallbackUpdateNode( NUID nuid, ENodeClass nodeClass );

        /**
        \brief Removes a node.
        \param nuid Node unique identifier of the node to remove.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool CallbackRemoveNode( NUID nuid );

        /**
        \brief Adds a property to a node.
        \param nuid Node unique identifier of the node.
        \param propKey The property key of the property value which has be be added to the node.
        \param nodePropertyValue The property value which has to be added.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool CallbackAddProperty( NUID nuid, PROPKEY propKey, const NodePropertyValue& nodePropertyValue );

        /**
        \brief Updates a property of an existing node.
        \param nuid Node unique identifier of the node.
        \param propKey The property key of the property value which has be be added to the node.
        \param nodePropertyValue The property value which has to be added.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool CallbackUpdateProperty( NUID nuid, PROPKEY propKey, const NodePropertyValue& nodePropertyValue );

        /**
        \brief Removes an existing property of an existing node.
        \param nuid Node unique identifier of the node.
        \param propKey The property key of the property value which has be be removed.
        \return Returns true in case of success, false otherwise.
        */
        virtual bool CallbackRemoveProperty( NUID nuid, PROPKEY propKey );

        /// Has to be called before any operation.
        virtual bool BeginOperation( void );

        /// Has to be called to finish operations(s).
        virtual bool FinishOperation( bool successful );


    protected:
        static void __stdcall TheStaticUxCallbackFunction( const uxapi::UxCallbackData* pCBData );

    protected:
        static const uxapi::ECallbackType m_uxCallbackTypes[3];

        CSQLTopologyDS* m_pStore;       ///< The data storage instance.
        ChangeNotificationCallbackFuncPointer m_pNotificationCallbackFunc;  ///< The notification callback function.
        void* m_NotificationCallbackContextValue;  ///< The notification callback context value supplied by the user.
        NodePropertyValue   m_Filename;     ///< the data base file name as specified by the user, can be NULL.
        EInitializeFlags    m_InitFlags;    ///< Initialization flags, see EInitializeFlags
        uxapi::UxCallbackHandle m_uxCallbackContexts[_countof( m_uxCallbackTypes )];
        mutable CCriticalSection    m_CS;
        bool                m_RefreshAllowed;
        NodePropertyValue   m_CurrentFilename; ///< the name of the currently used datastore (due to swap operations this can differ from m_FileName).
    };
}
