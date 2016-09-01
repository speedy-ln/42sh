#include "libft.h"

char        **ft_strarr_append(char **str1, char **str2)
{
    char    **tab;
    int     count;
    int     count2;

    count = 0;
    count2 = 0;
    if (!str1 && !str2)
        return (0);
    while (str1[count])
        count++;
    while (str2[count2])
        count2++;
    tab = (char **)malloc(sizeof(char *) * (count + count2 + 2));
    count = 0;
    count2 = 0;
    while (str1[count])
    {
        tab[count] = (char *)malloc(sizeof(char *) * ft_strlen(str1[count]));
        ft_strcpy(tab[count], str1[count]);
        count++;
    }
    while (str2[count2])
    {
        tab[count] = (char *)malloc(sizeof(char *) * ft_strlen(str2[count2]));
        ft_strcpy(tab[count], str2[count2]);
        count++;
        count2++;
    }
    tab[count] = 0;
    return (tab);
}
