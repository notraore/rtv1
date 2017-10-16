/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:48:13 by notraore          #+#    #+#             */
/*   Updated: 2017/05/26 13:48:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct				s_list
{
	struct s_list *next;
	void          *data;
}							t_list;
