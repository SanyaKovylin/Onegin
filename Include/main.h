#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

const char Source[] ="Source/source.txt";
const char Output[] ="Build/sorted.txt";

const int LENGTH = 1000;
const int LEN = 100;

struct Line {
    size_t length;
    char *start;
    char *end;
};

#endif //MAIN_H_INCLUDED
