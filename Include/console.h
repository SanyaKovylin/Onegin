#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include "utils.h"
#include "colors.h"

const int maxsorts = 10;

struct FlagStates {
    Sorts order[maxsorts];
    size_t pointer;
    int needhelp;
};

struct Flag {
    char shortform;
    const char* longform;
    void (*flagfunc)(FlagStates*);
};

void AddReverse  (FlagStates *states);
void AddStraight (FlagStates *states);
void AddOrigin   (FlagStates *states);
void SetHelp     (FlagStates *states);

const Flag Flags[] {
    'h', "--help"    , SetHelp,
    'o', "--origin"  , AddOrigin,
    'r', "--reverse" , AddReverse,
    's', "--straight", AddStraight,
};

const int NFlags = 4;


int CheckInputFlags (const char *argv[], int ArgNum, FlagStates *States);
int ParseConsoleArgument(const char *argv[], int CurrentPos, int CurrentArg,
                          FlagStates *States);
void ChangeColourTo (Colour colour);

#endif //CONSOLE_H_INCLUDED
