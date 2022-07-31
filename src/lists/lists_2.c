/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:51:18 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/31 14:00:18 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_env	*new_list_env(void)
{
	return (NULL);
}

bool	is_empty_list(t_token *li)
{
	if (li == NULL)
		return (true);
	return (false);
}

bool	is_empty_list_env(t_env *li)
{
	if (li == NULL)
		return (true);
	return (false);
}

void	ft_set_null_free_elem_pipe(t_pipe *elem)
{
	t_token	*tmp;
	int		i;

	if (!(elem))
		return ;
	i = 0;
	if (elem->args)
	{
		while (elem->args[i])
			free(elem->args[i++]);
		free(elem->args[i]);
		free (elem->args);
	}
	if (elem->cmd)
		free(elem->cmd);
	if (elem->limiter_name)
		free(elem->limiter_name);
	if (elem->cmd_verified)
		free(elem->cmd_verified);
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
