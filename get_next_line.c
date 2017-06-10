/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/03/24 15:00:00 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_line(char **line, char **save, char **endl)
{
	char *tmp;

	tmp = NULL;
	if (!(*line = ft_strndup(*save, ft_strlen(*save) - ft_strlen(*endl))))
		return (-1);
	if (**endl == '\n')
	{
		if (!(tmp = ft_strdup(*endl + 1)))
			return (-1);
	}
	ft_strdel(&*save);
	*save = tmp;
	return (1);
}

static int	ft_stock(const int fd, char **save)
{
	char	buff[GNL_BUFF_SIZE + 1];
	char	*tmp;
	int		ret_read;

	ft_bzero(buff, GNL_BUFF_SIZE + 1);
	if ((ret_read = read(fd, buff, GNL_BUFF_SIZE)))
	{
		if (!(tmp = ft_strjoin(*save, buff)))
			return (-1);
		ft_strdel(&*save);
		*save = tmp;
	}
	return (ret_read);
}

int			get_next_line(const int fd, char **line)
{
	static char *save = NULL;
	char		*endl;
	int			ret_read;

	if (!(save) && (!(save = ft_strnew(0))))
		return (-1);
	endl = ft_strchr(save, '\n');
	while (!endl)
	{
		if ((ret_read = ft_stock(fd, &save)) == 0)
		{
			if ((endl = ft_strchr(save, '\0')) == save)
			{
				ft_strdel(&save);
				return (0);
			}
		}
		else if (ret_read == -1)
			return (-1);
		else
			endl = ft_strchr(save, '\n');
	}
	return (ft_get_line(line, &save, &endl));
}
