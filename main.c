#include "fdf.h"

int ft_htoi(char *str, int *b)
{
    int b;
    int nb;

    (*b) += 2;
    nb = 0;
    while (str[*b] != ' ' && str[*b] != '\n')
    {
        while (str[*b] >= '0' && str[*b] <= '9')
		    nb = (nb * 10) + (str[(*b)++] - '0');
        if (str[*b] == 'A' || str[*b] == 'a')
            nb = (nb * 10) + 10;
        else if (str[*b] == 'B' || str[*b] == 'b')
            nb = (nb * 10) + 11;
        else if (str[*b] == 'C' || str[*b] == 'c')
            nb = (nb * 10) + 12;
        else if (str[*b] == 'D' || str[*b] == 'd')
            nb = (nb * 10) + 13;
        else if (str[*b] == 'E' || str[*b] == 'e')
            nb = (nb * 10) + 14;
        else if (str[*b] == 'F' || str[*b] == 'f')
            nb = (nb * 10) + 15;
        b++;
    }
    return (nb);
}

int absolute(int x)
{
    if (x < 0)
        return (-x);
    return (x);
}

void get_line_in2points2(t_data *img, t_get_coord c) //// c = x0, d = x1 , i = y0, j = y1;
{
    int dx;
    int dy;
    int steps;
    float x;
    float y;
    dx = c.d - c.c;
    dy = c.j - c.i;
    if (absolute(dx) > absolute(dy))
        steps = absolute(dx);
    else
        steps = absolute(dy);
    c.xinc = dx /(float)steps;
    c.yinc = dy /(float)steps;
    x = c.c;
    y = c.i;
    printf("%f ,  %f, %d, %d, %d\n",c.xinc, c.yinc, dx, dy, steps);
    if (c.i < c.j)
    {
        while (y < c.j)
        {
            x = x + c.xinc;
            y = y + c.yinc;
            printf("%f , %f, %d   sdfgh\n",x , y, c.d);
            my_mlx_pixel_put(img, x, y, 0x00FF00);
        }
    }
    else if (c.i > c.j)
    {
         while (y > c.j)
        {
            x = x + c.xinc;
            y = y + c.yinc;
            printf("%f , %f, %d   sdfghsdfghjk\n",x , y, c.d);
            my_mlx_pixel_put(img, x, y, 0x00FF00);
        }
    }
}

void get_line_in2points(t_data *img, t_get_coord c) //// c = x0, d = x1 , i = y0, j = y1;
{
    int dx;
    int dy;
    int steps;
    float x;
    float y;
    dx = c.d - c.c;
    dy = c.j - c.i;
    if (absolute(dx) > absolute(dy))
        steps = absolute(dx);
    else
        steps = absolute(dy);
    c.xinc = dx /(float)steps;
    c.yinc = dy /(float)steps;
    x = c.c;
    y = c.i;
    printf("%f ,  %f, %d, %d, %d\n",c.xinc, c.yinc, dx, dy, steps);
    while (x < c.d)
    {
        x = x + c.xinc;
        y = y + c.yinc;
        printf("%f , %f, %d   sdfgh\n",x , y, c.d);
        my_mlx_pixel_put(img, x, y, 0x00FF00);
    }
}

void get_vertical_lines(t_data *img, t_get_coord c)
{
    int i;
    int n_verticals;
    int nbr_row;

    nbr_row = c.a;
    n_verticals = 0;
    while(n_verticals < c.s_aux)
    {
        c.b = 0;
        i = n_verticals;
        while (c.array[0][i] != 2147483648 && c.b < (nbr_row - 1)) // && n_verticals != c.s_aux)
        {
            c.c = c.array[0][i];
            c.d = c.array[0][i + c.s_aux];
            c.i = c.array[1][i];
            c.j = c.array[1][i + c.s_aux];
            printf("yheyyy --linea  %d   %d!!!\n", c.b, nbr_row);
            get_line_in2points2(img, c);
            i += c.s_aux;
            c.b++;
        }
        n_verticals++;
    }
}
void get_horizontal_lines(t_data *img, t_get_coord c)
{
    int i;
    int nbr_row;
    int aux_n_row;

    i = 0;
    nbr_row = c.a;
    aux_n_row = 0;
    while(aux_n_row < nbr_row)
    {
        while (c.array[0][i] != 2147483648)
        {
            c.c = c.array[0][i];
            c.d = c.array[0][i + 1];
            c.i = c.array[1][i];
            c.j = c.array[1][i + 1];
            printf("yeahhh !!!\n");
            get_line_in2points(img, c);
            i++;
            printf("yes\n");
            if ((i+1)%c.s_aux == 0)
            {  
                printf("aaaaaaaaaaaaaaaayes ---> %d\n", c.s_aux);
                //exit(-1);
                aux_n_row++;
                i++;
            }
        }
    }
}

void recalcul_coords (long int **map, t_get_coord c)
{
    int i;
    int s_row;
    i = 0;
    c.i = 0;
    c.j = 0;
    while (c.array[0][i] != 2147483648)
    {
        s_row = c.s_aux;
        c.x_init = c.x_aux;
        while (s_row)
        {
            if (map[c.i][c.j] == 2147483648)
            {
                c.i++;
                c.j = 0;
            }
            c.c = c.x_init;
            c.d = c.y_init;
            iso(&c.c, &c.d, (map[c.i][c.j] * c.scale/1.5));
            c.array[0][i] = c.c;
            c.array[1][i] = c.d;
            i++;
            c.x_init += c.scale;
            s_row--;
            c.j++;
        }
        c.y_init += c.scale;  
    }
}

void recalcul_scale(t_get_coord c, int *i, int *j, long int **map)
{
    float max;
    if (*i >= *j)
        max = *i;
    else
        max = *j;
    printf("%d  %f escala\n", c.scale, max);
    c.scale = (c.scale * (980/max));
    printf("%d   escala", c.scale);
    if (c.scale == 0)
        c.scale = 1;
    //exit (-1);
    recalcul_coords (map, c);

}

int get_the_center (long int *array, int i)
{
    int	a;
    int min;

	a = 0;
    min = array[a];
    while (array[a] != 2147483648)
    {
        printf("hey2\n");
        if (array[a] < min)
            min = array[a];
        a++;
    }
    return (min + i/2);
}

void center_coords (long int **array, int i, int j)
{
    int x_middle;
    int y_middle;
    int x_move;
    int y_move;
    int a;
    a = 0;
    x_middle = get_the_center(array[0], i);
    y_middle = get_the_center(array[1], j);
    printf("%d %d--> je\n", x_middle, y_middle);
    //exit(-1);
    x_move = 500 - x_middle;
    y_move = 500 - y_middle;
    while (array[0][a] != 2147483648)
    {
        printf("hey|%ld|\n", array[0][a]);
        array[0][a] += x_move;
        array[1][a] += y_move;
        a++;
    }
    printf("salgo");
    //exit(-1);
}

int	get_map_size(long int *array)
{
	int	i;
    int min;
    int max;

	i = 0;
    min = array[i];
	while (array[i] != 2147483648)
    {
        if (array[i] < min)
            min = array[i];
        i++;
    }
    i = 0;
    max = array[i];
    while (array[i] != 2147483648)
    {
        if (array[i] > max)
            max = array[i];
        i++;
    }
	return (max - min);
}

void put_coords_good (long int **map, t_get_coord c)
{
    int i;
    int j;
    i = get_map_size(c.array[0]);
    j = get_map_size(c.array[1]);
    printf("%d %d--> i\n", i, j);
    //exit(-1);
    recalcul_scale(c, &i, &j, map);
    i = get_map_size(c.array[0]);
    j = get_map_size(c.array[1]);
    /*if (i >= j)
    {
        if(i > 1000)
            return ;   //////////hay que poner la funcion recalcul_coords
    }
    else if (j > 1000)
        return ;*/    //////////hay que poner la funcion recalcul_coords
    center_coords (c.array, i, j);
}

long int **ft_coord_map (int nbr_row, long int **map, t_get_coord c)
{
    int i;
    int s_row;
    i = 0;
    c.array = (long int **)malloc(sizeof(long int *) * 2);
    c.array[0] = malloc(sizeof(long int)*(nbr_row * c.s_aux + 1));
    c.array [1] = malloc(sizeof(long int) *(nbr_row * c.s_aux + 1));
    c.i = 0;
    while (nbr_row)
    {
        s_row = c.s_aux;
        c.x_init = c.x_aux;
        while (s_row)
        {
            if (map[c.i][c.j] == 2147483648)
            {
                c.i++;
                c.j = 0;
            }
            c.c = c.x_init;
            c.d = c.y_init;
            iso(&c.c, &c.d, (map[c.i][c.j] * c.scale/1.5));
            c.array[0][i] = c.c;
            c.array[1][i] = c.d;
            i++;
            c.x_init += c.scale;
            s_row--;
            c.j++;
        }
        c.y_init += c.scale;  
        nbr_row--;
    }
    c.array[0][i] = 2147483648;
    c.array[1][i] = 2147483648;
    put_coords_good (map, c);
    return (c.array);
}

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
    t_get_coord coords;
    t_program	mlx_p;
	t_data		img;
    int i = 0;
    coords.x = 500;	//CENTRO
	coords.y = 500;	//CENTRO
    coords.scale = 50;
    //printf ("%d---%d", s_row, nbr_row);
    coords.a = (s_row * coords.scale)/2;
    coords.b = (nbr_row * coords.scale)/2;
    coords.x_init = coords.x - coords.a;
    coords.y_init = coords.y - coords.b; 
    coords.s_aux = s_row; 
    coords.x_aux = coords.x_init;
    coords.i = 0;
    coords.j = 0;
	mlx_p.mlx = mlx_init();
	mlx_p.mlx_win = mlx_new_window(mlx_p.mlx, 1000, 1000, "Hello World!");
	img.img = mlx_new_image(mlx_p.mlx, 1000, 1000);
	img.ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
    coords.array = ft_coord_map (nbr_row, map, coords);
    free(map);
    coords.a = nbr_row;
    printf("|%d||%d|",nbr_row, s_row);
    //exit(0);
    while (coords.array[0][i] != 2147483648)
    {
        if (coords.array[0][i] < 1000 && coords.array[1][i] < 1000)
            my_mlx_pixel_put(&img, coords.array[0][i], coords.array[1][i], 0x0000FF00);
        //get_horizontal_lines(&img, coords);
        //while ()
        i++;
    }
    get_horizontal_lines(&img, coords);
    get_vertical_lines(&img, coords);
	mlx_put_image_to_window(mlx_p.mlx, mlx_p.mlx_win, img.img, 0, 0);
	//mlx_hook(mlx_p.mlx_win, 2, 3, ft_key, mlx_p.mlx);
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
            //printf ("%-3ld", map[i][c]);
            if (map[i][c] > INT_MAX || map[i][c] < INT_MIN)
			    ft_error();
            if (map[i][c] > 350)
                map[i][c] = 350;
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
        i++;
    }
    return (map);
}

void rev_hexas(char *map, int *i)
{
    int b;

    b = 0;
    if (map[*i] != '0' || map[(*i) + 1] != 'x')
    {
        printf("heheheh\n");
        ft_error ();
    }
    (*i) +=2;
    while (map[*i] && (map[*i] != ' ' && map[*i] != '\n') )
    {
        if (map[*i] < '0' || (map[*i] > '9' && map[*i] < 'A'))
        {
            printf("heheheh\n");
            ft_error ();
        }
        if ((map[*i] > 'F' && map[*i] < 'a') || map[*i] > 'f')
        {
            printf("2heheheh\n");
            ft_error ();
        }
        (*i)++;
        b++;
    }
    if (b > 6)
        ft_error ();
}

void rev_map (char *map)
{
    int i;

    i = 0;
    while (map[i] != '\0')
    {
        while(map[i] == ' ')
            i++;
        if(map[i] == '-' || map[i] == '+')
            i++;
        if(!ft_isdigit(map[i]))
        {
            printf("|%c|2heheheh\n", map[i]);
            ft_error();
        }
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
    //get_next_line (fd, &line);
    while (i > -1)
    {
        i = get_next_line (fd, &line);
        aux = ft_strjoin(line, "\n");
        free (line);
        line = NULL;
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
            all_map = ft_strdup(line);
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