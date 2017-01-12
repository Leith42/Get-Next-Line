/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/12 22:28:48 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char const *argv[])
{
	char *line = NULL;
	int fd;
	int save;

	if(argc != 2)
		return(-1);
	fd = open(argv[1], O_RDONLY);
	while((save = get_next_line(fd, &line)))
	{
		printf("%s\n", line);
		ft_strdel(&line);
	}
	close(fd);
	return 0;
}

static int	ft_get_line(char **line, char **save, char **endl_pos)
{
	char *tmp;

	if(!(*line = ft_strsub(*save, 0, *endl_pos - *save)))
		return (-1);
	if(!(tmp = ft_strdup(*endl_pos + 1)))
		return (-1);
	ft_strdel(&*save);
	*save = tmp;
	return (1);
}

static int	ft_stock(int fd, char **save)
{
	char	buff[BUFF_SIZE + 1] = "\0";
	char	*new_str;
	int		ret_read;

	if((ret_read = read(fd, buff, BUFF_SIZE)))
	{
		if(!(new_str = ft_strjoin(*save, buff)))
			return (-1);
		ft_strdel(&*save);
		*save = new_str;
	}
	return (ret_read);
}

int	get_next_line(const int fd, char **line)
{
	static char *save = NULL;
	char		*endl_pos;
	int			ret_read;

	if (!save)
	{
		if(!(save = ft_strnew(0)))
			return (-1);
	}
	while (!(endl_pos = ft_strchr(save, '\n')))
	{
		if ((ret_read = ft_stock(fd, &save)) == 0)
		{
			ft_strdel(&save);
			return (0);
		}
		else if (ret_read == -1)
		{
			ft_strdel(&save);
			return (-1);
		}

	}
	if (ft_get_line(line, &save, &endl_pos))
		return (ft_strlen(*line));
	return (-1);
}
