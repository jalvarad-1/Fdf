#include "fdf.h"
void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

int		ft_key(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void get_coordenates_init(long int **map, int s_row, int nbr_row)
{
    int a;
    int b;
    int	x = 500;	//CENTRO
	int y = 500;	//CENTRO
    int x_init;
    int y_init;
    int scale;
    int s_aux;
    int x_aux;
    int c;
    int d;
    scale = 20;
    printf ("%d---%d", s_row, nbr_row);
    a = (s_row * scale)/2;
    b = (nbr_row * scale)/2;
    x_init = x - a;
    y_init = y - b; 
    s_aux = s_row; 
    x_aux = x_init;
    t_program	mlx_p;
	t_data		img;
    if (!map)
        exit(0);
	mlx_p.mlx = mlx_init();
	mlx_p.mlx_win = mlx_new_window(mlx_p.mlx, 1000, 1000, "Hello World!");
	img.img = mlx_new_image(mlx_p.mlx, 1000, 1000);
	img.ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
    while (nbr_row)
    {
        s_row = s_aux;
        x_init = x_aux;
        while (s_row)
        {
            c = x_init;
            d = y_init;
            iso(&c, &d, 0);
            printf("%d---%d\n", c, d);
            my_mlx_pixel_put(&img, c, d, 0x0000FF00);
            x_init += scale;
            s_row--;
        }
        y_init += scale;  
        nbr_row--;
    }
	//my_mlx_pixel_put(&img, x_init, y_init, 0x0000FF00);
	mlx_put_image_to_window(mlx_p.mlx, mlx_p.mlx_win, img.img, 0, 0);
	mlx_hook(mlx_p.mlx_win, 2, 3, ft_key, mlx_p.mlx);
	mlx_loop(mlx_p.mlx);
}
long int  **get_nbrs_map(char **split, int  s_row, int nbr_row)
{
    long int **map;
    int i;
    int j;
    int c;

    i = 0;
    map = (long int **)malloc(sizeof(long int) * nbr_row);
    
    while (split[i])
    {
        j = 0;
        c = 0;
        map[i] = malloc(sizeof(long int *) * (s_row + 1));
        while (split[i][j] && c < s_row)
        {
            map[i][c] = ft_atoi(split[i] + j);
            printf ("%-3ld", map[i][c]);
            if (map[i][c] > INT_MAX || map[i][c] < INT_MIN)
			    ft_error();
            while (split[i][j] == '-' || split[i][j] == '+')
			    j++;
		    while (split[i][j] == ' ')
			    j++;
		    while (ft_isdigit(split[i][j]))
			    j++;
            if (split[i][j] == ',')
            {
                j++;
                rev_hexas(split[i], &j);
            }
		    while (split[i][j] == ' ')
			    j++;
            c++;
        }
        map[i][c] = 2147483648;
        //printf ("%ld\n", map[i][c]);
        i++;
    }
    return (map);
}

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
    t_tools_map     m;
    m.i = 0;
    m.fd = open(argv[1], O_RDONLY);
    if (m.fd == -1 || argc != 2)
        ft_error();
    m.all_map = get_map (m.fd);
    rev_map (m.all_map);
    m.nbr_row = ft_word_count(m.all_map, '\n');
    m.split = ft_split(m.all_map, '\n');
    m.s_row = ft_word_count(m.split[m.i], ' ');
    m.i++;
    while (m.nbr_row > 1 && m.split[m.i])
    {
        m.s_aux = ft_word_count(m.split[m.i], ' ');
        if (m.s_row != m.s_aux)
            ft_error();
        m.i++;
    }
    m.map =  get_nbrs_map(m.split, m.s_row, m.nbr_row);
    get_coordenates_init(m.map, m.s_row, m.nbr_row);
    free (m.all_map);
}