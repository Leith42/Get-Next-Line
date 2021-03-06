/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazri <aazri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 15:09:19 by aazri             #+#    #+#             */
/*   Updated: 2017/01/07 20:21:20 by leith            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new_list)
{
	if (alst && new_list)
	{
		new_list->next = *alst;
		*alst = new_list;
	}
}
