/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:54:27 by fbarrier          #+#    #+#             */
/*   Updated: 2022/05/27 17:58:39 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	clear_list(t_token *a_list)
{
	t_token	*tmp;

	if (!(a_list))
		return ;
	while (a_list)
	{
		tmp = (a_list)->next;
		ft_set_null_free_elem_2(a_list);
		a_list = tmp;
	}
}

void	ft_set_null_free_elem(t_env *elem)
{
	free(elem->key);
	free(elem->value);
	free(elem->full);
	free(elem);
}

void	clear_list_env(t_env *a_list)
{
	t_env	*tmp;

	while (a_list)
	{
		tmp = (a_list)->next;
		ft_set_null_free_elem(a_list);
		a_list = tmp;
	}
}

t_token	*new_list(void)
{
	return (NULL);
}

t_env	*new_list_env(void)
{
	return (NULL);
}
