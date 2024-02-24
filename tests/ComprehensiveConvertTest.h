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

#include <cstdio>
#include <cstdlib> // For atoi
#include <cstring> // For strlen
#include "Rand.h"

using namespace RakNet;

class ComprehensiveConvertTest : public TestInterface {
 public:
  ComprehensiveConvertTest();
  ~ComprehensiveConvertTest() override;
  int RunTest(
      DataStructures::List<RakString> params,
      bool isVerbose,
      bool noPauses)
      override; //should return 0 if no error, or the error number
  RakString GetTestName() override;
  RakString ErrorCodeToString(int errorCode) override;
  void DestroyPeers() override;

 private:
  static const int NUM_PEERS = 10;
  RakPeerInterface* peers[NUM_PEERS];
};
