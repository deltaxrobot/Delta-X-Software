//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2018-2021 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains the class CBooleanParameter used to simplify access to %GenApi parameters.
*/

#ifndef INCLUDED_BASLER_PYLON_CBOOLEANPARAMETER_H
#define INCLUDED_BASLER_PYLON_CBOOLEANPARAMETER_H

#pragma once

#include <pylon/PylonBase.h>
#include <GenApi/IBoolean.h>
#include <pylon/Parameter.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable : 4275 ) // Class needs to have a dll interface to be used by clients of the class.
#   pragma warning( disable : 4250 ) // warning C4250: 'Pylon::CXYZParameter': inherits 'Pylon::CParameter::Pylon::CParameter::ZYX' via dominance
#endif

namespace Pylon
{
    /*!
    \brief Extends the GenApi::IBoolean interface with convenience methods.
    */
    interface IBooleanEx : virtual public GENAPI_NAMESPACE::IBoolean, virtual public IValueEx
    {
        using GENAPI_NAMESPACE::IBoolean::operator=;

        /*!
        \brief Sets the Boolean value of the parameter if the parameter is writable.
        \return Returns false if the parameter is not writable.
        \param[in] value The Boolean value to set.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the preconditions are not met or if writing the value fails.
        */
        virtual bool TrySetValue( bool value ) = 0;


        /*!
        \brief Gets the Boolean value of the parameter if the parameter is readable.
        \brief Otherwise returns the default value.
        \return Returns the parameter value if the parameter is readable. Otherwise returns the default value.
        \param[in] defaultValue The default value returned if the parameter is not readable.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if reading the value fails.
        */
        virtual bool GetValueOrDefault( bool defaultValue ) = 0;
    };


    /*!
    \brief CBooleanParameter class used to simplify access to %GenApi parameters.
    */
    class PYLONBASE_API CBooleanParameter : public IBooleanEx, public CParameter
    {
    public:
        /*!
        \brief Creates an empty CBooleanParameter object.
        \error
            Does not throw C++ exceptions.
        */
        CBooleanParameter();


        /*!
        \brief Creates a CBooleanParameter object and attaches it to a node, typically retrieved for a nodemap calling GetNode().
        \param[in] pNode The node to attach.
        \post
        <ul>
        <li>If the passed node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the passed node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the source of the attached \c pNode has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            Does not throw C++ exceptions.
        */
        explicit CBooleanParameter( GENAPI_NAMESPACE::INode* pNode );


        /*!
        \brief Creates a CBooleanParameter object and attaches it to a node of a matching type.
        \param[in] pBoolean The node to attach.
        \post
            The parameter object must not be used to access the node's functionality if the source of the attached \c pBoolean has been destroyed. In this case, call Release() or attach a new node.
        \error
            Does not throw C++ exceptions.
        */
        explicit CBooleanParameter( GENAPI_NAMESPACE::IBoolean* pBoolean );


        /*!
        \brief Creates a CBooleanParameter object and attaches it to a node retrieved from the provided node map.
        \param[in] pNodeMap The node map. The source of the parameter.
        \param[in] pName The name of the parameter to attach.
        \post
        <ul>
        <li>If \c pNodeMap or \c name is NULL, the parameter will be empty, see IsValid().
        <li>If the node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the provided node map has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            The call to GenApi::INodeMap::GetNode can throw C++ exceptions.
        */
        CBooleanParameter( GENAPI_NAMESPACE::INodeMap* pNodeMap, const char* pName );


        /*!
        \brief Creates a CBooleanParameter object and attaches it to a node retrieved from the provided node map.
        \param[in] nodeMap The node map. The source of the parameter.
        \param[in] pName The name of the parameter to attach.
        \post
        <ul>
        <li>If \c name is NULL, the parameter will be empty, see IsValid().
        <li>If the node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the provided node map has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            The call to GenApi::INodeMap::GetNode can throw C++ exceptions.
        */
        CBooleanParameter( GENAPI_NAMESPACE::INodeMap& nodeMap, const char* pName );


        /*!
        \brief Copies a CBooleanParameter object.
        \param[in] rhs The object to copy.
        \error
            Does not throw C++ exceptions.
        */
        CBooleanParameter( const CBooleanParameter& rhs );


        /*!
        \brief Destroys the CBooleanParameter object.
        Does not access the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual ~CBooleanParameter();


        /*!
        \brief Attaches a node retrieved from the provided node map.
        \param[in] pNodeMap The node map. The source of the parameter.
        \param[in] pName The name of the parameter to attach.
        \return Returns true if the node has been attached.
        \post
        <ul>
        <li>If \c pNodeMap or \c name is NULL, the parameter will be empty, see IsValid().
        <li>If the node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the provided node map has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            The call to GenApi::INodeMap::GetNode can throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::INodeMap* pNodeMap, const char* pName );


        /*!
        \brief Attaches a node retrieved from the provided node map.
        \param[in] nodeMap The node map. The source of the parameter.
        \param[in] pName The name of the parameter to attach.
        \return Returns true if the node has been attached.
        \post
        <ul>
        <li>If \c name is NULL the parameter will be empty, see IsValid().
        <li>If the node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the provided node map has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            The call to GenApi::INodeMap::GetNode can throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::INodeMap& nodeMap, const char* pName );


        /*!
        \brief Attaches a node, typically retrieved for a nodemap calling GetNode().
        \param[in] pNode The node to assign.
        \return Returns true if the node has been attached.
        \post
        <ul>
        <li>If the node does not match the parameter type, the parameter will be empty, see IsValid().
        <li>If the node does match the parameter type, it is attached and the parameter object can be used to access the node's functionality.
        <li>The parameter object must not be used to access the node's functionality if the source of the attached \c pNode has been destroyed. In this case, call Release() or attach a new node.
        </ul>
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::INode* pNode );


        /*!
        \brief Assigns a node of the same type to the parameter object.
        \param[in] pBoolean The node to assign.
        \return Returns true if the node has been attached.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::IBoolean* pBoolean );


        /*!
        \brief Assigns a CBooleanParameter object.
        \param[in] rhs The object to assign.
        \error
            Does not throw C++ exceptions.
        */
        CBooleanParameter& operator=( const CBooleanParameter& rhs );


        /*!
        \brief Returns true if the same nodes are attached or both parameters are empty.
        \param[in] rhs The object to compare to.
        \return Returns true if the same nodes are attached or both parameters are empty.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const CBooleanParameter& rhs ) const;


        /*!
        \brief Returns true if the attached node pointer is equal.
        \param[in] pNode The node to compare to.
        \return Returns true if the attached node pointer is equal.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const GENAPI_NAMESPACE::INode* pNode ) const;


        /*!
        \brief Returns true if the attached node pointer is equal.
        \param[in] pBoolean The node to compare to.
        \return Returns true if the attached node pointer is equal.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const GENAPI_NAMESPACE::IBoolean* pBoolean ) const;


        /*!
        \brief Releases the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual void Release();


        // Implements IValueEx
        virtual bool IsValid() const;


        // Implements GenApi::IBoolean
        virtual void SetValue( bool value, bool verify = true );

        // Implements GenApi::IBoolean
        virtual void operator=( bool value );

        // Implements GenApi::IBoolean
        virtual bool GetValue( bool verify = false, bool ignoreCache = false ) const;

        // Implements GenApi::IBoolean
        virtual bool operator()() const;


        // Implements IBooleanEx
        virtual bool TrySetValue( bool value );

        // Implements IEnumerationEx
        virtual bool GetValueOrDefault( bool defaultValue );

    protected:
        GENAPI_NAMESPACE::IBoolean* m_pFeature;
    };
}
#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BASLER_PYLON_CBOOLEANPARAMETER_H */