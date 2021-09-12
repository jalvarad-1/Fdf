/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:41 by jalvarad          #+#    #+#             */
/*   Updated: 2021/09/11 19:41:15 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_map_aux(int fd, char **line, char **aux, char **all_map)
{
	int	i;

	i = 1;
	while (i > -1)
	{
		i = get_next_line (fd, line);
		*aux = ft_strjoin(*line, "\n");
		free (*line);
		*line = NULL;
		if (!(*all_map))
		{
			*all_map = ft_strdup(*aux);
			del_str(*aux);
		}
		else if (*all_map)
		{
			*line = ft_strjoin(*all_map, *aux);
			free (*all_map);
			free (*aux);
			*aux = NULL;
			*all_map = ft_strdup(*line);
		}
		free(*line);
	}
}

static char	*get_map(int fd)
{
	char	*line;
	char	*aux;
	char	*all_map;

	line = NULL;
	all_map = NULL;
	get_map_aux(fd, &line, &aux, &all_map);
	return (all_map);
}

static void	get_dimensions(t_tools_map *m)
{
	m->all_map = get_map (m->fd);
	close(m->fd);
	rev_map (m->all_map);
	m->nbr_row = ft_word_count(m->all_map, '\n');
	m->split = ft_split(m->all_map, '\n');
	free (m->all_map);
	m->s_row = ft_word_count(m->split[m->i], ' ');
}

int	main(int argc, char **argv)
{
	t_tools_map	m;

	m.i = 0;
	m.fd = open(argv[1], O_RDONLY);
	if (m.fd == -1 || argc != 2)
		ft_error();
	get_dimensions(&m);
	if (m.s_row < 2 || m.nbr_row < 2)
		error_in_map(m.split);
	m.i++;
	while (m.nbr_row > 1 && m.split[m.i])
	{
		m.s_aux = ft_word_count(m.split[m.i], ' ');
		if (m.s_row != m.s_aux)
			error_in_map(m.split);
		m.i++;
	}
	m.map = get_nbrs_map(m.split, m.s_row, m.nbr_row, &m.colors);
	del_split(m.split);
	get_coordenates_init(m.map, m.s_row, m.nbr_row, m.colors);
	return (0);
}
