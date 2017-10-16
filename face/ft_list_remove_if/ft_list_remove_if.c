/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:36:09 by notraore          #+#    #+#             */
/*   Updated: 2017/05/29 13:27:36 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{

	t_list *tmp;

	if (*begin_list)
	{
		if (cmp((*begin_list->data, data_ref) == 0))
		{
			tmp = *begin_list;
			(*begin_list) = (*begin_list)->next;
			free(tmp);
			ft_list_remove_if(begin_list, data_ref, cmp);
		}
	}
	else
		ft_list(&((begin_list)->next), data_ref, cmp);
}

