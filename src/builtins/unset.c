/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/24 14:34:49 by fbarrier         ###   ########.fr       */
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
	// env_lst->next = env_lst;
}

void	unset_command(t_sh *sh)
{
	t_env	*start;
	int		i;

	i = 0;
	start = sh->env_lst;
	printf("unset command\n");
	printf("cmd ==> %s\n", sh->pipe_lst->cmd);

	while (sh->pipe_lst->args[i])
	{
		printf("option\n");
		while(sh->env_lst)
		{
			if (!ft_strcmp(sh->pipe_lst->args[i], sh->env_lst->key))
			{
				// printf("key ==> %s\n", sh->env_lst->key);
				// printf("key next ==> %s\n", sh->env_lst->next->key);
				// printf("key prev ==> %s\n", sh->env_lst->prev->key);
				delete_env(sh->env_lst);
				break;
			}
			sh->env_lst = sh->env_lst->next;
		}
		sh->env_lst = start;
		i++;
	}
}

// gerer plusieurs agruments


// int i = 1;
// while(sh->pipe_lst->args[i])
// {
// 	printf("options ==> %s\n", sh->pipe_lst->args[i]);
// 	i++;
// }