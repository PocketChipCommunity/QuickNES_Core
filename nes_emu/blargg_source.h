/* Included at the beginning of library source files, AFTER all other #include
lines. Sets up helpful macros and services used in my source code. Since this
is only "active" in my source code, I don't have to worry about polluting the
global namespace with unprefixed names. */

// File_Extractor 1.0.0
#ifndef BLARGG_SOURCE_H
#define BLARGG_SOURCE_H

#ifndef BLARGG_COMMON_H // optimization only
	#include "blargg_common.h"
#endif
#include "blargg_errors.h"

#include <string.h> /* memcpy(), memset(), memmove() */
#include <stddef.h> /* offsetof() */

/* If expr yields non-NULL error string, returns it from current function,
otherwise continues normally. */
#undef  RETURN_ERR
#define RETURN_ERR( expr ) \
	do {\
		const char *blargg_return_err_ = (expr);\
		if ( blargg_return_err_ )\
			return blargg_return_err_;\
	} while ( 0 )

/* If ptr is NULL, returns out-of-memory error, otherwise continues normally. */
#undef  CHECK_ALLOC
#define CHECK_ALLOC( ptr ) \
	do {\
		if ( !(ptr) )\
			return blargg_err_memory;\
	} while ( 0 )

/* The usual min/max functions for built-in types. */

template<typename T> T min( T x, T y ) { return x < y ? x : y; }
template<typename T> T max( T x, T y ) { return x > y ? x : y; }

#define BLARGG_DEF_MIN_MAX( type )

BLARGG_DEF_MIN_MAX( int )
BLARGG_DEF_MIN_MAX( unsigned )
BLARGG_DEF_MIN_MAX( long )
BLARGG_DEF_MIN_MAX( unsigned long )
BLARGG_DEF_MIN_MAX( float )
BLARGG_DEF_MIN_MAX( double )
#if __WORDSIZE != 64
BLARGG_DEF_MIN_MAX( uint64_t )
#endif

// typedef unsigned char byte;
typedef unsigned char blargg_byte;
#undef  byte
#define byte blargg_byte

#ifndef BLARGG_EXPORT
	#if defined (_WIN32) && BLARGG_BUILD_DLL
		#define BLARGG_EXPORT __declspec(dllexport)
	#elif defined (__GNUC__)
		// can always set visibility, even when not building DLL
		#define BLARGG_EXPORT __attribute__ ((visibility ("default")))
	#else
		#define BLARGG_EXPORT
	#endif
#endif

#if BLARGG_LEGACY
	#define BLARGG_CHECK_ALLOC CHECK_ALLOC
	#define BLARGG_RETURN_ERR  RETURN_ERR
#endif

#endif
