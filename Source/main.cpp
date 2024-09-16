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

int main (void){

    char *Buffer = NULL;
    size_t lenbuf = BaseRead(Source, &Buffer);

    Line *text = NULL;
    size_t size = StrToPoint(Buffer, lenbuf, &text);

    StrSorter(text, size, sizeof(Line), revcmpstr);

    PrintToFile(Output, text, size);
}


