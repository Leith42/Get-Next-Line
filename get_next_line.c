/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/13 14:42:29 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_get_line(char **line, char **save, char **endl_pos)
{
	char *tmp;

	tmp = NULL;
	if (!(*line = ft_strsub(*save, 0, *endl_pos - *save)))
		return (-1);
	if (**endl_pos == '\n')
	{
		if (!(tmp = ft_strdup(*endl_pos + 1)))
			return (-1);
	}
	ft_strdel(&*save);
	*save = tmp;
	return (1);
}

static int	ft_stock(int fd, char **save)
{
	char	buff[BUFF_SIZE + 1];
	char	*new_str;
	int		ret_read;

	ft_bzero(buff, BUFF_SIZE + 1);
	if ((ret_read = read(fd, buff, BUFF_SIZE)))
	{
		if (!(new_str = ft_strjoin(*save, buff)))
			return (-1);
		ft_strdel(&*save);
		*save = new_str;
	}
	return (ret_read);
}

int			get_next_line(const int fd, char **line)
{
	static *t_list;
	static char *save = NULL;
	char		*endl_pos;
	int			ret_read;

	if (!save && !(save = ft_strnew(0)))
		return (-1);
	endl_pos = ft_strchr(save, '\n');
	while (!endl_pos)
	{
		if ((ret_read = ft_stock(fd, &save)) == 0)
		{
			if ((endl_pos = ft_strchr(save, '\0')) == save)
			{
				ft_strdel(&save);
				return (0);
			}
		}
		else if (ret_read == -1)
		{
			ft_strdel(&save);
			return (-1);
		}
		else
			endl_pos = ft_strchr(save, '\n');
	}
	return (ft_get_line(line, &save, &endl_pos));
}
