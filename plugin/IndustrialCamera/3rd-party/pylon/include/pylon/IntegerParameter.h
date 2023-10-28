//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2018-2021 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains the class CIntegerParameter used to simplify access to %GenApi parameters.
*/

#ifndef INCLUDED_BASLER_PYLON_CINTEGERPARAMETER_H
#define INCLUDED_BASLER_PYLON_CINTEGERPARAMETER_H

#pragma once

#include <pylon/PylonBase.h>
#include <GenApi/IInteger.h>
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
    /// Lists possible integer value corrections.
    enum EIntegerValueCorrection
    {
        /// No correction is applied. If the value isn't valid for the parameter, an exception is thrown.
        IntegerValueCorrection_None = 0,
        /// The value is corrected by rounding up to the nearest valid value.
        /// If the value is lower/higher than the minimum/maximum in the range of valid values, the value is corrected to the minimum/maximum.
        IntegerValueCorrection_Up = 1,
        /// The value is corrected by rounding down to the nearest valid value.
        /// If the value is lower/higher than the minimum/maximum in the range of valid values, the value is corrected to the minimum/maximum.
        IntegerValueCorrection_Down = 2,
        /// The value is corrected by rounding up or down to the nearest valid value.
        /// If the correction in each direction is equal, the value is corrected by rounding up to the nearest valid value.
        /// If the value is lower/higher than the minimum/maximum in the range of valid values, the value is corrected to the minimum/maximum.
        IntegerValueCorrection_Nearest = 3
    };


    /*!
    \brief Extends the GenApi::IInteger interface with convenience methods.
    */
    interface IIntegerEx : virtual public GENAPI_NAMESPACE::IInteger, virtual public IValueEx
    {
        using GENAPI_NAMESPACE::IInteger::operator=;

        using GENAPI_NAMESPACE::IInteger::SetValue;

        /*!
        \brief Sets the value of the parameter if the parameter is writable.
        \brief The value must be in the valid range and the increment must be correct.
        \return Returns false if the parameter is not writable.
        \param[in] value The value to set.
        \pre
        <ul>
        <li>The passed value must be &gt;= GenApi::IInteger::GetMin().
        <li>The passed value must be &lt;= GenApi::IInteger::GetMax().
        <li>The passed value must be aligned to the increment returned by GenApi::IInteger::GetInc().
        </ul>
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the preconditions are not met or if writing the value fails.
        */
        virtual bool TrySetValue( int64_t value ) = 0;


        /*!
        \brief Gets the value of the parameter if the parameter is readable.
        \brief Otherwise returns the default value.
        \return Returns the parameter value if the parameter is readable. Otherwise returns the default value.
        \param[in] defaultValue The default value returned if the parameter is not readable.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exception if reading the value fails.
        */
        virtual int64_t GetValueOrDefault( int64_t defaultValue ) = 0;


        /*!
        \brief Sets the value of the parameter if the parameter is writable and readable.
        \brief The value is automatically corrected if needed.
        \return Returns false if the parameter is not readable or not writable.
        \param[in] value The value to set.
        \param[in] correction The correction method.
        \note Calls TrySetValue(GenApi::IInteger*, int64_t) if \c correction equals IntegerValueCorrection_None.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual bool TrySetValue( int64_t value, EIntegerValueCorrection correction ) = 0;


        /*!
        \brief Sets the value of the parameter. The value is automatically corrected if needed.
        \param[in] value The value to set.
        \param[in] correction The correction method.
        \pre
        <ul>
        <li>The parameter must be writable.
        <li>The parameter must be readable.
        </ul>
        \note Calls GenApi::IInteger::SetValue(int64_t) if \c correction equals IntegerValueCorrection_None.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the preconditions are not met or if writing the value fails.
        */
        virtual void SetValue( int64_t value, EIntegerValueCorrection correction ) = 0;


        /*!
        \brief Gets the value of the parameter in percent of its value range (from minimum to maximum).
        \return Returns the parameter value in percent of its value range. Returns 100 if minimum equals maximum.
        \pre The parameter must be readable.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual double GetValuePercentOfRange() = 0;


        /*!
        \brief Sets the value of the parameter to a value within its range, using this formula (simplified): ((max - min) * (percentOfRange / 100.0)) + min.
        \brief The value is always corrected to the nearest valid value.
        \param[in] percentOfRange The percentage of the range to be used in the calculation.
        <remarks><para>The parameter must be writable.
        \pre
        <ul>
        <li>The parameter must be writable.
        <li>The parameter must be readable.
        </ul>
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual void SetValuePercentOfRange( double percentOfRange ) = 0;


        /*!
        \brief If the parameter is writable and readable, sets the value of the parameter to a value within its range, using this formula (simplified): ((max - min) * (percentOfRange / 100.0)) + min.
        \brief The value is always corrected to the nearest valid value.
        \return Returns true if the a value has been set.
        \param[in] percentOfRange The percentage of the range to be used in the calculation.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual bool TrySetValuePercentOfRange( double percentOfRange ) = 0;


        /*!
        \brief Sets the value of the parameter to the maximum possible value.
        \pre
        <ul>
        <li>The parameter must be writable.
        <li>The parameter must be readable.
        </ul>
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the parameter is not writable, not readable, or if reading or writing fails.
        */
        virtual void SetToMaximum() = 0;


        /*!
        \brief Sets the value of the parameter to the minimum possible value.
        \pre
        <ul>
        <li>The parameter must be writable.
        <li>The parameter must be readable.
        </ul>
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the parameter is not writable, not readable, or if reading or writing fails.
        */
        virtual void SetToMinimum() = 0;


        /*!
        \brief Sets the value of the parameter to the maximum possible value if the parameter is readable and writable.
        \return Returns true if the maximum value has been set.

        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if reading or writing fails.
        */
        virtual bool TrySetToMaximum() = 0;


        /*!
        \brief Sets the value of the parameter to the minimum possible value if the parameter is readable and writable.
        \return Returns true if the minimum value has been set.

        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if reading or writing fails.
        */
        virtual bool TrySetToMinimum() = 0;
    };


    /*!
    \brief CIntegerParameter class used to simplify access to %GenApi parameters.
    */
    class PYLONBASE_API CIntegerParameter : public IIntegerEx, public CParameter
    {
    public:
        /*!
        \brief Creates an empty CIntegerParameter object.
        \error
            Does not throw C++ exceptions.
        */
        CIntegerParameter();


        /*!
        \brief Creates a CIntegerParameter object and attaches it to a node, typically retrieved for a nodemap calling GetNode().
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
        explicit CIntegerParameter( GENAPI_NAMESPACE::INode* pNode );


        /*!
        \brief Creates a CIntegerParameter object and attaches it to a node of a matching type.
        \param[in] pInteger The node to attach.
        \post
            The parameter object must not be used to access the node's functionality if the source of the attached \c pInteger has been destroyed. In this case, call Release() or attach a new node.
        \error
            Does not throw C++ exceptions.
        */
        explicit CIntegerParameter( GENAPI_NAMESPACE::IInteger* pInteger );


        /*!
        \brief Creates a CIntegerParameter object and attaches it to a node retrieved from the provided node map.
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
        CIntegerParameter( GENAPI_NAMESPACE::INodeMap* pNodeMap, const char* pName );


        /*!
        \brief Creates a CIntegerParameter object and attaches it to a node retrieved from the provided node map.
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
        CIntegerParameter( GENAPI_NAMESPACE::INodeMap& nodeMap, const char* pName );


        /*!
        \brief Copies a CIntegerParameter object.
        \param[in] rhs The object to copy.
        \error
            Does not throw C++ exceptions.
        */
        CIntegerParameter( const CIntegerParameter& rhs );


        /*!
        \brief Destroys the CIntegerParameter object.
        Does not access the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual ~CIntegerParameter();


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
        \param[in] pInteger The node to assign.
        \return Returns true if the node has been attached.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::IInteger* pInteger );


        /*!
        \brief Assigns a CIntegerParameter object.
        \param[in] rhs The object to assign.
        \error
            Does not throw C++ exceptions.
        */
        CIntegerParameter& operator=( const CIntegerParameter& rhs );


        /*!
        \brief Returns true if the same nodes are attached or both parameters are empty.
        \param[in] rhs The object to compare to.
        \return Returns true if the same nodes are attached or both parameters are empty.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const CIntegerParameter& rhs ) const;


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
        \param[in] pInteger The node to compare to.
        \return Returns true if the attached node pointer is equal.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const GENAPI_NAMESPACE::IInteger* pInteger ) const;


        /*!
        \brief Releases the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual void Release();


        // Implements IValueEx
        virtual bool IsValid() const;


        // Implements GenApi::IInteger
        virtual void SetValue( int64_t value, bool verify = true );

        // Implements GenApi::IInteger
        virtual GENAPI_NAMESPACE::IInteger& operator=( int64_t value );

        // Implements GenApi::IInteger
        virtual int64_t GetValue( bool verify = false, bool ignoreCache = false );

        // Implements GenApi::IInteger
        virtual int64_t operator()();

        // Implements GenApi::IInteger
        virtual int64_t operator*();

        // Implements GenApi::IInteger
        virtual int64_t GetMin();

        // Implements GenApi::IInteger
        virtual int64_t GetMax();

        // Implements GenApi::IInteger
        virtual GENAPI_NAMESPACE::EIncMode GetIncMode();

        // Implements GenApi::IInteger
        virtual int64_t GetInc();

        // Implements GenApi::IInteger
        virtual GENAPI_NAMESPACE::int64_autovector_t GetListOfValidValues( bool bounded = true );

        // Implements GenApi::IInteger
        virtual GENAPI_NAMESPACE::ERepresentation GetRepresentation();

        // Implements GenApi::IInteger
        virtual GENICAM_NAMESPACE::gcstring GetUnit();

        // Implements GenApi::IInteger
        virtual void ImposeMin( int64_t value );

        // Implements GenApi::IInteger
        virtual void ImposeMax( int64_t value );


        // Implements IIntegerEx
        virtual bool TrySetValue( int64_t value );

        // Implements IIntegerEx
        virtual int64_t GetValueOrDefault( int64_t defaultValue );

        // Implements IIntegerEx
        virtual bool TrySetValue( int64_t value, EIntegerValueCorrection correction );

        // Implements IIntegerEx
        virtual void SetValue( int64_t value, EIntegerValueCorrection correction );

        // Implements IIntegerEx
        virtual double GetValuePercentOfRange();

        // Implements IIntegerEx
        virtual void SetValuePercentOfRange( double percentOfRange );

        // Implements IIntegerEx
        virtual bool TrySetValuePercentOfRange( double percentOfRange );

        // Implements IIntegerEx
        virtual void SetToMaximum();

        // Implements IIntegerEx
        virtual void SetToMinimum();

        // Implements IIntegerEx
        virtual bool TrySetToMaximum();

        // Implements IIntegerEx
        virtual bool TrySetToMinimum();

    protected:
        GENAPI_NAMESPACE::IInteger* m_pFeature;
    };
}
#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BASLER_PYLON_CINTEGERPARAMETER_H */