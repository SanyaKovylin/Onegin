#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#include "unisorter.h"
#include "myio.h"
#include "utils.h"

const char Source[] ="Source/source.txt";
const char Output[] ="Build/sorted.txt";

int main (const int argc, const char *argv[]){

    char *Buffer = NULL;
    size_t lenbuf = BaseRead (Source, &Buffer);

    Line *text = NULL;
    size_t size = StrToPoint (Buffer, lenbuf, &text);

    struct Flags ConsoleFlags = {0, 0, 0, 0};

    struct OneginContent Content{
        Buffer,
        lenbuf,
        text,
        size,
        sizeof(Line),
        NULL,
        Output,
        fopen (Output, "w"),
    };

    if (argc != 1) {
        CheckInputFlags (argv, argc, &ConsoleFlags, Content);
    }
    else {
        return OneginSort (Content, cmpstr);
    }
    return 0;

    //PrintToFile(Output, text, size);
}


