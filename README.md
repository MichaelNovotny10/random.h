# Random.h - A fast single-header xorshift64 PRNG for C

## Features
* Single header (you only need to download one file)
* No dependencies, standard C
* Optimized for speed
* Seeded from hardware clock

## Usage
```c
#include "Random.h"

int main(void) {
    int n   = xrandInt(0, 100);
    float f = xrandFloat(0.0f, 100.0f);
    int b   = xrandBool();
    int arr[] = {0,1,2,3};
    int choice1 = xrandChoice(arr);
    int choice2 = xrandChoiceL(arr, 4);
}
```

## Config

### Settings
* XRAND_FIXED_SEED: Fixes seed to 0xdeadbeefcafeULL
* XRAND_NO_ASSERT:  Disables compile-time check that unsigned long long
                    is 64 bit

### How to use
Must be defined **before** the include:
```c
#define XRAND_FIXED_SEED
#define XRAND_NO_ASSERT
#include "Random.h"
```

## API Reference

| Function | Returns | Description | Precondition |
|---|---|---|---|
| `xrand()` | `uint64` | Raw 64-bit random number | — |
| `xrandSeed(seed)` | `void` | Override the rng seed | — |
| `xrandInt(min, max)` | `int` | Random integer in [min, max] | max >= min |
| `xrandFloat(min, max)` | `float` | Random float in [min, max] | max >= min |
| `xrandBool()` | `int` | 0 or 1 | — |
| `xrandChoice(arr)` | element | Random element from a stack array | arr must not be a pointer |
| `xrandChoiceL(arr, len)` | element | Random element from array of known length | len > 0 |

## Platform notes
Requires x86 for rdtsc seeding. On other platforms, define `XRAND_FIXED_SEED` or call `xrandSeed()` manually before generating numbers.

## Roadmap

- [x] Core implementation
- [ ] Cross-platform support
- [ ] `XRAND_IMPLEMENTATION` guard (stb-style)
- [ ] Thread safety
- [ ] C++ compatibility
- [ ] More customization options (`xrandDouble`, `xrandShuffle`, `xrandWeighted`, `xrandString`)
- [ ] Speed & quality improvements
- [ ] Benchmarks in README
- [ ] GitHub Releases with versioned header downloads

## License
Licensed under the MIT License.
See: https://opensource.org/licenses/MIT
