#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#include "console.h"
#include "myio.h"

const char Source[] ="Source/source.txt";
const char Output[] ="Build/sorted.txt";

int main (const int argc, const char *argv[]){

    char *buffer = NULL;
    size_t lenbuf = BaseRead (Source, &buffer);

    Line *text = NULL;
    size_t size = StrToPoint (buffer, &lenbuf, &text); // создать Line* CreatLine, StrToLine

    FlagStates States {
        .order    = {},
        .pointer  =  0,
        .needhelp =  0,
    };

    struct OneginContent Content{
        .buffer = buffer,
        .lenbuf = lenbuf,
        .text   = text,
        .length = size,
        .elsize = sizeof(Line),
        .cmpfunc = NULL,
        .output = Output,
        .fwrite = fopen (Output, "w"),
    };

    CheckInputFlags (argv, argc, &States);
    // Я ХОЧУ: чтобы функция которая называется CheckInputFlags
    //         проверяла флаги и не больше
    // Я ХОЧУ: функцию, в которую я передам "настройки" (consoleFlags) и она мне сделает

    OneginSort (Content, States.order, States.pointer);

    return 0;

    //PrintToFile(Output, text, size);
}


