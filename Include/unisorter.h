#ifndef UNISORTER_H_INCLUDED
#define UNISORTER_H_INCLUDED

int StrSorter(void *data,   size_t len,   size_t elsize,
                        int (*cmpfunc)(void *elem1, void *elem2));

#endif //UNISORTER_H_INCLUDED
