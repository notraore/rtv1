/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 13:27:55 by notraore          #+#    #+#             */
/*   Updated: 2017/06/05 19:14:15 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list *tmp = lst;
	int		stc;

	while (tmp && tmp->next)
	{
		if ((*cmp)(tmp->data, tmp->next->data) == 0)
		{
			stc = tmp->data;
			tmp->data = tmp->next->data;
			tmp->next->data = stc;
			tmp = lst;
		}
		else
			tmp = tmp->next;
	}
	return (lst);
}
