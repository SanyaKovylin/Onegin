#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#include "utils.h"

int StrSort(struct Line **txt, size_t len, rev needreverse){

    size_t left = 0;
    size_t right = len - 1;

    char *midelem = (char*) calloc (100, sizeof (char));
    strcpy (midelem, (*txt)[(left + right) / 2].start + 1);

    struct Line buffer = {};

    while (left < right) {

        while (mystrcmp (&((*txt)[left]), midelem, needreverse) == LOWER) {

            left++;
        }

        while ((mystrcmp (&(*txt)[right], midelem, needreverse) == HIGHER) && right > 0) {
            right--;
        }

        if (left <= right) {

            buffer = (*txt)[left];
            (*txt)[left] = (*txt)[right];
            (*txt)[right] = buffer;

            if (right > 0) {
                right--;
            }

            left++;
        }

    }

    if (right > 0) {

        StrSort(txt, right + 1, needreverse);
    }

    if (left < len - 1) {

        Line *txt1 = (*txt + left);
        StrSort(&txt1, len-left, needreverse);
    }

    return 1;
}

equality mystrcmp( const Line *line, const char *midelem, const rev needreverse){

    int elem1 = 0;
    int elem2 = 0;

    size_t len = line->length;
    size_t len1 = strlen (midelem);

    char *src1 = (char*) calloc ( len, sizeof (char));
    char *src2 = (char*) calloc (len1 + 2, sizeof (char));


    if (needreverse) {

        for (size_t i = 0; i < len; i++) {

            src1[i] = line->start[len - i - 1];
        }

        for (size_t i = 0; i < len1; i++) {

            src2[i] = midelem[len1 - i - 1];
        }
    }
    else {
        strcpy(src1, line->start + 1);
        strcpy(src2,         midelem);
    }

    for (;!isalpha(src1[elem1]); elem1++);
    for (;!isalpha(src2[elem2]); elem2++);

    while (src1[elem1] == src2[elem2]  && src1[elem1] != '\0'
                                       && src2[elem2] != '\0') {

        elem1++;
        elem2++;
    }

    equality ans = ER;

    if (src1[elem1] == '\0') {

        if (src2[elem2] == '\0') {

            ans = EQUAL;
        }
        else {

            ans = LOWER;
        }
    }
    else {
        if (src2[elem2] == '\0') {

            ans = HIGHER;
        }
        else {
            if (src1[elem1] > src2[elem2]) {

                ans = HIGHER;
            }
            else {

                ans = LOWER;
            }
        }
    }

    free(src1);
    free(src2);
    return ans;
}

int cmpstr(void* el1, void* el2){

    int elem1 = 0;
    int elem2 = 0;

    Line *line1 = (Line*) el1;
    Line *line2 = (Line*) el2;

    size_t len1 = line1->length;
    size_t len2 = line2->length;

    char *src1 = (char*) calloc (len1, sizeof (char));
    char *src2 = (char*) calloc (len2, sizeof (char));

    strcpy(src1, line1->start + 1);
    strcpy(src2, line2->start + 1);

    for (;!isalpha(src1[elem1]); elem1++);
    for (;!isalpha(src2[elem2]); elem2++);

    while (src1[elem1] == src2[elem2]  && src1[elem1] != '\0'
                                       && src2[elem2] != '\0') {

        elem1++;
        elem2++;
    }

    equality ans = ER;

    if (src1[elem1] == '\0') {

        if (src2[elem2] == '\0') {

            ans = EQUAL;
        }
        else {

            ans = LOWER;
        }
    }
    else {
        if (src2[elem2] == '\0') {

            ans = HIGHER;
        }
        else {
            if (src1[elem1] > src2[elem2]) {

                ans = HIGHER;
            }
            else {

                ans = LOWER;
            }
        }
    }
    free(src1);
    free(src2);
    return ans;
}

int revcmpstr(void* el1, void* el2){

    int elem1 = 0;
    int elem2 = 0;

    Line *line1 = (Line*) el1;
    Line *line2 = (Line*) el2;

    size_t len1 = line1->length;
    size_t len2 = line2->length;

    char *src1 = (char*) calloc (len1, sizeof (char));
    char *src2 = (char*) calloc (len2, sizeof (char));

    for (size_t i = 0; i < len1; i++) {

        src1[i] = (*line1).start[len1 - i - 1];
    }
    for (size_t i = 0; i < len2; i++) {
        src2[i] = (*line2).start[len2 - i - 1];
    }


    for (;!isalpha(src1[elem1]); elem1++);
    for (;!isalpha(src2[elem2]); elem2++);

    while (src1[elem1] == src2[elem2]  && src1[elem1] != '\0'
                                       && src2[elem2] != '\0') {

        elem1++;
        elem2++;
    }

    equality ans = ER;

    if (src1[elem1] == '\0') {

        if (src2[elem2] == '\0') {

            ans = EQUAL;
        }
        else {

            ans = LOWER;
        }
    }
    else {
        if (src2[elem2] == '\0') {

            ans = HIGHER;
        }
        else {
            if (src1[elem1] > src2[elem2]) {

                ans = HIGHER;
            }
            else {

                ans = LOWER;
            }
        }
    }
    free(src1);
    free(src2);
    return ans;
}
