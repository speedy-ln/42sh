#include "fortytwosh.h"

int     ft_tab(t_main *e)
{
    int     x;
//    struct dirent   *dp;
//    DIR             *fd;

    x = -1;
    while (e->a[e->y].line[++x] == '\t' || e->a[e->y].line[++x] == ' ')
           ;
    e->is_tab = (e->cursor < x) + e->is_tab * (e->cursor >= x);
    if (e->ctrl_v == 1)//then tab space can be added hence
        e->is_tab = 1;
    if (e->is_tab && (ft_selectinsert(e, '\t')))//then mode to add tab spaces is activated.
        e->cursor += (e->cursor < e->a[e->y].x + 1);//thus add \t to string
    if (!e->ctrl_v && !e->is_tab)//then we need to print the list
    {//following list depends on where we are positioned in the string.
        //print list and add list to memory
    }
    //    fd = opendir(".");
//    if (e->y)//rm
//        ;
//    while ((dp = readdir(fd)))
//    {//0 1 free
        
//    }
//    ft_selectinsert(e, '\t');
//    e->cursor += 1;
//closedir(fd);
    e->is_tab = 0;
    e->ctrl_v = 0;//always false until cntrl v is clicked.
    return (1);
}
