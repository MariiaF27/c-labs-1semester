#ifndef MYSTRING_H
#define MYSTRING_H
#include <stddef.h>
size_t mystrlen(const char *s);
void *mymemcpy(void *dest, void *src, int n);
char *mystrchr(const char *str, int c);
char *mystrtok(char *string, char *delim);
char *get_str(char *prompt);
char *mystrdup(const char *src);

#endif