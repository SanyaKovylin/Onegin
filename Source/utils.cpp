#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "myio.h"
#include "unisorter.h"

int OneginSort (OneginContent Content, Sorts *order, size_t numsorts){

    for (size_t i = 0; i < numsorts; i++) {
        switch (order[i]) {

            case REVERSE: {
                StrSorter (Content.text, Content.length, Content.elsize, revcmpstr);
                PrintToFile (Content.output, Content.text, Content.length, Content.fwrite);
                break;
            }

            case STRAIGHT: {
                StrSorter (Content.text, Content.length, Content.elsize, cmpstr);
                PrintToFile (Content.output, Content.text, Content.length, Content.fwrite);
                break;
            }

            case ORIGIN: {
                PrintOrigin(Content);
                break;
            }

            default: return 1;
        }
    }
    return 0;
}

int cmpstr (void* el1, void* el2){

    assert (el1 != NULL);
    assert (el2 != NULL);

    int elem1 = 0;
    int elem2 = 0;

    Line *line1 = (Line*) el1;
    Line *line2 = (Line*) el2;

    size_t len1 = line1->length;
    size_t len2 = line2->length;

    char *src1 = (char*) calloc (len1, sizeof (char));
    char *src2 = (char*) calloc (len2, sizeof (char));

    strcpy (src1, line1->start + 1);
    strcpy (src2, line2->start + 1);

    for (;!isalpha (src1[elem1]); elem1++);
    for (;!isalpha (src2[elem2]); elem2++);

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
    free (src1);
    free (src2);
    return ans;
}

int revcmpstr(void* el1, void* el2){

    assert (el1 != NULL);
    assert (el2 != NULL);

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


    for (;!isalpha (src1[elem1]); elem1++);
    for (;!isalpha (src2[elem2]); elem2++);

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
    free (src1);
    free (src2);
    return ans;
}

bool CompStr (const char *Line1, const char *Line2){

    assert (Line1 != NULL);
    assert (Line2 != NULL);

    int Position = 0;
    for (; Line1[Position] != '\0' && Line2[Position] != '\0'
                                   && Line1[Position] == Line2[Position]; Position++)
        ;

    return Line1[Position] == '\0' && Line2[Position] == '\0';

}
