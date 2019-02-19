#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static char a;
    char        b;
    void        *c = malloc(32);

    printf("%p %p %p\n", &a, &b, c);

    free(c);

}