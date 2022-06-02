/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:54:27 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/02 15:58:16 by fbarrier         ###   ########.fr       */
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
	// printf("%s\n", elem->value);
	// printf("ADRESS = %p\n", elem->value);
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
	while (elem->token)
	{
		tmp = (elem->token)->next;
		// free(elem->token->value);
		free(elem->token);
		elem->token = tmp;
	}
	// free(elem->token->value);
	// free(elem->token);
	// clear_list(elem->token);
	// free(elem->cmd);
	// free(elem);
}

void	clear_list_pipe(t_pipe *a_list)
{
	t_pipe	*tmp;

	if (!(a_list))
		return ;
	free(a_list->cmd);
	while (a_list)
	{
		tmp = (a_list)->next;
		// free(a_list);
		ft_set_null_free_elem_pipe(a_list);
		// clear_list(a_list->token);
		free(a_list);
		a_list = tmp;
	}
}