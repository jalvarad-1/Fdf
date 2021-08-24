#include "fdf.h"

void rev_hexas(char *map, int *i)
{
    int b;

    b = 0;
    if (map[*i] != '0' || map[(*i) + 1] != 'x')
        ft_error ();
    (*i) +=2;
    while (b < 6)
    {
        if (map[*i] < '0' || map[*i] > 'F')
            ft_error ();
        if (map[*i] > '9' && map[*i] < 'A')
            ft_error ();
        (*i)++;
        b++;
    }
}

void rev_map (char *map)
{
    int i;

    i = 0;
    while (map[i] != '\0')
    {
        if(map[i] == '-' || map[i] == '+')
            i++;
        if(!ft_isdigit(map[i]))
            ft_error();
        while (ft_isdigit(map[i]))
            i++;
        if (map [i] == ',')
        {
            i++;
            rev_hexas(map, &i);
        }
        if (map[i] != '\0' && map[i] != ' ' && map[i] != '\n')
            ft_error ();
        while (map[i] == ' ')
            i++;
        while (map [i] == '\n')
            i++;
    }
}

char *get_map(int fd)
{
    char    *line;
    char    *aux;
    char    *all_map;
    int     i;

    line = NULL;
    all_map = NULL;
    i = 1;
    while (i > 0)
    {
        i = get_next_line (fd, &line);
        aux = ft_strjoin(line, "\n");
        free (line);
        if (!all_map)
        {
            all_map = ft_strdup(aux);
            free (aux);
        }
        else if (all_map)
        {
            line = ft_strjoin(all_map, aux);
            free (all_map);
            free (aux);
            all_map = line;
        }
    }
    return (all_map);
}

void    ft_error(void)
{
    write (1, "Error\n", 6);
    exit (-1);
}

int main (int argc, char **argv)
{
    int     fd;
    char    *all_map;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1 || argc != 2)
        ft_error();
    all_map = get_map (fd);
    rev_map (all_map);
    printf ("%s\n", all_map);
    free (all_map);
}