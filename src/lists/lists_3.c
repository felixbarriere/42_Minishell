/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:54:27 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/27 14:59:12 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_token	*new_list(void)
{
	return (NULL);
}

void	ft_set_null_free_elem(t_env *elem)
{
	if (elem)
	{
		if (elem->key)
			free(elem->key);
		if (elem->value)
			free(elem->value);
		if (elem->full)
			free(elem->full);
		if (elem)
			free(elem);
	}
}

void	clear_list_env(t_env *a_list)
{
	t_env	*tmp;

	if (!(a_list))
		return ;
	while (a_list != NULL)
	{
		tmp = (a_list)->next;
		ft_set_null_free_elem(a_list);
		a_list = tmp;
	}
	ft_set_null_free_elem(tmp);
}

/********************************************************************/

void	ft_set_null_free_elem_2(t_token *elem)
{
	if (!elem)
		return ;
	if (ft_strcmp(elem->value, "<<") && ft_strcmp(elem->value, ">>")
		&& ft_strcmp(elem->value, "<") && ft_strcmp(elem->value, ">")
		&& ft_strcmp(elem->value, "|"))
		free(elem->value);
	free(elem);
}

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
