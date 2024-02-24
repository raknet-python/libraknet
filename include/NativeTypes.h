/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#ifndef __NATIVE_TYPES_H
#define __NATIVE_TYPES_H

#if defined(__GNUC__) || defined(__GCCXML__) || defined(__SNC__) || \
    defined(__S3E__)
#include <stdint.h>
#elif !defined(_STDINT_H) && !defined(_SN_STDINT_H) && \
    !defined(_SYS_STDINT_H_) && !defined(_STDINT) &&   \
    !defined(_MACHTYPES_H_) && !defined(_STDINT_H_)
using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using int8_t = signed char;
using int16_t = short;
using int32_t = int;
#if defined(_MSC_VER) && _MSC_VER < 1300
typedef unsigned __int64 uint64_t;
typedef signed __int64 int64_t;
#else
using uint64_t = unsigned long long;
using int64_t = long long;
#endif
#endif

#endif
