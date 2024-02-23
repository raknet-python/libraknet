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
///

#include "NetworkIDManager.h"
#include "GetTime.h"
#include "NetworkIDObject.h"
#include "RakAssert.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include "SuperFastHash.h"

using namespace RakNet;

STATIC_FACTORY_DEFINITIONS(NetworkIDManager, NetworkIDManager)

NetworkIDManager::NetworkIDManager() {
  startingOffset = RakPeerInterface::Get64BitUniqueRandomNumber();
  Clear();
}
NetworkIDManager::~NetworkIDManager() = default;
void NetworkIDManager::Clear() {
  memset(networkIdHash, 0, sizeof(networkIdHash));
}
NetworkIDObject* NetworkIDManager::GET_BASE_OBJECT_FROM_ID(NetworkID x) {
  unsigned int hashIndex = NetworkIDToHashIndex(x);
  NetworkIDObject* nio = networkIdHash[hashIndex];
  while (nio) {
    if (nio->GetNetworkID() == x)
      return nio;
    nio = nio->nextInstanceForNetworkIDManager;
  }
  return nullptr;
}
NetworkID NetworkIDManager::GetNewNetworkID() {
  while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
    ;
  if (startingOffset == UNASSIGNED_NETWORK_ID) {
    while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
      ;
  }
  return startingOffset;
}
unsigned int NetworkIDManager::NetworkIDToHashIndex(NetworkID networkId) {
  //	return SuperFastHash((const char*) &networkId.guid.g,sizeof(networkId.guid.g)) % NETWORK_ID_MANAGER_HASH_LENGTH;
  return (unsigned int)(networkId % NETWORK_ID_MANAGER_HASH_LENGTH);
}
void NetworkIDManager::TrackNetworkIDObject(NetworkIDObject* networkIdObject) {
  RakAssert(networkIdObject->GetNetworkIDManager() == this);
  NetworkID rawId = networkIdObject->GetNetworkID();
  RakAssert(rawId != UNASSIGNED_NETWORK_ID);

  networkIdObject->nextInstanceForNetworkIDManager = nullptr;

  unsigned int hashIndex = NetworkIDToHashIndex(rawId);
  //	printf("TrackNetworkIDObject hashIndex=%i guid=%s\n",hashIndex, networkIdObject->GetNetworkID().guid.ToString()); // removeme
  if (networkIdHash[hashIndex] == nullptr) {
    networkIdHash[hashIndex] = networkIdObject;
    return;
  }
  NetworkIDObject* nio = networkIdHash[hashIndex];
  // Duplicate insertion?
  RakAssert(nio != networkIdObject);
  // Random GUID conflict?
  RakAssert(nio->GetNetworkID() != rawId);

  while (nio->nextInstanceForNetworkIDManager != nullptr) {
    nio = nio->nextInstanceForNetworkIDManager;

    // Duplicate insertion?
    RakAssert(nio != networkIdObject);
    // Random GUID conflict?
    RakAssert(nio->GetNetworkID() != rawId);
  }

  nio->nextInstanceForNetworkIDManager = networkIdObject;
}
void NetworkIDManager::StopTrackingNetworkIDObject(
    NetworkIDObject* networkIdObject) {
  RakAssert(networkIdObject->GetNetworkIDManager() == this);
  NetworkID rawId = networkIdObject->GetNetworkID();
  RakAssert(rawId != UNASSIGNED_NETWORK_ID);

  // RakAssert(networkIdObject->GetNetworkID()!=UNASSIGNED_NETWORK_ID);
  unsigned int hashIndex = NetworkIDToHashIndex(rawId);
  //	printf("hashIndex=%i\n",hashIndex); // removeme
  NetworkIDObject* nio = networkIdHash[hashIndex];
  if (nio == nullptr) {
    RakAssert(
        "NetworkIDManager::StopTrackingNetworkIDObject didn't find object" &&
        0);
    return;
  }
  if (nio == networkIdObject) {
    networkIdHash[hashIndex] = nio->nextInstanceForNetworkIDManager;
    return;
  }

  while (nio) {
    if (nio->nextInstanceForNetworkIDManager == networkIdObject) {
      nio->nextInstanceForNetworkIDManager =
          networkIdObject->nextInstanceForNetworkIDManager;
      return;
    }
    nio = nio->nextInstanceForNetworkIDManager;
  }

  RakAssert(
      "NetworkIDManager::StopTrackingNetworkIDObject didn't find object" && 0);
}
