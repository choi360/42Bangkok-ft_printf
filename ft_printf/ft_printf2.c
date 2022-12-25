#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int print_string(char *str, char c, int flag)
{
    int count;

    if (flag)
    {
        if (str)
        {
        count = 0;
        while (str[count++])
            ;
        return (write(1, str, count - 1));
        }
        else
        {
            return (write(1, "(null)", 6));
        }
    }
    else
    {
        return (write(1, &c, 1));
    }
}