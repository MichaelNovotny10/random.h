#include <stdio.h>
#include "Random.h"

int main(void) {
    // Random integers
    printf("=== xrandInt ===\n");
    for (int i = 0; i < 5; i++)
        printf("  %d\n", xrandInt(0, 100));

    // Random floats
    printf("=== xrandFloat ===\n");
    for (int i = 0; i < 5; i++)
        printf("  %.4f\n", xrandFloat(0.0f, 1.0f));

    // Random booleans
    printf("=== xrandBool ===\n");
    for (int i = 0; i < 8; i++)
        printf("  %d", xrandBool());
    printf("\n");

    // Random choice from array
    printf("=== xrandChoice ===\n");
    const char *words[] = {"apple", "banana", "cherry", "date"};
    for (int i = 0; i < 5; i++)
        printf("  %s\n", xrandChoice(words));

    // Manual seed — same seed always produces the same sequence
    printf("=== xrandSeed (reproducible) ===\n");
    xrandSeed(42);
    for (int i = 0; i < 3; i++)
        printf("  %d\n", xrandInt(0, 1000));

    return 0;
}
