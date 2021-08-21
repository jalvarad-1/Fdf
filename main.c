#include "fdf.h"

void rev_hexas()
{
    
}
void rev_map (char *map)
{
    int i;

    i = 0;
    while (map[i] != '\0')
    {
        if (i == 0 && !ft_isdigit(map[i]))
            ft_error();
        if (map[i] == ' ' && !ft_isdigit(map[i + 1]))
            ft_error();
        if (map[i] == '\n' && !ft_isdigit(map[i + 1]))
            ft_error();
        if (i != 0 && ft_isdigit(map[i]))
            rev_hexas();
        i++;
    }
}

char *get_map(int fd)
{
    char    *line;
    char    *aux;
    char    *all_map;

    line = NULL;
    all_map = NULL;
    while (get_next_line (fd, &line))
    {
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
    free (line);
    return (all_map);
}

void    ft_error(void)
{
    write (1, "Error\n", 6);
}

int main (int argc, char **argv)
{
    int     fd;
    /*char    *line;
    char    *aux;*/
    char    *all_map;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1 || argc != 2)
        ft_error();
    //line = NULL;
    all_map = get_map (fd);
    rev_map ();
    printf ("%s", all_map);
    free (all_map);
}