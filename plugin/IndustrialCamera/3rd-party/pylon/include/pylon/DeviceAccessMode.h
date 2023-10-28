//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2006-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief    Definition of Device Access Mode
*/

#ifndef INCLUDED_DEVICEACCESSMODE_H_6600916
#define INCLUDED_DEVICEACCESSMODE_H_6600916

#include <pylon/PylonBase.h>
#include <pylon/PylonVersionNumber.h>

#ifdef _MSC_VER
#   pragma pack(push, PYLON_PACKING)
#endif /* _MSC_VER */

#include <string>
#include <iomanip>

namespace Pylon
{
    // --------------------------------------------------------------------------
    // enum EDeviceAccessMode
    // --------------------------------------------------------------------------
    /// The available access modes when opening a camera object
    /*!
        \ingroup Pylon_TransportLayer
    */
    enum EDeviceAccessMode
    {
        Control = 0x1,     //!< access the control and status registers
        Stream = 0x3,      //!< access a streaming data channel
        Event = 0x4,       //!< access the event data channel
        Exclusive = 0x5,   //!< exclusive access to the device
        _NumModes
    };

    // --------------------------------------------------------------------------
    // class AccessModeSet
    // --------------------------------------------------------------------------
    /// Collection of access mode bits
    /*!
        Used for defining how a device is accessed.

        \par Low Level API:
        This set is used when a device is opened. The combination of
        different access modes specifies how the device is opened.
        Not all combinations may be allowed because the
        device implementations have certain restrictions.

        \code
        AccessModeSet a = Exclusive | Stream;
        if (a.test( Exclusive ))
        {
            // Exclusive implies Control access, so set it also
            a |= Control;
        }
        \endcode
        \sa The method of IDevice::Open() uses it to define a default value.
        \sa The global operator |( EDeviceAccessMode lhs, EDeviceAccessMode rhs ) allows to combine
        two modes to a set.
        \ingroup Pylon_TransportLayer
    */
    class PYLONBASE_API AccessModeSet
    {
    public:
        /// Default constructor creates an empty set.
        AccessModeSet( void );
        /// Converts an access mode into a set.
        AccessModeSet( EDeviceAccessMode am );
        /// Copy constructor
        AccessModeSet( const AccessModeSet& ams );
        ///
        explicit AccessModeSet( unsigned long l );
        // Destructor
        ~AccessModeSet();

        /*!
            \brief Sets the bit at position pos.
            \param pos Order position of the bit whose value is modified. Order positions are counted from the rightmost bit, which is order position 0.
            \ingroup Pylon_TransportLayer
            \return *this
        */
        AccessModeSet& set( size_t pos );


        /*!
            \brief Resets all bits to zero
            \return *this
            \ingroup Pylon_TransportLayer
        */
        AccessModeSet& reset();

        /*!
            \brief Returns whether any of the bits is set (i.e., whether at least one bit in the AccessModeSet is set to one).
            \returns true if any of the bits in the AccessModeSet is set (to one), and false otherwise.
            \ingroup Pylon_TransportLayer
        */
        bool any() const;

        /*!
            \brief Returns whether any of the bits is set (i.e., whether at least one bit in the AccessModeSet is set to one).
            \returns true if any of the bits in the AccessModeSet is set (to one), and false otherwise.
            \ingroup Pylon_TransportLayer
        */
        bool none() const;

        /*!
            \brief Returns whether the bit at position pos is set (i.e., whether it is one).
            \param pos Order position of the bit whose value is modified. Order positions are counted from the rightmost bit, which is order position 0.
            \returns true if the bit at position pos is set, and false if it is not set.
            \ingroup Pylon_TransportLayer
        */
        bool test( size_t pos ) const;

        /*!
            \brief Returns an unsigned long with the integer value that has the same bits set as the AccessModeSet.
            \returns Integer value with the same bit representation as the AccessModeSet object.
            \ingroup Pylon_TransportLayer
        */
        unsigned long to_ulong() const;

    private:
        unsigned long mBits;


    };

    // -------------------------------------------------------------------------
    // Access mode operators
    // -------------------------------------------------------------------------

    /*!
       \brief Creates a set containing lhs and rhs operands
       \param lhs left operand
       \param rhs right operand
       \return returns an AccessModeSet containing both operands
       \ingroup Pylon_TransportLayer
    */
    AccessModeSet PYLONBASE_API operator+( EDeviceAccessMode lhs, EDeviceAccessMode rhs );

    /*!
       \brief Creates a set containing lhs and rhs operands.
       \param lhs left operand
       \param rhs right operand
       \ingroup Pylon_TransportLayer
    */
    AccessModeSet PYLONBASE_API operator|( EDeviceAccessMode lhs, EDeviceAccessMode rhs );

    /*!
        \brief Adds the operand rhs to the set lhs
        \param lhs a set of bits.
        \param rhs the additional bit
        \ingroup Pylon_TransportLayer
    */
    AccessModeSet PYLONBASE_API operator+( const AccessModeSet& lhs, EDeviceAccessMode rhs );

    /*!
        \brief Adds the operand rhs to the set lhs
        \param lhs a set of bits.
        \param rhs the additional bit
        \ingroup Pylon_TransportLayer
    */
    AccessModeSet PYLONBASE_API operator|( const AccessModeSet& lhs, EDeviceAccessMode rhs );



    /*!
        \brief Check if the operand rhs is equal to lhs
        \param lhs a set of bits.
        \param rhs the additional set of bits.
        \ingroup Pylon_TransportLayer
    */
    bool PYLONBASE_API operator==( const AccessModeSet& lhs, const AccessModeSet& rhs );

    /*!
        \brief Check if the operand rhs is not equal to lhs
        \param lhs a set of bits.
        \param rhs the additional set of bits.
        \ingroup Pylon_TransportLayer
    */
    bool PYLONBASE_API operator!=( const AccessModeSet& lhs, const AccessModeSet& rhs );


    // -------------------------------------------------------------------------
    // STL output operators
    // -------------------------------------------------------------------------

    //! STL operator out
    //! \ingroup Pylon_TransportLayer
    inline std::ostream& operator <<( std::ostream& ostr, const Pylon::AccessModeSet& ams )
    {
        // use formatted output operator of std::string
        ostr << "0x"
            << std::setfill( '0' ) << std::setw( sizeof( unsigned long ) * 2 )
            << std::hex << ams.to_ulong();

        return ostr;
    }


#ifdef _MSC_VER
#   pragma pack(pop)
#endif /* _MSC_VER */
}

#endif /* INCLUDED_DEVICEACCESSMODE_H_6600916 */
