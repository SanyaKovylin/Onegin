#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

enum eq {
    EQUAL  =  0,
    LOWER  = -1,
    HIGHER =  1,
    ER   = 1000,
};

enum rev {
    STRAIGHT = 0,
    REVERSE  = 1,
};

eq mystrcmp (const Line *line, const char *s1, rev needreverce);
int StrSort (struct Line **txt, size_t len, rev needreverce);

#endif //UTILS_H_INCLUDED
