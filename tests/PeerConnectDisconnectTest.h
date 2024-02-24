/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#pragma once

#include "TestInterface.h"

#include "RakString.h"

#include "BitStream.h"
#include "CommonFunctions.h"
#include "DebugTools.h"
#include "GetTime.h"
#include "MessageIdentifiers.h"
#include "RakNetTime.h"
#include "RakPeer.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"

using namespace RakNet;
class PeerConnectDisconnectTest : public TestInterface {
 public:
  PeerConnectDisconnectTest();
  ~PeerConnectDisconnectTest() override;
  int RunTest(
      DataStructures::List<RakString> params,
      bool isVerbose,
      bool noPauses)
      override; //should return 0 if no error, or the error number
  RakString GetTestName() override;
  RakString ErrorCodeToString(int errorCode) override;
  void DestroyPeers() override;

 protected:
  void WaitForConnectionRequestsToComplete(
      RakPeerInterface** peerList,
      int peerNum,
      bool isVerbose);
  void
  WaitAndPrintResults(RakPeerInterface** peerList, int peerNum, bool isVerbose);

 private:
  DataStructures::List<RakPeerInterface*> destroyList;
};
