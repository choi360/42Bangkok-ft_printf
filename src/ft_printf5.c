#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
    char specifier;
    void (*function)(va_list ap, int *len);
} t_specifier;

void print_char(va_list ap, int *len) {
    char c = va_arg(ap, int);
    *len += write(1, &c, 1);
}

void print_string(va_list ap, int *len) {
    char *str = va_arg(ap, char *);
    if (str) {
        int i = 0;
        while (str[i]) {
            *len += write(1, &str[i], 1);
            i++;
        }
    }
    else {
        *len += write(1, "(null)", 6);
    }
}

void print_int(va_list ap, int *len) {
    int64_t n = va_arg(ap, int);
    if (n < 0) {
        *len += write(1, "-", 1);
        n = -n;
    }
    if (n >= 10) {
        print_int(n / 10, len);
    }
    *len += write(1, "0123456789"[n % 10], 1);
}

void print_uint(va_list ap, int *len) {
    uint64_t n = va_arg(ap, unsigned int);
    if (n >= 10) {
        print_uint(n / 10, len);
    }
    *len += write(1, "0123456789"[n % 10], 1);
}

void print_hex(va_list ap, int *len, char *charset) {
    uint64_t n = va_arg(ap, unsigned int);
    if (n >= 16) {
        print_hex(n / 16, len, charset);
    }
    *len += write(1, &charset[n % 16], 1);
}

void print_pointer(va_list ap, int *len) {
    uintptr_t n = va_arg(ap, uintptr_t);
    *len += write(1, "0x", 2);
    if (n >= 16) {
        print_pointer(n / 16, len);
    }
    *len += write(1, "0123456789abcdef"[n % 16], 1);
}

int ft_printf(const char *format, ...) {
    static t_specifier specifiers[] = {
        {'c', print_char},
        {'s', print_string},
        {'d', print_int},
        {'i', print_int},
        {'u', print_uint},
        {'x', print_hex, "0123456789abcdef"},
        {'X', print_hex, "0123456789ABCDEF"},
        {'p', print_pointer},
        {0, NULL}
    };
    va_list ap;
    va_start(ap, format);
    int len = 0;

    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            i++;
            for (int j = 0; specifiers[j].specifier; j++) {
                if (format[i] == specifiers[j].specifier) {
                    specifiers[j].function(ap, &len);
                    break;
                }
            }
        }
        else {
            len += write(1, &format[i], 1);
        }
    }

    va_end(ap);
    return len;
}

// main test function
int main(void) {
    printf("printf: %d %s %c %p %x %X %u %i", 42, "hello", 'a', &ft_printf, 42, 42, 42, 42);
    ft_printf("ft_printf: %d %s %c %p %x %X %u %i", 42, "hello", 'a', &ft_printf, 42, 42, 42, 42);
    return 0;
}