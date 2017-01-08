/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:11:12 by aazri             #+#    #+#             */
/*   Updated: 2017/01/08 17:16:51 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int letter)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == letter)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == letter)
		return ((char *)str + i);
	return (NULL);
}
