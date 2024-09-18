#ifndef MYIO_H_INCLUDED
#define MYIO_H_INCLUDED

#include "utils.h"

struct Flags {
    int StraightSort;
    int ReverseSort;
    int Origin;
    int NeedHelp;
};

//=========================================================================
//Flags
#define HelpFlag "--help"

#define OriginFlag "--origin"

const char HFlag = 'h';
#define HFlagStr "h"

const char OFlag = 'o';
#define OFlagStr "o"

const char SFlag = 's';
#define SFlagStr "s"

const char RFlag = 'r';
#define RFlagStr "r"
//==========================================================================

size_t BaseRead    (const char *src,   char **Buf);
size_t StrToPoint  (  char  *buffer, size_t length, Line **textptr);
void PrintToFile   (const char *file, Line *text ,size_t size, FILE* fwrite=NULL);

int CheckInputFlags (const char *argv[], int ArgNum,
                    struct Flags *ConsoleFlags, OneginContent Content);

#endif //IO_H_INCLUDED
