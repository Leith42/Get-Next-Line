/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:39 by aazri             #+#    #+#             */
/*   Updated: 2017/01/16 20:52:54 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*int main(int argc, char const *argv[])
{
	int fd1;
	int fd2;
	int *fd;

	char *line;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd = &fd1;
	while(get_next_line(*fd, &line))
	{
		printf("%s | %d\n", line, *fd);
		ft_strdel(&line);
		if(fd == &fd1)
			fd = &fd2;
		else
			fd = &fd1;
	}
	close(fd1);
	close(fd2);
	return 0;
}*/

static int	ft_get_line(char **line, t_save **save, char **endl)
{
	char *tmp;

	tmp = NULL;
	if (!(*line = ft_strsub((*save)->data, 0, *endl - (*save)->data)))
		return (-1);
	if (**endl == '\n')
	{
		if (!(tmp = ft_strdup(*endl + 1)))
			return (-1);
	}
	ft_strdel(&(*save)->data);
	(*save)->data = tmp;
	return (1);
}

static int	ft_stock(const int fd, t_save **save)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret_read;

	ft_bzero(buff, BUFF_SIZE + 1);
	if ((ret_read = read(fd, buff, BUFF_SIZE)))
	{
		if (!(tmp = ft_strjoin((*save)->data, buff)))
			return (-1);
		ft_strdel(&(*save)->data);
		(*save)->data = tmp;
	}
	return (ret_read);
}

t_save		*search_fd(t_save **save, const int fd)
{
	t_save *tmp;

	tmp = *save;
	while(tmp)
	{
		if(fd == tmp->fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = *save;
	while(tmp)
	{
		if(fd == tmp->fd)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

int			manage_list(t_save **save, const int fd)
{
	t_save *tmp = NULL;

	if (!*save)
	{
		(*save) = (t_save *)malloc(sizeof(t_save));
		(*save)->data = ft_strnew(0);
		(*save)->fd = fd;
		(*save)->next = NULL;
		(*save)->prev = NULL;
	}
	else if ((fd != (*save)->fd) && (!(tmp = search_fd(save, fd))))
	{
		(*save)->next = (t_save *)malloc(sizeof(t_save));
		(*save)->next->data = ft_strnew(0);
		(*save)->next->fd = fd;
		(*save)->next->prev = *save;
		(*save) = (*save)->next;
		(*save)->next = NULL;
	}
	if(tmp)
		*save = tmp;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_save	*save;
	char			*endl = NULL;
	int				ret_read;

	if(!manage_list(&save, fd))
		return (-1);
	endl = ft_strchr(save->data, '\n');
	while (!endl)
	{
		if ((ret_read = ft_stock(fd, &save)) == 0)
		{
			if ((endl = ft_strchr(save->data, '\0')) == save->data)
			{
				ft_strdel(&save->data);
				free(save);
				return (0);
			}
		}
		else if (ret_read == -1)
			return (-1);
		else
			endl = ft_strchr(save->data, '\n');
	}
	return (ft_get_line(line, &save, &endl));
}
