#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "myio.h"


const size_t startalloc = 6000;

// int ParseConsoleArgument (const char *argv[], int CurrentPos, int CurrentArg,
                        //   struct Flags *ConsFlags);

void PrintSplitter(FILE* fw);


size_t BaseRead (const char *src, char **Buffer) {

    assert (src    != NULL);
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


size_t StrToPoint (char *buffer, size_t *len, Line **textptr){

    assert (textptr != NULL);
    assert (buffer  != NULL);

    size_t size = 0;
    size_t lenbuf = *len;
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

    *len = writer;
    for (; writer < lenbuf; writer++) {
        buffer[writer] = '\0';
    }

    text = (Line*) realloc (text, size*sizeof(Line));
    assert(text != NULL);

    *textptr = text;
    return size;
}

void PrintToFile (const char *file, Line *text ,size_t size, FILE* fwrite){

    assert (file != NULL);
    assert (text != NULL);

    FILE *fw = NULL;

    if (!fwrite) {
        fw = fopen (file, "w");
    }
    else {
        fw = fwrite;
    }

    for (size_t i = 0; i < size; i++) {

        fputs (text[i].start + 1, fw);
        fputs ("\n",fw);
    }


    PrintSplitter(fw);
}

void PrintOrigin (OneginContent Content){

    char *buffer = Content.buffer + 1;
    size_t len = Content.lenbuf;

    FILE* fw = Content.fwrite;

    size_t pointer = 0;

    while (pointer < len - 1) {
        fputs (buffer + pointer, fw);
        pointer += strlen (buffer + pointer) + 1;
        fputc ('\n', fw);
    }
    PrintSplitter(fw);
}

void PrintSplitter(FILE*fw) {
        fputs (
        "\n"
        "------------------------------------------------------------------------------------------"
        "\n\n",
        fw
    );
}
