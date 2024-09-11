#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "main.h"
#include "utils.h"

const size_t startalloc = 6000;

//int getline (char **lineptr, size_t n, FILE *stream);

int main (void){

    int fo = open (Source, O_RDONLY ,"rb");

    struct stat st = {};

    stat (Source, &st);

    printf ("%ld\n", st.st_size);

    char *filebuf = (char*) calloc (st.st_size + 2, sizeof (char));
    filebuf[0] = '\0';

    read (fo, filebuf + 1, st.st_size);

    size_t size = 0;
    size_t alloc = startalloc;
    struct Line *text = (Line*) calloc (alloc,sizeof(Line));
    text[size].start = filebuf;

    size_t w = 1;
    _off_t r = 1;

    for (r = 1; r < 500; r++) {
    // for (r = 1; r < st.st_size ; r++) {
        //strcat(outbuf, text[i].line);
        //printf("%c", filebuf[i]);
        // printf("%llu\n", size);
        if (filebuf[r + 1] != '\r') {
            if (filebuf[r] != '\n') {

                filebuf[w] = filebuf[r];
            }
            else {

                filebuf[w] = '\0';
                text[size].end = w + filebuf;
                text[size].length = text[size].end - text[size].start;
                text[size + 1].start = filebuf + w;
                size++;
            }
            // if (size > 0){
            //     printf("%s\n", text[size - 1].start + 1 );
            // }
            //printf("%llu\n", size);
            w++;
        }
//         if (size + 1  > alloc) {
//                 alloc *= 2;
//                 printf("%llu %llu", size, alloc);
//                 text = (Line*) realloc (text, alloc*sizeof(Line));
//
//                 assert(text != NULL);
//             }
    }

    size++;
    text = (Line*) realloc (text, size*sizeof(Line));
    assert(text != NULL);

    filebuf[w] = '\0';
    filebuf = (char*) realloc (filebuf,sizeof(char)*w);

    assert(filebuf != NULL);

    StrSort(&text, size, STRAIGHT);

    size_t lenbuf = w;
    printf("\n\n\n%llu\n", size);

    for (size_t i = 0; i < size; i++) {

        printf("%d %s\n",text[i].length, text[i].start + 1);
    }



//     FILE *fw = fopen ("w", Output);
//
//     fwrite (filebuf, sizeof (char),  lenbuf, fw);


//     struct Line *text = (Line*) calloc (LENGTH, sizeof (Line));
//
//     int len = 0;
//     int linenum = 0;
//     int nLENGTH = 1;
//     int sumlen = 0;
//     size_t l = LEN;
//
//     char *line = (char *) calloc (l, sizeof(char));
//
//      while ((len = mygetline(&line, l, fo)) != -1) {
//
//         if (linenum == LENGTH*nLENGTH) {
//
//             nLENGTH++;
//             text = (Line*) realloc (text, LENGTH*nLENGTH*sizeof (Line));
//
//         }
//
//         text[linenum] = {(size_t) len, {'\0'}};
//
//         for (int i = 0; i < len + 1; i++){
//             text[linenum].line[i] = line[i];
//         }
//
//         text[linenum].length = len;
//         sumlen += len + 1;
//
//         linenum++;
//     }
//
//     text = (Line*) realloc (text, linenum*sizeof (Line));
//
//     StrSort(&text, linenum);
//
//     char *outbuf = (char*) calloc (sumlen, sizeof (char));
//
//     FILE *fw = fopen (Output, "w");
//
//     for (int i = 0; i < linenum; i++) {
//         strcat(outbuf, text[i].line);
//         //fprintf(fw, "%d !%s!",text[i].length ,text[i].line );
//     }
//
//     fwrite (outbuf, sizeof (char), sumlen, fw);
}



