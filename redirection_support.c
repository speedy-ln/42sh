#include "fortytwosh.h"

static  void    initialize_null(char *str)
{
    int     i;

    i = -1;
    while(str[++i])
        str[i] = '\0';
}

char    *get_commands(char *line, char **cmd, char *redirects)
{
    int     count;
    int     redirects_count;
    int     cmd_count;
    int     temp_count;
    char    *temp;

    count = 0;
    temp_count = 0;
    cmd_count = 0;
    redirects_count = 0;
    temp = (char *)malloc(sizeof(char *) * (ft_strlen(line) + 1));
    int     i;

    i = -1;
    while(temp[++i])
        temp[i] = '\0';
    while (line[count])
    {
        if (line[count] == '<')
        {
            if (line[count + 1] && line[count + 1] == '<')
            {
                count++;
                redirects[redirects_count] = '1';
            }
            else
                redirects[redirects_count] = '2';
            temp[temp_count] = '\0';
            cmd[cmd_count] = (char *)malloc(sizeof(char *) * ft_strlen(temp));
            ft_strcpy(cmd[cmd_count], temp);
            temp_count = 0;
            cmd_count++;
            redirects_count++;
            initialize_null(temp);
        }
        else if (line[count] == '>')
        {
            if (line[count + 1] && line[count + 1] == '>')
            {
                count++;
                redirects[redirects_count] = '3';
            }
            else
                redirects[redirects_count] = '4';
            temp[temp_count] = '\0';
            cmd[cmd_count] = (char *)malloc(sizeof(char *) * ft_strlen(temp));
            ft_strcpy(cmd[cmd_count], temp);
            temp_count = 0;
            cmd_count++;
            redirects_count++;
            initialize_null(temp);
        }
        else
        {
            temp[temp_count] = line[count];
            temp_count++;
        }
        count++;
    }
    cmd[cmd_count] = ft_strdup(temp);
    if (cmd[cmd_count + 1])
        cmd[cmd_count + 1] = NULL;
    free(temp);
    return (redirects);
}