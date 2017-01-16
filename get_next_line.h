/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:39:53 by aazri             #+#    #+#             */
/*   Updated: 2017/01/14 13:30:25 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 256

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int	get_next_line(const int fd, char **line);

#endif
