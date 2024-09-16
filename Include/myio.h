#ifndef MYIO_H_INCLUDED
#define MYIO_H_INCLUDED

#include "utils.h"

size_t BaseRead   (const char *src,   char **Buf);
size_t StrToPoint (  char  *buffer, size_t length, Line **textptr);
void PrintToFile(const char *file, Line *text ,size_t size);

#endif //IO_H_INCLUDED
