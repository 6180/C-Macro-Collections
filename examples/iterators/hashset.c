/**
 * hashset.c
 *
 * Creation Date: 11/04/2019
 *
 * Authors:
 * Leonardo Vencovsky (https://github.com/LeoVen)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "hashset.h"

HASHSET_GENERATE(hs, hset, static, int)

size_t inthash(int t)
{
    size_t a = t;
    a += ~(a << 15);
    a ^= (a >> 10);
    a += (a << 3);
    a ^= (a >> 6);
    a += ~(a << 11);
    a ^= (a >> 16);
    return a;
}

int intcmp(int a, int b)
{
    return a - b;
}

int main(int argc, char const *argv[])
{
    size_t i;
    int r;

    // Initialize hash set and add some elements
    hset *hs = hs_new(10, 0.9, intcmp, inthash);
    for (int i = 0; i < 10; i++)
        hs_insert(hs, i);

    // Initialize iterator
    hset_iter iter;
    hs_iter_init(&iter, hs);

    // Make the iterator go back and forward
    for (int j = 0; j < 4; j++)
    {
        while (hs_iter_next(&iter, &r, &i))
            printf("C[%2d] = %2d\n", i, r);
        printf("\n");
        while (hs_iter_prev(&iter, &r, &i))
            printf("C[%2d] = %2d\n", i, r);
        printf("\n\n");
    }

    for (hs_iter_tostart(&iter); !hs_iter_end(&iter); /**/)
    {
        hs_iter_next(&iter, &r, &i);
        printf("S[%2d] = %2d\n", i, r);
    }

    printf("\n");

    for (hs_iter_toend(&iter); !hs_iter_start(&iter); /**/)
    {
        hs_iter_prev(&iter, &r, &i);
        printf("S[%2d] = %2d\n", i, r);
    }

    hs_free(hs);

    return 0;
}
