/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file
/// \brief Contains the NAT-type detection code for the client
///

#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_NatTypeDetectionClient == 1

#ifndef __NAT_TYPE_DETECTION_CLIENT_H
#define __NAT_TYPE_DETECTION_CLIENT_H

#include "DS_OrderedList.h"
#include "Export.h"
#include "NatTypeDetectionCommon.h"
#include "PacketPriority.h"
#include "PluginInterface2.h"
#include "RakNetTypes.h"
#include "RakString.h"
#include "SocketIncludes.h"

namespace RakNet {
/// Forward declarations
class RakPeerInterface;
struct Packet;

/// \brief Client code for NatTypeDetection
/// \details See NatTypeDetectionServer.h for algorithm
/// To use, just connect to the server, and call DetectNAT
/// You will get back ID_NAT_TYPE_DETECTION_RESULT with one of the enumerated values of NATTypeDetectionResult found in NATTypeDetectionCommon.h
/// See also http://www.jenkinssoftware.com/raknet/manual/natpunchthrough.html
/// \sa NatPunchthroughClient
/// \sa NatTypeDetectionServer
/// \ingroup NAT_TYPE_DETECTION_GROUP
class RAK_DLL_EXPORT NatTypeDetectionClient : public PluginInterface2,
                                              public RNS2EventHandler {
 public:
  // GetInstance() and DestroyInstance(instance*)
  STATIC_FACTORY_DECLARATIONS(NatTypeDetectionClient)

  // Constructor
  NatTypeDetectionClient();

  // Destructor
  ~NatTypeDetectionClient() override;

  /// Send the message to the server to detect the nat type
  /// Server must be running NatTypeDetectionServer
  /// We must already be connected to the server
  /// \param[in] serverAddress address of the server
  void DetectNATType(SystemAddress _serverAddress);

  /// \internal For plugin handling
  void Update() override;

  /// \internal For plugin handling
  PluginReceiveResult OnReceive(Packet* packet) override;

  void OnClosedConnection(
      const SystemAddress& systemAddress,
      RakNetGUID rakNetGUID,
      PI2_LostConnectionReason lostConnectionReason) override;
  void OnRakPeerShutdown() override;
  void OnDetach() override;

  void OnRNS2Recv(RNS2RecvStruct* recvStruct) override;
  void DeallocRNS2RecvStruct(
      RNS2RecvStruct* s,
      const char* file,
      unsigned int line) override;
  RNS2RecvStruct* AllocRNS2RecvStruct(const char* file, unsigned int line)
      override;

 protected:
  DataStructures::Queue<RNS2RecvStruct*> bufferedPackets;
  SimpleMutex bufferedPacketsMutex;

  RakNetSocket2* c2;
  //unsigned short c2Port;
  void Shutdown();
  void OnCompletion(NATTypeDetectionResult result);
  bool IsInProgress() const;

  void OnTestPortRestricted(Packet* packet);
  SystemAddress serverAddress;
};

} // namespace RakNet

#endif

#endif // _RAKNET_SUPPORT_*
