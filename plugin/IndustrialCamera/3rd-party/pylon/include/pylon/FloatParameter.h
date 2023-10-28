//------------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2018-2021 Basler AG
//  http://www.baslerweb.com
//------------------------------------------------------------------------------
/*!
\file
\brief Contains the class CFloatParameter used to simplify access to %GenApi parameters.
*/

#ifndef INCLUDED_BASLER_PYLON_CFLOATPARAMETER_H
#define INCLUDED_BASLER_PYLON_CFLOATPARAMETER_H

#pragma once

#include <pylon/PylonBase.h>
#include <GenApi/IFloat.h>
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
    /// Lists possible float value correction strategies.
    enum EFloatValueCorrection
    {
        /// No correction is applied. If the value isn't valid for the parameter, an exception is thrown.
        FloatValueCorrection_None = 0,
        /// If the value is not in the valid range, the value is corrected to the valid range.
        FloatValueCorrection_ClipToRange = 3
    };

    class CIntegerParameter;
    /*!
    \brief Extends the GenApi::IFloat interface with convenience methods.
    */
    interface IFloatEx : virtual public GENAPI_NAMESPACE::IFloat, virtual public IValueEx
    {
        using GENAPI_NAMESPACE::IFloat::operator=;

        using GENAPI_NAMESPACE::IFloat::SetValue;

        /*!
        \brief Sets the value of the parameter if the parameter is writable.
        \brief The value must be in the valid range and the increment must be correct.
        \return Returns false if the parameter is not writable.
        \param[in] value The value to set.
        <para>If the float parameter has an increment, the increment is automatically corrected.
        \pre
        <ul>
        <li>The passed value must be &gt;= GenApi::IFloat::GetMin().
        <li>The passed value must be &lt;= GenApi::IFloat::GetMax().
        </ul>
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the preconditions are not met or if writing the value fails.
        */
        virtual bool TrySetValue( double value ) = 0;


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
        virtual double GetValueOrDefault( double defaultValue ) = 0;


        /*!
        \brief Sets the value of the parameter if the parameter is writable and readable.
        \brief The value is automatically corrected if needed.
        \return Returns false if the parameter is not readable or not writable.
        \param[in] value The value to set.
        \param[in] correction The correction method.
        \note Calls TrySetValue(GenApi::IFloatParameter, double) if \c correction equals FloatValueCorrection_None.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual bool TrySetValue( double value, EFloatValueCorrection correction ) = 0;


        /*!
        \brief Sets the value of the parameter. The value is automatically corrected if needed.
        \param[in] value The value to set.
        \param[in] correction The correction method.
        \pre
        <ul>
        <li>The parameter must be writable.
        <li>The parameter must be readable.
        </ul>
        \note Calls GenApi::IFloatParameter::SetValue(double) if \c correction equals FloatValueCorrection_None.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if the preconditions are not met or if writing the value fails.
        */
        virtual void SetValue( double value, EFloatValueCorrection correction ) = 0;


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
        \param[in] percentOfRange The percentage of the range to be used in the calculation.
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
        \return Returns true if the value has been set.
        \param[in] percentOfRange The percentage of the range used in the calculation. Valid values are in the range of 0 to 100.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if writing the value fails.
        */
        virtual bool TrySetValuePercentOfRange( double percentOfRange ) = 0;


        /*!
        \brief Sets the parameter value to the maximum possible value.
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
        \brief Sets the parameter value to the minimum possible value.
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
        \brief Sets the parameter value to the maximum possible value if the parameter is readable and writable.
        \return Returns true if the maximum value has been set.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if reading or writing fails.
        */
        virtual bool TrySetToMaximum() = 0;


        /*!
        \brief Sets the parameter value to the minimum possible value if the parameter is readable and writable.
        \return Returns true if the minimum value has been set.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions if reading or writing fails.
        */
        virtual bool TrySetToMinimum() = 0;


        /*!
        \brief Gets the alternative integer representation of the float parameter, if available.
        The alternative integer representation is typically used if a parameter is represented as a
        float value in the node map, but as an integer register in the camera device.
        \param[out] parameter The integer representation returned. The returned value will be empty if no alternative representation is available.
        \threading
             The method accesses the parameter multiple times. These accesses are not synchronized by a lock.
        \error
             Can throw exceptions.
        */
        virtual void GetAlternativeIntegerRepresentation( CIntegerParameter& parameter ) = 0;
    };


    /*!
    \brief CFloatParameter class used to simplify access to %GenApi parameters.
    */
    class PYLONBASE_API CFloatParameter : public IFloatEx, public CParameter
    {
    public:
        /*!
        \brief Creates an empty CFloatParameter object.
        \error
            Does not throw C++ exceptions.
        */
        CFloatParameter();


        /*!
        \brief Creates a CFloatParameter object and attaches it to a node, typically retrieved for a nodemap calling GetNode().
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
        explicit CFloatParameter( GENAPI_NAMESPACE::INode* pNode );


        /*!
        \brief Creates a CFloatParameter object and attaches it to a node of a matching type.
        \param[in] pFloat The node to attach.
        \post
            The parameter object must not be used to access the node's functionality if the source of the attached \c pFloat has been destroyed. In this case, call Release() or attach a new node.
        \error
            Does not throw C++ exceptions.
        */
        explicit CFloatParameter( GENAPI_NAMESPACE::IFloat* pFloat );


        /*!
        \brief Creates a CFloatParameter object and attaches it to a node retrieved from the provided node map.
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
        CFloatParameter( GENAPI_NAMESPACE::INodeMap* pNodeMap, const char* pName );


        /*!
        \brief Creates a CFloatParameter object and attaches it to a node retrieved from the provided node map.
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
        CFloatParameter( GENAPI_NAMESPACE::INodeMap& nodeMap, const char* pName );


        /*!
        \brief Copies a CFloatParameter object.
        \param[in] rhs The object to copy.
        \error
            Does not throw C++ exceptions.
        */
        CFloatParameter( const CFloatParameter& rhs );


        /*!
        \brief Destroys the CFloatParameter object.
        Does not access the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual ~CFloatParameter();


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
        \param[in] pFloat The node to assign.
        \return Returns true if the node has been attached.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Attach( GENAPI_NAMESPACE::IFloat* pFloat );


        /*!
        \brief Assigns a CFloatParameter object.
        \param[in] rhs The object to assign.
        \error
            Does not throw C++ exceptions.
        */
        CFloatParameter& operator=( const CFloatParameter& rhs );


        /*!
        \brief Returns true if the same nodes are attached or both parameters are empty.
        \param[in] rhs The object to compare to.
        \return Returns true if the same nodes are attached or both parameters are empty.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const CFloatParameter& rhs ) const;


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
        \param[in] pFloat The node to compare to.
        \return Returns true if the attached node pointer is equal.
        \error
            Does not throw C++ exceptions.
        */
        virtual bool Equals( const GENAPI_NAMESPACE::IFloat* pFloat ) const;


        /*!
        \brief Releases the attached node.
        \error
            Does not throw C++ exceptions.
        */
        virtual void Release();


        // Implements IValueEx
        virtual bool IsValid() const;


        // Implements GenApi::IFloat
        virtual void SetValue( double value, bool verify = true );

        // Implements GenApi::IFloat
        virtual GENAPI_NAMESPACE::IFloat& operator=( double value );

        // Implements GenApi::IFloat
        virtual double GetValue( bool verify = false, bool ignoreCache = false );

        // Implements GenApi::IFloat
        virtual double operator()();

        // Implements GenApi::IFloat
        virtual double operator*();

        // Implements GenApi::IFloat
        virtual double GetMin();

        // Implements GenApi::IFloat
        virtual double GetMax();

        // Implements GenApi::IFloat
        virtual bool HasInc();

        // Implements GenApi::IFloat
        virtual GENAPI_NAMESPACE::EIncMode GetIncMode();

        // Implements GenApi::IFloat
        virtual double GetInc();

        // Implements GenApi::IFloat
        virtual GENAPI_NAMESPACE::double_autovector_t GetListOfValidValues( bool bounded = true );

        // Implements GenApi::IFloat
        virtual GENAPI_NAMESPACE::ERepresentation GetRepresentation();

        // Implements GenApi::IFloat
        virtual GENICAM_NAMESPACE::gcstring GetUnit() const;

        // Implements GenApi::IFloat
        virtual GENAPI_NAMESPACE::EDisplayNotation GetDisplayNotation() const;

        // Implements GenApi::IFloat
        virtual int64_t GetDisplayPrecision() const;

        // Implements GenApi::IFloat
        virtual void ImposeMin( double value );

        // Implements GenApi::IFloat
        virtual void ImposeMax( double value );


        // Implements IFloatEx
        virtual bool TrySetValue( double value );

        // Implements IFloatEx
        virtual double GetValueOrDefault( double defaultValue );

        // Implements IFloatEx
        virtual bool TrySetValue( double value, EFloatValueCorrection correction );

        // Implements IFloatEx
        virtual void SetValue( double value, EFloatValueCorrection correction );

        // Implements IFloatEx
        virtual double GetValuePercentOfRange();

        // Implements IFloatEx
        virtual void SetValuePercentOfRange( double percentOfRange );

        // Implements IFloatEx
        virtual bool TrySetValuePercentOfRange( double percentOfRange );

        // Implements IFloatEx
        virtual void SetToMaximum();

        // Implements IFloatEx
        virtual void SetToMinimum();

        // Implements IFloatEx
        virtual bool TrySetToMaximum();

        // Implements IFloatEx
        virtual bool TrySetToMinimum();

        // Implements IFloatEx
        virtual void GetAlternativeIntegerRepresentation( CIntegerParameter& parameter );

    protected:
        GENAPI_NAMESPACE::IFloat* m_pFeature;
    };
}
#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */

#endif /* INCLUDED_BASLER_PYLON_CFLOATPARAMETER_H */