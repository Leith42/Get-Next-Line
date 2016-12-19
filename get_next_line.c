/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2016/12/19 17:10:09 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char**	get_next_line(const int fd, char **line);

int main(int argc, char const *argv[])
{
	char **line = NULL;
	if(argc != 2)
		exit(0);
	get_next_line(open(argv[1], O_RDONLY), line);
	//printf("%s", *line);
	return 0;
}

char	**get_next_line(const int fd, char **line)
{
	size_t i = 0;
	size_t buff_tmp = BUFF_SIZE;
	char buff[BUFF_SIZE];

	while(read(fd, &buff[i], 1) && i < BUFF_SIZE && buff[i] != '\n')
	{
		buff_tmp--;
		i++;
	}
	buff[i] = 0;
	printf("%s", buff);
	return (line);
}
