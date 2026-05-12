// Copyright (C) 2026 Michael Novotny.
// Licensed under the MIT License.
// See: https://opensource.org/licenses/MIT


// Single-header xorshift64 PRNG. Requires x86 unless XRAND_FIXED_SEED is defined.

// Settings:
//      XRAND_FIXED_SEED:       If defined, seed = 0xdeadbeefcafeULL
//                              If not defined, seed is randomized via rdtsc
//      XRAND_NO_ASSERT:        Disables compile-time check that unsigned long long is 64 bit

#ifndef RANDOM_H
#define RANDOM_H

#define XRAND_MAX 0xFFFFFFFFFFFFFFFFULL
typedef unsigned long long uint64;

#ifndef XRAND_NO_ASSERT
_Static_assert(sizeof(unsigned long long) == 8,
    "Random.h: unsigned long long is not 64 bits on this platform — library will malfunction.");
#endif

static uint64 rng_state = 0xdeadbeefcafeULL;

// Internal: auto-seeds rng_state on first call via rdtsc
static inline void rng_init() {
    static int seeded = 0;
    if (!seeded) {
        #ifndef XRAND_FIXED_SEED
        rng_state = __builtin_ia32_rdtsc();
        #endif
        seeded = 1;
    }
}

// xorshift64 with shift triple (13, 7, 17)
static inline uint64 xorshift64() {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state;
}

// Override the rng seed manually
static inline void xrandSeed(uint64 seed) {
    rng_state = seed;
}

static inline uint64 xrand() {
    rng_init();
    return xorshift64();
}

// Generate Random Integer (range: from min - max)
// Assumes max >= min
static inline int xrandInt(int min, int max) {
    return xrand() % (max - min + 1) + min;
}

// Generate Random Floating Point Number (range: from min - max)
// Assumes max >= min
static inline float xrandFloat(float min, float max) {
    const float inv_max = 1.0f / (float)XRAND_MAX;
    return ((float)xrand() * inv_max) * (max - min) + min;
}

// Generate Random Boolean (0,1)
static inline int xrandBool() {
    return xrand() % 2;
}

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

// Return Random Element of Array (can be used with structs)
#define xrandChoice(arr)       ((arr)[xrandInt(0, ARRAY_LEN(arr) - 1)])
#define xrandChoiceL(arr, len) ((arr)[xrandInt(0, (len) - 1)])

#endif
