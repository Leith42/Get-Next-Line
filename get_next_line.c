/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/02 19:03:50 by leith            ###   ########.fr       */
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
	while(get_next_line(fd, &line))
	{
		puts(line);
		//free(line);
	}
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

static char *ft_search(char **line, char *buff, char *rest)
{
	size_t i;
	char buff_tmp[BUFF_SIZE + 1] = "\0";
	//static char *rest = NULL;

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
		return (rest);
	return (NULL);
}

int	get_next_line(const int fd, char **line)
{
	char *buff;
	static char *rest = NULL;
	//char buff_tab[BUFF_SIZE + 1] = "\0";

	*line = ft_strnew(BUFF_SIZE);
	buff = ft_strnew(BUFF_SIZE);
	while((read(fd, &*buff, BUFF_SIZE)))
	{
		if((rest = ft_search(line, buff, rest)))
		{
			free(buff);
			return (1);
		}
	}
	if(rest[0])
	{
		ft_strcpy(*line, rest);
		free(buff);
		free(rest);
		return (1);
	}
	free(buff);
	return (0);
}
