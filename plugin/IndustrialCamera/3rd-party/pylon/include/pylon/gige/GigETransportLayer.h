//-----------------------------------------------------------------------------
//  Basler pylon SDK
//  Copyright (c) 2008-2021 Basler AG
//  http://www.baslerweb.com
//  Author:  Thomas Koeller, Hartmut Nebelung
//-----------------------------------------------------------------------------
/*!
\file
\brief Definition of the GigE-specific transport layer interface extension
*/

#ifndef TRANSPORTLAYER_GIGE_H
#define TRANSPORTLAYER_GIGE_H

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include <pylon/TransportLayer.h>
#include "PylonGigE.h"

namespace Pylon
{
    /*!
    \ingroup Pylon_TransportLayer
    \brief Lists possible status codes returned by IGigETransportLayer::IssueActionCommand or IGigETransportLayer::IssueScheduledActionCommand.
    */
    enum EGigEActionCommandStatus
    {
        /**
        \brief The device acknowledged the command.
        */
        GigEActionCommandStatus_Ok = 0,

        /**
        \brief The device is not synchronized to a master clock to be used as time reference.
        Typically used when scheduled action commands cannot be scheduled for
        a future time since the reference time coming from IEEE 1588 is not locked.
        The action command has been ignored by the device.
        */
        GigEActionCommandStatus_NoRefTime = 0xE1018013,

        /**
        \brief Returned when the scheduled action commands queue is full and the device cannot accept the additional request.
        The action command has been discarded by the device.
        */
        GigEActionCommandStatus_Overflow = 0xE1018015,

        /**
        \brief The requested scheduled action command was requested at a point in time that is in the past.
        If the time tag of the scheduled action command is in the past (relative to the device timestamp), and if it is a valid action
        command, then the device will execute this action command immediately and return \c GigEActionCommandStatus_ActionLate.
        This status code is used as an indicator to the application requesting the action command that a mis-synchronization might have
        occurred.
        */
        GigEActionCommandStatus_ActionLate = 0xE1018016
    };


    /*!
    \ingroup Pylon_TransportLayer
    \brief Optional result structure of IGigETransportLayer::IssueActionCommand and IGigETransportLayer::IssueScheduledActionCommand.
    */
    struct GigEActionCommandResult
    {
        /// IP address of the device.
        char DeviceAddress[12 + 3 + 1];

        /// GigE Vision status code returned by the device. See Pylon::EGigEActionCommandStatus for more information.
        int32_t Status;
    };


    /*!
    \ingroup Pylon_TransportLayer
    \interface IGigETransportLayer
    \brief Extends the ITransportLayer interface by GigE Vision specific
           functionality.
    */
    interface PUBLIC_INTERFACE IGigETransportLayer : public ITransportLayer
    {
        //! \brief Enumerates all available Basler GigE Vision devices
        /*!
            In contrast to the ITransportLayer::EnumerateDevices method,
            devices having a subnet configured that is different from the subnet of the
            application will be listed.

            All Basler GigE Vision devices will be listed, including the Basler blaze,
            which is usually not considered by the GigE transport layer.
         */
        virtual int EnumerateAllDevices( DeviceInfoList_t&, bool addToList = false ) = 0;

        //! \brief "Force" a static IP address configuration in a device identified by its MAC Address
        /**
            This applies to all Basler GigE Vision devices, including the Basler blaze, which isn't
            usually considered by the GigE transport layer.

        \note When calling this function, there must be no opened camera object for
               the device to be reconfigured!

        \param MacAddress MAC address as a string, no delimiters are used. e.g., 003053061a58
        \param IpAddress Temporary IP address, "dot notation", e.g., 192.168.1.2
        \param SubnetMask Temporary SubnetMask, "dot notation", e.g. 255.255.255.0
        \param DefaultGateway Temporary DefaultGateway, "dot notation", e.g., 192.168.1.1
        */
        virtual void ForceIp( const String_t& MacAddress,
                              const String_t& IpAddress,
                              const String_t& SubnetMask,
                              const String_t& DefaultGateway ) = 0;

        //! \brief Let a device restart the IP configuration cycle
        /**
        \note This function fails when the device is open, i.e., a control channel is established
        \param MacAddress MAC address as a string, no delimiters are used, e.g., 003053061a58
        */
        virtual void RestartIpConfiguration( const String_t& MacAddress ) = 0;

        //! \brief Announce that a remote device is going to be used
        /*!
            This applies to all Basler GigE Vision devices, including the Basler blaze, which isn't
            usually considered by the GigE transport layer.

            \note This device must be reachable, a route is configured.
            \param IpAddress address of device in "dot notation"
            \param pInfo This optional parameter holds the full device info if found
        */
        virtual bool AnnounceRemoteDevice( const String_t& IpAddress, CDeviceInfo* pInfo = NULL ) = 0;
        //! \brief Stop using remote device.
        /*! \param IpAddress address of device in "dot notation" */
        virtual bool RenounceRemoteDevice( const String_t& IpAddress ) = 0;

        //! \brief Broadcast a new IP configuration
        /**
         All Basler GigE Vision devices can be configured, including the Basler blaze, which
         isn't usually considered by the GigE transport layer.
         When configuring a blaze camera, some options may not be supported. Please check
         the camera documentation for more information.

        \param MacAddress MAC address as a string, no delimiters are used. e.g., 003053061a58
        \param EnablePersistentIp If true, a persistent Ip address will be set
        \param EnableDhcp If true, DHCP is enabled
        \param IpAddress Device's new IP address, "dot notation", e.g., 192.168.1.2
        \param SubnetMask Device's new SubnetMask, "dot notation", e.g. 255.255.255.0
        \param DefaultGateway Device's new DefaultGateway, "dot notation", e.g., 192.168.1.1
        \param UserdefinedName Device's new UserdefinedName, maximal 16 character
        \return true if configuration was successfully written
        */
        virtual bool BroadcastIpConfiguration( const String_t& MacAddress,
                                               bool EnablePersistentIp,
                                               bool EnableDhcp,
                                               const String_t& IpAddress,
                                               const String_t& SubnetMask,
                                               const String_t& DefaultGateway,
                                               const String_t& UserdefinedName ) = 0;


        //! \brief Issue a broadcast action command.
        /**
        \param[in] deviceKey   The device key addresses devices managed by an application.
                               The device key is only known to the application controlling its camera devices
                               and it ensures that only this application can trigger the camera devices.
                               Therefore the device key cannot be read from a device.
                               An exact match of the send \c deviceKey and the device key stored in a device
                               is required for executing an action.

        \param[in] groupKey    The group key is used to create groups of devices or actions.
                               An exact match of the send \c groupKey and the group key stored in a device
                               for an action is required for executing an action.

        \param[in] groupMask   The groupMask is a bit mask that allows to send an action to a subgroup
                               of the devices addressed by the \c deviceKey \c groupKey pair.
                               The result of a bitwise AND operation of \c groupMask and the group mask
                               stored in a device for an action must be non-zero for executing an action.

        \param[in] broadcastAddress   BroadcastAddress in dot notation where the command will be broadcast to,
                                      e.g. 255.255.255.255 (all adapters, default),
                                      192.168.1.255 (all devices in a single subnet 192.168.1.xxx),
                                      192.168.1.38 (single device).
                                      See the note below.

        \param[in] timeoutMs   Optional: Time in milliseconds the call is waiting for acknowledges of the addressed devices.
                                Waiting for acknowledges is stopped if \c pNumResults have been received.
                                This parameter can be 0 if a check of action command results is not required.

        \param[in,out] pNumResults      Optional: The number of results in the \c results array.
                                        The value passed should be equal to the expected number of devices that acknowledge the command.
                                        Returns the number of received results.
                                        This parameter is ignored if \c timeoutMs is 0.
                                        Thus this parameter can be NULL if \c timeoutMs is 0.

        \param[out] results             Optional: An Array with \c *pNumResults elements to hold the action command result status.
                                        The buffer is filled beginning from the start. Remaining results are
                                        not changed if less results are received than result items available.
                                        This parameter is ignored if \c timeoutMs is 0.
                                        Thus this parameter can be NULL if \c timeoutMs is 0.


        \return Returns true if *pNumResults have been received and the \c Status of all results is \c GigEActionCommandStatus_Ok.
                Returns true if no results have been requested.

        The action command feature lets you trigger actions in multiple devices (e.g. cameras) at roughly
        the same time or at a defined point in time (scheduled action command) by using a single broadcast protocol message (without extra cabling). Action
        commands are used in cameras in the same way as for example the digital input lines.

        \note The request is sent via all existing network adapters. If a network adapter has more than one IP address, the request is sent separately for each address. 
        This is not executed simultaneously but consecutively, IP address by IP address. That's why additional latency is added to the execution time.
        Directed broadcasts (192.168.1.255) or unicasts (192.168.1.38) are only sent if the request subnet matches the subnet of the IP address, i.e., if no gateway or routing are required.        

        See \ref sample_Grab_UsingActionCommand and Pylon::CActionTriggerConfiguration for more information.

        \pre
        <ul>
        <li> IP4 addresses must be used.
        <li> \c groupMask must not be 0.
        <li> \c pNumResult, \c *pNumResult and \c results must not be 0 if a \c timeoutMs value other than 0 is passed.
        </ul>

        \error
            Throws an exception if the preconditions are not met. Throws C++ exceptions.

        \threading
            The method is thread-safe.
        */
        virtual bool IssueActionCommand( uint32_t deviceKey,
                                         uint32_t groupKey,
                                         uint32_t groupMask,
                                         const String_t &broadcastAddress = "255.255.255.255",
                                         uint32_t timeoutMs = 0,
                                         uint32_t *pNumResults = 0,
                                         GigEActionCommandResult results[] = NULL ) = 0;


        //! \brief Issue a scheduled action command via broadcast.
        /**
        \copydetails IGigETransportLayer::IssueActionCommand

        \param[in] actionTimeNs   Time in nanoseconds when the action is to be executed.
                                   The actual value depends on the used master clock.
                                   A master clock value can be obtained for instance for a set of
                                   synchronized camera devices by reading the timestamp value
                                   (GevTimestampValue) after latching the timestamp value
                                   (GevTimestampControlLatch) from one camera device of the set

        \pre \c actionTimeNs must be smaller than or equal INT64_MAX.
        */
        virtual bool IssueScheduledActionCommand( uint32_t deviceKey,
                                                  uint32_t groupKey,
                                                  uint32_t groupMask,
                                                  uint64_t actionTimeNs,
                                                  const String_t &broadcastAddress = "255.255.255.255",
                                                  uint32_t timeoutMs = 0,
                                                  uint32_t *pNumResults = 0,
                                                  GigEActionCommandResult results[] = NULL
        ) = 0;

    };
} // namespace Pylon

#endif // TRANSPORTLAYER_GIGE_H
