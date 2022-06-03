/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:54:27 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/03 18:10:41 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

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

void	ft_set_null_free_elem_pipe(t_pipe *elem)
{
	t_token	*tmp;

	if (!(elem))
		return ;
	free (elem->args);
	free (elem->cmd);
	free (elem->limiter);
	while (elem->token)
	{
		tmp = (elem->token)->next;
		free(elem->token);
		elem->token = tmp;
	}
}

void	clear_list_pipe(t_pipe *a_list)
{
	t_pipe	*tmp;

	if (!(a_list))
		return ;
	while (a_list)
	{
		tmp = (a_list)->next;
		ft_set_null_free_elem_pipe(a_list);
		free(a_list);
		a_list = tmp;
	}
}