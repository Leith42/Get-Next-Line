/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:53 by aazri             #+#    #+#             */
/*   Updated: 2017/01/13 14:52:41 by aazri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 64

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_save
{
	int				fd;
	char 			*save;
	struct s_save 	*next_fd;
	struct s_save	*previous_fd;
}				t_save;

int	get_next_line(const int fd, char **line);

#endif
