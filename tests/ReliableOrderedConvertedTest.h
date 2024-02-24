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

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "DS_List.h"
#include "RakPeerInterface.h"
#include "RakString.h"
#include "TestInterface.h"

using namespace RakNet;

class ReliableOrderedConvertedTest : public TestInterface {
 public:
  ReliableOrderedConvertedTest();
  ~ReliableOrderedConvertedTest() override;
  int RunTest(
      DataStructures::List<RakString> params,
      bool isVerbose,
      bool noPauses)
      override; //should return 0 if no error, or the error number
  RakString GetTestName() override;
  RakString ErrorCodeToString(int errorCode) override;
  void DestroyPeers() override;

 protected:
  void* LoggedMalloc(size_t size, const char* file, unsigned int line);
  void LoggedFree(void* p, const char* file, unsigned int line);
  void*
  LoggedRealloc(void* p, size_t size, const char* file, unsigned int line);

 private:
  DataStructures::List<RakPeerInterface*> destroyList;
};
