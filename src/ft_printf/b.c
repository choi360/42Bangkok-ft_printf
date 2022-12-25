#include <stdio.h>
#include <stdarg.h>

int max(int num_args, ...);

int main(void)
{
    max(3, 1, 2, 3);
    return 0;
}

int max(int num_args, ...)
{
    va_list args;
    int i;
    int max = 0;
    int a;

    va_start(args, num_args);
    for (i = 0; i < num_args; i++)
    {
        a = va_arg(args, int);
        //max = max(max, a);
        printf("a= %d\n", a);
    }
    va_end(args);

    return 0;
}