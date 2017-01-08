/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/08 23:49:39 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char const *argv[])
{
	char *line = NULL;
	int fd;

	if(argc != 2)
		exit(0);
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &line))
	{
		puts(line);
		ft_strdel(&line);
	}
	close(fd);
	return 0;
}

static int	ft_stock(char **line, char **ret, char **endl_pos)
{
	if(!(*line = ft_strsub(*ret, 0, *endl_pos - *ret)))
		return (-1);
//	free(*ret);
	/*while(**endl_pos == '\n')
		*endl_pos += 1;*/
	if(!(*ret = ft_strdup(*endl_pos + 1)))
		return (-1);
	return (1);
}

static int	ft_read(int fd, char **ret)
{
	char	buff[BUFF_SIZE + 1];
	int	ret_read;
	char *new_str;

	if((ret_read = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret_read] = '\0';
		if(!(new_str = ft_strjoin(*ret, buff)))
			return (-1);
		//free(*ret);
		*ret = new_str;
	}
	return (ret_read);
}

int	get_next_line(const int fd, char **line)
{
	static char *ret = NULL;
	char *endl_pos;
	int ret_read;

	if (!ret)
	{
		if(!(ret = ft_strnew(0)))
			return (-1);
	}
	while(!(endl_pos = ft_strchr(ret, '\n')))
	{
		if((ret_read = ft_read(fd, &ret)) == 0)
		{
			if((endl_pos = ft_strchr(ret, '\0')) == ret)
			{
				free(ret);
				return (0);
			}
		}
		else if(ret_read < 0)
		{
			free(ret);
			return (-1);
		}
	}
	return (ft_stock(line, &ret, &endl_pos));
}
