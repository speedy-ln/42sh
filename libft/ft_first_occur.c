#include "libft.h"

int ft_first_occur(char *str, char first, char second)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == first)
            return (1);
        else if (str[i] == second)
            return (2);
        i++;
    }
    return (0);
}
