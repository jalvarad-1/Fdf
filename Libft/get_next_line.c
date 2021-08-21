/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:27:47 by jalvarad          #+#    #+#             */
/*   Updated: 2021/06/08 17:19:22 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_return(ssize_t n_bytes, char **save, char **line)
{
	char	*temp;
	char	*temp2;

	if (n_bytes == -1)
		return (-1);
	if (!n_bytes && !*save)
		*line = ft_strdup("");
	else if (ft_strchr(*save, '\n'))
	{
		temp = ft_strchr(*save, '\n');
		*temp = '\0';
		*line = ft_strdup(*save);
		temp2 = ft_strdup (temp + 1);
		free(*save);
		*save = temp2;
		return (1);
	}
	else if (ft_strchr(*save, '\0'))
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char			*tmp;
	char			buff[BUFFER_SIZE + 1];
	static char		*save[FD_SETSIZE];
	ssize_t			n_bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	n_bytes = read(fd, buff, BUFFER_SIZE);
	while (n_bytes > 0 )
	{
		buff[n_bytes] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(save[fd], buff);
			free(save[fd]);
			save[fd] = tmp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
		n_bytes = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_return(n_bytes, &save[fd], &*line));
}
