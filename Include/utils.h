#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED



enum equality {
    EQUAL  =  0,
    LOWER  = -1,
    HIGHER =  1,
    ER   = 1000,
};

enum rev {
    STRAIGHT = 0,
    REVERSE  = 1,
};

struct Line {
    size_t length;
    char *start;
    char *end;
};

struct OneginContent {
    char* buffer;
    size_t lenbuf;
    Line* text;
    size_t length;
    size_t elsize;
    int (*cmpfunc)(void *elem1, void *elem2);
    const char *output;
    FILE* fwrite;
};

int OneginSort (OneginContent Content, int (*cmpfunc)(void *elem1, void *elem2));

equality mystrcmp (const Line *line, const char *s1, rev needreverce);
int StrSort (struct Line **txt, size_t len, rev needreverce);
int cmpstr (void* el1, void* el2);
int revcmpstr (void* el1, void* el2);
#endif //UTILS_H_INCLUDED
