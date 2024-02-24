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

#include "DS_List.h"
#include "RakNetTypes.h"
#include "RakPeerInterface.h"
#include "RakString.h"
#include "TestInterface.h"

using namespace RakNet;

class SystemAddressAndGuidTest : public TestInterface {
 public:
  SystemAddressAndGuidTest();
  ~SystemAddressAndGuidTest() override;
  int RunTest(
      DataStructures::List<RakString> params,
      bool isVerbose,
      bool noPauses)
      override; //should return 0 if no error, or the error number
  RakString GetTestName() override;
  RakString ErrorCodeToString(int errorCode) override;
  void DestroyPeers() override;

 protected:
  bool compareSystemAddresses(
      SystemAddress ad1,
      SystemAddress ad2); //true if same;
 private:
  DataStructures::List<RakString> errorList;
  DataStructures::List<RakPeerInterface*> destroyList;
};
