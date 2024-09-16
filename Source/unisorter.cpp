#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>

#include"unisorter.h"
#include "utils.h"

union pointer {
        void *ub;
        uint64_t count;
    };

equality mstrcmp( const Line *line, const char *midelem, const rev needreverse);

int swap(void* p1, void* p2, size_t size);

int StrSorter(void *data,   size_t len,   size_t elsize,
                        int (*cmpfunc)(void *elem1, void *elem2)){

    #define POINTER(x) (void *) (((char*) data) + elsize*(x))
    #define POINT(x) (((char*) data) + elsize*(x))
    size_t left = 0;
    size_t right = len - 1;

    switch (len) {

        case 1: {

            return 1;
        }

        case 2: {
            if (cmpfunc(POINTER(0),POINTER(1)) > 0) {
                // printf("}}");
                if (!swap (POINTER(0), POINTER(1), elsize)) assert(0);

            }
            return 1;
        }
        default: break;
    }

    size_t middle = ((right + left) / 2);

    while (left < right) {
        while (cmpfunc(POINTER(left), POINTER(middle)) < 0) {
            left++;
        }
        while (cmpfunc(POINTER(right), POINTER(middle)) > 0 && right > 0) {
            right--;

        }
        // printf("t2");
        if (left <= right) {
            // printf("tt");
            if (middle == left){
                middle = right;
            }
            else if (middle == right) {
                middle = left;
            }
            if (!swap (POINTER(left), POINTER(right), elsize)) assert(0);

            if (right > 0) {
                right--;
            }
            left++;
        }

    }

    if (right > 0) {

        StrSorter(data, right + 1, elsize , cmpfunc);
    }

    if (left < len - 1) {

        StrSorter(POINTER(left), len-left, elsize ,cmpfunc);
    }

    return 1;
    #undef POINTER
}

int swap(void* p1, void* p2, size_t size){

    void *buffer = (void*) calloc (size, 1);
    memcpy(buffer, p1,size);
    memcpy(p1, p2, size);
    memcpy(p2, buffer, size);
    free(buffer);
    return 1;
}
