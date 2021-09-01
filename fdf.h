#ifndef FDF_H
# define FDF_H

# include "Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct s_program
{
	void *mlx;
	void *mlx_win;
}	t_program;

typedef struct s_data
{
	void *img;
	char *ptr;
	int bpp;
	int	line_length;
	int endian;
}	t_data;

typedef struct	s_tools_map
{
	int			fd;
    char		*all_map;
    char		**split;
    int			s_row;
    int     	s_aux;
    int			i;
    int			nbr_row;
    long int	**map;
}	t_tools_map;

void    ft_error(void);
void rev_hexas(char *map, int *i);
#endif