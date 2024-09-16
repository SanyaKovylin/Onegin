#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "myio.h"

const size_t startalloc = 6000;

size_t BaseRead (const char *src, char **Buffer) {

    assert (src != NULL);
    assert (Buffer != NULL);

    int fo = open (src, O_RDONLY | O_BINARY);

    struct stat st = {};

    stat (src, &st);
    _off_t readlen = st.st_size;
    // _off_t readlen = 1500;

    *Buffer = (char*) calloc (readlen + 2, sizeof (char));
    *Buffer[0] = '\0';

    size_t lenbuf = read (fo, *Buffer + 1, readlen);
    return lenbuf;
}


size_t StrToPoint(char *buffer, size_t lenbuf, Line **textptr){

    assert (textptr != NULL);
    assert (buffer  != NULL);

    size_t size = 0;
    size_t alloc = startalloc;

    struct Line *text = (Line*) calloc (alloc, sizeof(Line));
    assert (text != NULL);

    text[size].start = buffer;

    size_t writer = 1;
    size_t reader = 1;

    for (reader = 1; reader < lenbuf - 1; reader++) {

        if (buffer[reader] != '\r') {

            if (buffer[reader] != '\n') {

                buffer[writer] = buffer[reader];
            }
            else {

                buffer[writer] = '\0';
                text[size].end = writer + buffer;
                text[size].length = text[size].end - text[size].start;
                text[size + 1].start = text[size].end;
                size++;
            }

            writer++;
        }
    }

    for (; writer < lenbuf; writer++) {
        buffer[writer] = '\0';
    }

    text = (Line*) realloc (text, size*sizeof(Line));
    assert(text != NULL);

    *textptr = text;
    return size;
}

void PrintToFile (const char *file, Line *text ,size_t size){

    assert (file != NULL);
    assert (text != NULL);

    FILE *fw = fopen(file, "w");

    for (size_t i = 0; i < size; i++) {

        fprintf(fw, "%s\n", text[i].start + 1);
    }
}
