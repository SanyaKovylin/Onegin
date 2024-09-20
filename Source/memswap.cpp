#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>
#include <stdint.h>

#include <memswap.h>

#define POINTER(y) (void *) ((char*) y + pointer)

void memswap (void* p1, void* p2, size_t size){

    size_t pointer = 0;
    size_t elsize = sizeof(uint64_t);

    static char buffer [sizeof(uint64_t)] = {};

    while (elsize > 0){
        while (size - pointer >= elsize) {

            swapbysize(POINTER(p1), POINTER(p2), buffer, elsize);
            pointer += elsize;
        }
        elsize /= 2;
    }
}

void swapbysize (void* p1, void* p2, void* buffer, size_t size){

    assert (p1 != NULL);
    assert (p2 != NULL);

    memcpy ((void*) buffer, p1, size);
    memcpy (p1, p2, size);
    memcpy (p2, (void*) buffer, size);
}
