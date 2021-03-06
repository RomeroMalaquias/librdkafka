/*
* librdkafka - Apache Kafka C library
*
* Copyright (c) 2012-2015 Magnus Edenhill
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * Win32 (Visual Studio) support
 */
#pragma once


#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <assert.h>



/**
 * Types
 */
typedef SSIZE_T ssize_t;
typedef int socklen_t;

struct iovec {
	void *iov_base;
	size_t iov_len;
};

struct msghdr {
	struct iovec  *msg_iov;
	int            msg_iovlen;
};

#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7



/**
* Annotations, attributes, optimizers
*/
#ifndef likely
#define likely(x)   x
#endif
#ifndef unlikely
#define unlikely(x) x
#endif

#define RD_UNUSED
#define RD_WARN_UNUSED_RESULT
#define RD_NORETURN __declspec(noreturn)
#define RD_IS_CONSTANT(p)  (0)
#define RD_TLS __declspec(thread)


/**
 * Allocation
 */
#define rd_alloca(N) _alloca(N)


/**
 * Strings, formatting, printf, ..
 */

/* size_t and ssize_t format strings */
#define PRIusz  "Iu"
#define PRIdsz  "Id"

#define RD_FORMAT(...)
#define rd_snprintf(...)  sprintf_s(__VA_ARGS__)
#define rd_vsnprintf(buf,size,...) vsnprintf_s(buf,size,_TRUNCATE,__VA_ARGS__)

#define rd_strcasecmp(A,B) _stricmp(A,B)
#define rd_strncasecmp(A,B,N) _strnicmp(A,B,N)


/**
 * Errors
 */
static __inline RD_UNUSED const char *rd_strerror(int err) {
	static RD_TLS char ret[128];

	strerror_s(ret, sizeof(ret) - 1, err);
	return ret;
}


/**
 * Atomics
 */
#include "rdatomic.h"


/**
 * Misc
 */

/**
 * Microsecond sleep.
 * 'retry': if true, retry if sleep is interrupted (because of signal)
 */
#define rd_usleep(usec,terminate)  Sleep((usec) / 1000)


#define rd_assert(EXPR)  assert(EXPR)

/**
 * Empty struct initializer
 */
#define RD_ZERO_INIT  {0}
