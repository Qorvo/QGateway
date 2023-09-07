#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <string.h>
#include <stdint.h>
#include <inttypes.h>

//compiler specific stuff
#define INLINE
#define PACKED_PRE
#define PACKED_POST  __attribute__((packed))
#define ALIGNMENT_NEEDED

#define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))

//#define HAVE_NO_64BIT

#define NORETURN

//Pointer type, use this type to perform pointer arithmetic
typedef uintptr_t  UIntPtr;
typedef UIntPtr    UIntPtr_P;

#endif //_COMPILER_H_
