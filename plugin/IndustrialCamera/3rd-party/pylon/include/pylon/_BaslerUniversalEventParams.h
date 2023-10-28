//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2019-2021 Basler AG
//  http://www.baslerweb.com
//-----------------------------------------------------------------------------

/*!
\file
\brief A parameter class containing all parameters as members that are available for pylon event grabbers

The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------

#ifndef BASLER_PYLON_UNIVERSALEVENTPARAMS_H
#define BASLER_PYLON_UNIVERSALEVENTPARAMS_H

#pragma once

// common parameter types
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>

namespace Basler_UniversalEventParams
{
    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    //! Valid values for Status
    enum StatusEnums
    {
        Status_Closed,  //!< The low level event grabber is closed - Applies to: GigE
        Status_Open  //!< The low level event grabber is open - Applies to: GigE
    };


    
    
    //**************************************************************************************************
    // Parameter class CUniversalEventParams_Params_v6_2_0
    //**************************************************************************************************
    

    /*!
    \brief A parameter class containing all parameters as members that are available for pylon event grabbers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class PYLONBASE_API CUniversalEventParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
    // If you want to show the following methods in the help file
    // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
    //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalEventParams_Params_v6_2_0( void );

        //! Destructor
        ~CUniversalEventParams_Params_v6_2_0( void );

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* );

    //! \endcond

    private:
        class CUniversalEventParams_Params_v6_2_0_Data;
        CUniversalEventParams_Params_v6_2_0_Data* m_pCUniversalEventParams_Params_v6_2_0_Data;


    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        //! \name Categories: Root
        //@{
        /*!
            \brief Number of buffers to be used - Applies to: GigE and USB

            Number of Buffers that are going to be used receiving events. .

            Visibility: Expert

        */
        Pylon::IIntegerEx& NumBuffer;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of USB request blocks (URBs) to be enqueued simultaneously - Applies to: USB


            Visibility: Guru

        */
        Pylon::IIntegerEx& NumMaxQueuedUrbs;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Maximum number of retries - Applies to: GigE

            Number retry attempts by the camera to get an acknowledge for a sent event message.

            Visibility: Expert

        */
        Pylon::IIntegerEx& RetryCount;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Count of processed events with an error status - Applies to: USB


            Visibility: Expert

        */
        Pylon::IIntegerEx& Statistic_Failed_Event_Count;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Status code of the last failed event buffer - Applies to: USB


            Visibility: Expert

        */
        Pylon::IIntegerEx& Statistic_Last_Failed_Event_Buffer_Status;

        //@}


        //! \name Categories: Statistic
        //@{
        /*!
            \brief Total count of processed events - Applies to: USB


            Visibility: Expert

        */
        Pylon::IIntegerEx& Statistic_Total_Event_Count;

        //@}


        //! \name Categories: Debug
        //@{
        /*!
            \brief For internal use only - Applies to: GigE


            Visibility: Guru

        */
        Pylon::IEnumParameterT<StatusEnums>& Status;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Acknowledge timeout in milliseconds - Applies to: GigE

            Time to wait by the camera if an acknowledge request is configured (RetryCount != 0) to wait until the acknowledge arrives before resending the event message on its own.

            Visibility: Expert

        */
        Pylon::IIntegerEx& Timeout;

        //@}


        //! \name Categories: Root
        //@{
        /*!
            \brief Priority of the thread that handles USB requests from the stream interface - Applies to: USB


            Visibility: Guru

        */
        Pylon::IIntegerEx& TransferLoopThreadPriority;

        //@}


    private:
    //! \cond HIDE_CLASS_METHODS

        //! not implemented copy constructor
        CUniversalEventParams_Params_v6_2_0(CUniversalEventParams_Params_v6_2_0&);

        //! not implemented assignment operator
        CUniversalEventParams_Params_v6_2_0& operator=(CUniversalEventParams_Params_v6_2_0&);

    //! \endcond
    };


    /*!
    \brief A parameter class containing all parameters as members that are available for pylon event grabbers

    The parameter class is used by the \c Pylon::CBaslerUniversalInstantCamera class.
    The \ref sample_ParametrizeCamera_NativeParameterAccess code sample shows how to access camera parameters via the \c Pylon::CBaslerUniversalInstantCamera class.
    */
    class CUniversalEventParams_Params : public CUniversalEventParams_Params_v6_2_0
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
        //! Constructor
        CUniversalEventParams_Params( void )
        {
        }

        //! Destructor
        ~CUniversalEventParams_Params( void )
        {
        }

        //! Initializes the references
        void _Initialize( GENAPI_NAMESPACE::INodeMap* pNodeMap )
        {
            CUniversalEventParams_Params_v6_2_0::_Initialize( pNodeMap );
        }
        //! \endcond
    };
} // namespace Basler_UniversalEventParams

#endif // BASLER_PYLON_UNIVERSALEVENTPARAMS_H
