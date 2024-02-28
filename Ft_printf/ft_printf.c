#include <unistd.h>
#include <stdarg.h>

void    ft_putstr(char *str, int *len)
{
    int i = 0;
    if(!str)
        str = "(null)";
    while (str[i])
        *len += write(1, &str[i++], 1);
}

void    ft_putnbr_hex(long long int nbr, int base, int *len)
{
    char	*hex = "0123456789abcdef";

    if(nbr < 0)
    {
        nbr *= -1;
        *len += write(1, "-", 1);
    }
    if(nbr >= base)
        ft_putnbr_hex((nbr / base), base, len);
    *len += write(1, &hex[nbr % base], 1);
}

int ft_printf(const char *str, ...)
{
    int i = 0;
    int len = 0;

    va_list ptr;
    va_start(ptr, str);
    while(str[i])
    {
        if (str[i] == '%')
        {
            i++;
            if(str[i] == 's')
                ft_putstr(va_arg(ptr, char *), &len);
            else if(str[i] == 'd')
                ft_putnbr_hex((long long int)va_arg(ptr, int), 10, &len);
            else if(str[i] == 'x')
                ft_putnbr_hex((long long int)va_arg(ptr, unsigned int), 16, &len);
        }
        else
            len += write(1, &str[i], 1);
        i++;
    }
    return (va_end(ptr), len);
}
