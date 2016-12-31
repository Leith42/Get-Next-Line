/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2016/12/31 18:10:53 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char const *argv[])
{
	char *line;
	int fd;

	if(argc != 2)
		exit(0);
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &line));
	return 0;
}

static char *ft_rest(char *buff, size_t b)
{
	int i;
	char *rest;

	i = 0;
	rest = ft_strnew(BUFF_SIZE);
	if(buff[b])
	{
		while(buff[b] == '\n')
			b++;
		while(buff[b] && buff[b] != '\n' && buff[b] != EOF)
		{
			rest[i] = buff[b];
			i++;
			b++;
		}
	}
	return (rest);
}

static int ft_search(char **line, char *buff, int rd)
{
	size_t i;
	char buff_tmp[BUFF_SIZE + 1] = "\0";
	static char *rest = NULL;

	i = 0;
	while(buff[i] && buff[i] != '\n' && buff[i] != EOF)
	{
		buff_tmp[i] = buff[i];
		i++;
	}
	if(rest)
	{
		*line = ft_strjoin(*line, rest);
		free(rest);
	}
	rest = ft_rest(buff, i);
	*line = ft_strjoin(*line, buff_tmp);
	if(buff[i] == '\n')
		return (0);
	return(1);
}

int	get_next_line(const int fd, char **line)
{
	int rd;
	char *buff;

	*line = ft_strnew(BUFF_SIZE);
	buff = ft_strnew(BUFF_SIZE);
	while((rd = read(fd, &*buff, BUFF_SIZE)))
	{
		if(!(ft_search(line, buff, rd)))
		{
			puts(*line);
			free(buff);
			return (1);
		}
	}
	//ft_search(line, buff, rd);
	free(buff);
	return (0);
}
