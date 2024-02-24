/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "WSAStartupSingleton.h"

#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)
#include <winsock2.h>
#include <ws2tcpip.h>

#endif
#include <cstdio>
#include "RakNetDefines.h"

int WSAStartupSingleton::refCount = 0;

WSAStartupSingleton::WSAStartupSingleton() = default;
WSAStartupSingleton::~WSAStartupSingleton() = default;

void WSAStartupSingleton::AddRef() {
#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)

  refCount++;

  if (refCount != 1) {
    return;
  }

  WSADATA winsockInfo;
  if (WSAStartup(MAKEWORD(2, 2), &winsockInfo) != 0) {
#if defined(_DEBUG) && !defined(WINDOWS_PHONE_8)
    DWORD dwIOError = GetLastError();
    LPVOID messageBuffer;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        dwIOError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR)&messageBuffer,
        0,
        nullptr);
    // something has gone wrong here...
    RAKNET_DEBUG_PRINTF(
        "WSAStartup failed:Error code - %lu\n%s",
        dwIOError,
        (LPTSTR)messageBuffer);
    //Free the buffer.
    LocalFree(messageBuffer);
#endif
  }

#endif
}

void WSAStartupSingleton::Deref() {
#if defined(_WIN32) && !defined(WINDOWS_STORE_RT)
  if (refCount == 0) {
    return;
  }

  if (refCount > 1) {
    refCount--;
    return;
  }

  WSACleanup();

  refCount = 0;
#endif
}
