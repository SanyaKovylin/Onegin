#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

// size_t getline (char **lineptr, size_t n, FILE *stream);
//
// int main(void){
//     FILE *fp = fopen("onegin.txt","r");
//     char *buf = (char *) calloc (200000, sizeof(char));
//     char *line = NULL;
//     int sumlen = 0;
//     int len = 0;
//     size_t l = 100;
//     while (( len = getline(&line, l, fp) )!= -1) {
//         // printf("%d %s", len, line);
//         if (len > 110){
//             strcat(buf, line);
//             sumlen += strlen(line);
//         }
//
//     }
//     FILE *fw = fopen("source.txt","w");
//     fwrite(buf, sizeof(char), sumlen, fw);
// }
