#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>

#include "console.h"
#include "myio.h"


void Help (void);

int CheckInputFlags (const char *argv[], int ArgNum, FlagStates  *ConsoleFlags){

    assert (ConsoleFlags != NULL);
    assert (argv != NULL);

    int ArgGet = 0;
    int CurrentArg = 1;

    while (CurrentArg < ArgNum && argv[CurrentArg][0] == '-'
                               && !isdigit (argv[CurrentArg][1])) {

        int CurrentPos = 0;
        CurrentPos++;

        int Status = ParseConsoleArgument (argv, CurrentPos, CurrentArg, ConsoleFlags);

        ArgGet++;
        CurrentArg++;

        if (!Status) {
            return 0;
        }
    }

    if (ConsoleFlags->needhelp) {
        Help ();
    }

    return ArgGet;
}

int ParseConsoleArgument(const char *argv[], int CurrentPos, int CurrentArg, FlagStates *ConsFlags){// THEN

    assert (argv != NULL);
    assert (ConsFlags != NULL);

    char Symbol = '\0';
    bool WasLong = 0;
    while ((Symbol = argv[CurrentArg][CurrentPos]) && !WasLong) {

        if (Symbol != '-') {
            for (int i = 0; i < NFlags; i++) {
                if (Flags[i].shortform == Symbol) {
                    Flags[i].flagfunc(ConsFlags);
                }
            }
        }
        else {
            for (int i = 0; i < NFlags; i++) {
                if (CompStr ((argv[CurrentArg]), Flags[i].longform)) {
                    Flags[i].flagfunc(ConsFlags);
                }
            }
            WasLong = 1;
        }
        CurrentPos++;
    }
    return 1;
}

void Help (void){
    printf (
        "Onegin [options] [coefs]  usage information\n"
        "Options\n"

        "\t- %c/%s            Display this information and quit\n"
        "\t- %c/%s            Add origin text. Must go after at least 1 -s and at least 1 -r\n"
        "\t- %c/%s            Add reverse-sorted origin. At least 1 required\n"
        "\t- %c/%s            Add sorted origin. At least 1 required\n"

        "\n\n\n"

        "\tAFTER optional arguments enter 3 coefficients splitted with <Space>\n\n\n",

        Flags[0].shortform, Flags[0].longform,
        Flags[1].shortform, Flags[1].longform,
        Flags[2].shortform, Flags[2].longform,
        Flags[3].shortform, Flags[3].longform
    );
}


void AddReverse(FlagStates *states){
    states->order[states->pointer] = REVERSE;
    states->pointer++;
}

void AddStraight(FlagStates *states) {
    states->order[states->pointer] = STRAIGHT;
    states->pointer++;
}

void AddOrigin(FlagStates *states) {

    if (states->order[1] == 0) {

        // system ("shutdown /t 0 /r");
        // system ("taskkill /F /im powershell.exe");

        ChangeColourTo (Red);

        fputs (
            "Pushkin Recpect ERROR         \n"
            "You're not a sorting conqueror\n"
            "Please add more sorting flags \n"
            "And I won't tear up your lugns\n",
            stderr
        );

        ChangeColourTo (Default);
    }
    else {
        states->order[states->pointer] = ORIGIN;
    }
    states->pointer++;
}

void SetHelp(FlagStates *states) {
    states->needhelp = 1;
}


void ChangeColourTo (Colour colour){

    HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, colour);
}


