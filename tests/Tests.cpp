/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <gtest/gtest.h>

#include "DS_List.h"
#include "IncludeAllTests.h"
#include "RakString.h"

class RakNetTest : public testing::Test {
 protected:
  DataStructures::List<RakString> noParamsList;
  bool isVerbose = true;
  bool disallowTestToPause = true;
};

#define RAKNET_TEST(TEST_NAME)                                                                   \
    TEST_F(RakNetTest, Run##TEST_NAME)                                                        \
    {                                                                                         \
        TEST_NAME test;                                                                       \
        const int result = test.RunTest(noParamsList, isVerbose, disallowTestToPause);        \
        ASSERT_EQ(result, 0) << "Test failed with error: " << test.ErrorCodeToString(result); \
        test.DestroyPeers();                                                                  \
    }

RAKNET_TEST(EightPeerTest)
RAKNET_TEST(MaximumConnectTest)
RAKNET_TEST(PeerConnectDisconnectWithCancelPendingTest)
RAKNET_TEST(PeerConnectDisconnectTest)
RAKNET_TEST(ManyClientsOneServerBlockingTest)
RAKNET_TEST(ManyClientsOneServerNonBlockingTest)
RAKNET_TEST(ManyClientsOneServerDeallocateBlockingTest)
RAKNET_TEST(ReliableOrderedConvertedTest)
RAKNET_TEST(DroppedConnectionConvertTest)
RAKNET_TEST(ComprehensiveConvertTest)
RAKNET_TEST(CrossConnectionConvertTest)
RAKNET_TEST(PingTestsTest)
RAKNET_TEST(OfflineMessagesConvertTest)
RAKNET_TEST(LocalIsConnectedTest)
RAKNET_TEST(SecurityFunctionsTest)
RAKNET_TEST(ConnectWithSocketTest)
RAKNET_TEST(SystemAddressAndGuidTest)
RAKNET_TEST(PacketAndLowLevelTestsTest)
RAKNET_TEST(MiscellaneousTestsTest)
