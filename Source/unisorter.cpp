#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>

#include "unisorter.h"
#include "utils.h"
#include "memswap.h"

int StrSorter (void *data,   size_t len,   size_t elsize,
                        int (*cmpfunc)(void *elem1, void *elem2))
{

    #define POINTER(x) (void *) (((char*) data) + elsize*(x))

    assert (data    != NULL);
    assert (cmpfunc != NULL);

    size_t left = 0;
    size_t right = len - 1;

    switch (len) {

        case 1: {

            return 1;
        }

        case 2: {
            if (cmpfunc (POINTER(0), POINTER(1)) > 0) {

                memswap (POINTER(0), POINTER(1), elsize);
            }
            return 1;
        }
        default: break;
    }

    size_t middle = ((right + left) / 2);

    while (left < right) {

        while (cmpfunc (POINTER (left), POINTER (middle)) < 0) {
            left++;
        }

        while (cmpfunc (POINTER (right), POINTER (middle)) > 0 && right > 0) {
            right--;
        }

        if (left <= right) {

            if (middle == left){
                middle = right;
            }
            else if (middle == right) {
                middle = left;
            }

            memswap (POINTER(left), POINTER(right), elsize);

            if (right > 0) {
                right--;
            }
            left++;
        }

    }

    if (right > 0) {

        StrSorter (data, right + 1, elsize , cmpfunc);
    }

    if (left < len - 1) {

        StrSorter (POINTER(left), len-left, elsize ,cmpfunc);
    }

    return 0;
    #undef POINTER
}
