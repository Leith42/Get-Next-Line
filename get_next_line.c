/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/03 15:10:33 by aazri            ###   ########.fr       */
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
		puts(line);
	return 0;
}

static char *ft_stock_rest(char *buff, size_t b)
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
	else
	{
		free(rest);
		rest = NULL;
	}
	return (rest);
}

static char *ft_stock_line(char **line, char buff[], char *rest)
{
	size_t i;
	char buff_tmp[BUFF_SIZE + 1] = "\0";

	i = 0;
	while(buff[i] && buff[i] != '\n')
	{
		buff_tmp[i] = buff[i];
		i++;
	}
	if(rest)
	{
		*line = ft_strjoin(*line, rest);
		free(rest);
	}
	rest = ft_stock_rest(buff, i);
	*line = ft_strjoin(*line, buff_tmp);
	if(buff[i] == '\n' && rest)
		return (rest);
	return (NULL);
}

static int	ft_count_endl(char buff[])
{
	size_t i;
	size_t endl;

	i = 0;
	endl = 0;
	while(buff[i])
	{
		if(buff[i] == '\n')
			endl++;
		i++;
	}
	return (endl);
}

int	get_next_line(const int fd, char **line)
{
	static char *rest = NULL;
	char buffer[BUFF_SIZE + 1] = "\0";
	size_t endl;

	*line = ft_strnew(BUFF_SIZE);
	while((read(fd, buffer, BUFF_SIZE)))
	{
		if((rest = ft_stock_line(line, buffer, rest)))
			return (1);
	}
	/*if(rest)
	{
		ft_strcpy(*line, rest);
		free(rest);
		rest = NULL;
		return (1);
	}*/
	return (0);
}
