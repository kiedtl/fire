//
// type.h: defines integer types.
// this file is part of the LPTSTR common C header collection, and
// is licensed under the MIT license.
// (c) Kied Llaentenn and LPTSTR contributors.
//

// why?
// I miss the Rust type system :P

#ifndef TYPE_H
#define TYPE_H

typedef uint8_t		 u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef int8_t		 i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

#if UINTPTR_MAX == 0xffff
typedef uint16_t      usize;
#elif UINTPTR_MAX == 0xffffffff
typedef uint32_t      usize;
#elif UINTPTR_MAX == 0xffffffffffffffff
typedef uint64_t      usize;
#endif

#if INTPTR_MAX == 0xffff
typedef int16_t       isize;
#elif INTPTR_MAX == 0xffffffff
typedef int32_t       isize;
#elif INTPTR_MAX == 0xffffffffffffffff
typedef int64_t       isize;
#endif

#endif
