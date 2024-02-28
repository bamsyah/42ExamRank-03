#include <stdarg.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *str)
{
    char *n = "(null)";
    int i = 0;
    if (str == NULL)
        return (ft_putstr(n));
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (ft_strlen(str));
}
int count_nbr (int nbr, int signe, int base)
{
    int count  = 0;
    if (nbr == 0)
        return (0);
    while (nbr != 0)
    {
       nbr /= base;
       count++;
    }
    if (signe == -1)
        count++;
    return (count);
}
int ft_putnbr(long int nbr)
{
    int signe = 1;
    if (nbr < 0)
    {
        signe = -1;
        ft_putchar('-');
        nbr *= -1;
    }
    if (nbr > 9)
    {
        ft_putnbr(nbr / 10);
        ft_putnbr(nbr % 10);
    }
    else
        ft_putchar(nbr + 48);
    return (count_nbr(nbr, signe, 10));
}
int ft_puthex(unsigned long nbr, int base)
{
	char    *hex = "0123456789abcdef";

    if (nbr >=16)
    {
        ft_puthex(nbr / 16, base);
        ft_puthex(nbr % 16, base);
    }
    else
    {
        if (nbr <10)
            ft_putnbr(nbr);
        else
            ft_putchar(hex[nbr]);
    }
    return (count_nbr(nbr, 1, 16));
}

int ft_sec(va_list args, char k)
{
    int c = 0;
    if (k == 'd')
        c+=ft_putnbr(va_arg(args, int));
    if (k == 's')
        c+= ft_putstr(va_arg(args, char *));
    if (k == 'x')
        c+= ft_puthex(va_arg(args, unsigned int), 'x');
    if (k =='%')
        c+= ft_putchar('%');
    return (c);
}

int    ft_printf(const char *str, ...)
{
    va_list args;
    int i = 0;
    int k = 0;
    if (!str)
        return (0);
    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%')
		{
            k+= ft_sec(args, str[i+1]);
			i++;
		}
        else
            k+= ft_putchar(str[i]);
        i++;
    }
    va_end(args);
    return(k);
}