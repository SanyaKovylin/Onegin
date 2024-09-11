#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "utils.h"


void swapstr(char *str1, char *str2);
int Sort(int **s, size_t len);


// static int s[] = {1, 2, 3};
//
// static size_t slen = 3;
// int *d = s;

// static struct Line text[9] =
//     {
//         {6,"::Myt"},
//         {5,"Nyt, "},
//         {5,"Mytt"},
//         {5,"Nyt "},
//         {5,"Nytg"},
//         {6,"Mytio"},
//         {6, "uncle" },
//         {7 ,"mostly"},
//         {4, "lol" },
//     };
// Line *T = text;
// static size_t txtlen = 9;
//
// int main(void){
// //     Sort(&d, slen);
// //     char r[3] = "w:";
// //     for (size_t i = 0; i<slen; i++) {
// //
// //         printf("%d", s[i]);
// //     }
//     printf ("\n%d", mystrcmp ("But it was passion that preempted", "At once Anisia came to greet her,"));
//     StrSort(&T, txtlen);
//     for (size_t i = 0; i<txtlen; i++) {
//
//         printf("\n!%s!", text[i].line);
//     }
// }

void swapstr(char *str1, char *str2){
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    //printf("(%s %s)", str1, str2);
    char buf = 0;
    size_t len = len1 > len2 ? len2 : len1;
    //printf("%d", len);
    for (size_t i = 0; i < len; i++) {

        buf = str1[i];
        str1[i] = str2[i];
        str2[i] = buf;
    }
    //printf("(%s %s)", str1, str2);
    if (len1 > len2) {
        for (size_t i = len; i < len1; i++) {

            str2[i] = str1[i];
            str1[i] = '\0';
        }
    }

    if (len1 < len2) {
        for (size_t i = len; i < len2; i++) {

            str1[i] = str2[i];
            str2[i] = '\0';
        }
    }


    //printf("(%s %s)", str1, str2);
}


int Sort(int **s, size_t len){

    if (len == 1) return 0;

    // printf(" Q%dQ \n", len);
    size_t ll = 0;
    size_t rr = len - 1;

    int buf = 0;

    int piv = (*s)[(ll + rr) / 2];

//     for (size_t i = 0; i<len; i++) {
//
//             printf("%d", (*s)[i]);
//         }
//     printf("\n%d\n", piv);

    while (ll < rr) {
        //printf("%d %d %d\n", ll, rr);
        while ((*s)[ll] < piv) {
            ll++;
        }

        while ((*s)[rr] > piv && rr > 0) {
            rr--;
        }

        if (ll <= rr) {

            buf = (*s)[ll];

            (*s)[ll] = (*s)[rr];
            (*s)[rr] = buf;
            if (rr > 0)
                rr--;
            ll++;
        }
    }


    if (rr > 0) {
        //printf("%d",rr);
        Sort(s, rr + 1);
    }
    if (ll < len - 1) {
        int *s1 = (*s + ll);
        Sort(&s1, len-ll);
    }




    return 1;
}

int StrSort(struct Line **txt, size_t len, rev needreverse){

    size_t ll = 0;
    size_t rr = len - 1;

    // for (int i = 0; i < len; i++) {
    //     //strcat(outbuf, text[i].line);
    //     printf("%s", (*txt)[i].line );
    // }
    // printf("\n");

    char *piv = (char*) calloc (LEN, sizeof (char));
    strcpy (piv, (*txt)[(ll + rr) /2 ].start + 1);

    printf("|||||%s\n",piv);

    printf("%d", mystrcmp (&(*txt)[ll], piv, needreverse));

    struct Line buf = {};

    while (ll < rr) {


        while (mystrcmp (&((*txt)[ll]), piv, needreverse) == LOWER) {

            ll++;
            printf("\n%lld %lld %s %s\n", ll, rr, (*txt)[ll].start + 1, piv);
        }

        printf("{{%s %lld}}",(*txt)[ll].start+1, ll);

        while ((mystrcmp (&(*txt)[rr], piv, needreverse) == HIGHER) && rr > 0) {
            printf("%lld\n", rr);
            rr--;
        }

        if (ll <= rr) {


            // swapstr((*txt)[ll].line, (*txt)[rr].line);
            buf = (*txt)[ll];
            (*txt)[ll] = (*txt)[rr];
            (*txt)[rr] = buf;
            if (rr > 0)
                rr--;
            ll++;
        }
        printf("%lld %lld \n", ll, rr);
    }

    for (size_t i = 0; i < len; i++) {
        //strcat(outbuf, text[i].line);
        printf("%s", (*txt)[i].start+1);
    }
    printf("\n");
    printf("%lld %lld\n", ll, rr);
    printf("-------------------------------------------------");
    printf("\n");

    if (rr > 0) {
        StrSort(txt, rr + 1, needreverse);
    }
    if (ll < len - 1) {
        Line *txt1 = (*txt + ll);
        StrSort(&txt1, len-ll, needreverse);
    }

    return 1;
}

eq mystrcmp( const Line *line, const char *piv,const rev needreverse){

    int i1 = 0;
    int i2 = 0;
    printf("TTTTT\n");
    size_t len = line->length;
    size_t len1 = strlen (piv);
    printf("TTTTT %lld\n", len);
    char *s1 = (char*) calloc ( len, sizeof (char));
    printf("TTTTT\n");
    char *s2 = (char*) calloc (len1, sizeof (char));
     printf("TTTTT\n");

    if (needreverse) {
        for (size_t i = 0; i < len; i++) {
            s1[i] = line->start[len - i - 1];
        }
        for (size_t i = 0; i < len1; i++) {
            s2[i] = piv[len1 - i - 1];

        }
    }
    else {
        strcpy(s1, line->start+1);
        strcpy(s2, piv);
    }

    printf("(%s)\n(%s)\n\n", s2, s1);

    for (;!isalpha(s1[i1]); i1++);
    for (;!isalpha(s2[i2]); i2++);

    while (s1[i1] != '\0' && s1[i1] == s2[i2] && s2[i2] != '\0') {
        printf("%c %c", s1[i1], s2[i2]);
        i1++;
        i2++;
    }
        printf("%c %c", s1[i1], s2[i2]);

    eq ans = ER;

    if (s1[i1] == '\0') {

        if (s2[i2] == '\0') {

            ans = EQUAL;
        }
        else {

            ans = LOWER;
        }
    }
    else {
        if (s2[i2] == '\0') {

            ans = HIGHER;
        }
        else {
            if (s1[i1] > s2[i2]) {

                ans = HIGHER;
            }
            else {

                ans = LOWER;
            }
        }
    }
    // printf("END%s\n", s1);
    // assert(s1);
    // free(s1);
    // printf("END1");
    // free(s2);
    // printf("END2");
    // printf("\n");
    return ans;
}

