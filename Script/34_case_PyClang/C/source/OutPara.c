#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    char *p;
    char *v;
}S;

void Pass (S *st, char *Store)
{
    char *tmp = Store;
    
    memcpy (tmp, "pwdtest", strlen ("pwdtest"));
    tmp += strlen ("pwdtest");

    strcpy (tmp, st->p);
    return;
}




