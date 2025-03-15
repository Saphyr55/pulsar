#pragma once

#include <cstdint>
#include <cstdio>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;


/**
 * Defines PDEBUG on debugging.
 */
#if defined(_DEBUG) || defined(DEBUG)
#define PULSAR_IS_DEBUG
#endif

/**
 *
 */
#if defined(_MSC_VER)
#define PDEBUGBREAK() __debugbreak()
#else
#define PDEBUGBREAK() __builtin_trap()
#endif

/**
 *
 */
#ifdef PULSAR_IS_DEBUG
#define PCHECK(expr)   \
    if (!(expr)) {     \
        PDEBUGBREAK(); \
    }
#else
#define PCHECK(expr)
#endif

/**
 *
 */
// TODO: Remove printf() ...
#ifdef PULSAR_IS_DEBUG
#define PCHECK_MSG(expr, msg) \
    if (!(expr)) {            \
        ::printf("%s", msg);  \
        PDEBUGBREAK();        \
    }
#else
#define PCHECK_MSG(expr, msg)
#endif

/**
 *
 */
#if defined(__clang__) || defined(__gcc__)
#define PINLINE __attribute__((always_inline)) inline
#define PNOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define PINLINE __forceinline
#define PNOINLINE __declspec(noinline)
#else
#define PINLINE inline
#define PNOINLINE
#endif

#define PDEPRECATED(version, msg)
