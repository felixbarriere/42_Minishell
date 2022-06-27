/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/27 19:58:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	delete_env(t_env	*env_lst)
{
	env_lst->prev->next = env_lst->next;
	free(env_lst->key);
	free(env_lst->value);
	free(env_lst);
}

void	update_path(t_sh	*sh)
{
	t_env	*temp;

	temp = sh->env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH"))
		{
			// printf("temp->value: %s\n", temp->value);
			// sh->path = NULL;
			temp = temp->next;
		}
		else
			return ;
	}
	printf("test\n");
	ft_free(sh->path);
	printf("sh->path: %s\n", sh->path[1]);
}

void	unset_command(t_sh *sh)
{
	t_env	*start;
	int		i;

	i = 0;
	start = sh->env_lst;
	while (sh->pipe_lst->args[i])
	{
		while (sh->env_lst)
		{
			if (!ft_strcmp(sh->pipe_lst->args[i], sh->env_lst->key))
			{
				delete_env(sh->env_lst);
				update_path(sh);
				break ;
			}
			sh->env_lst = sh->env_lst->next;
		}
		sh->env_lst = start;
		i++;
	}
}
