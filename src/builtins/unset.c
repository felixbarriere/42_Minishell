/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/05 16:12:36 by marvin           ###   ########.fr       */
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

void	update_path(t_sh *sh, char *key)
{
	int	i;

	i = 0;
	if (!ft_strcmp(key, "PATH"))
	{
		printf("test\n");
		printf("path avant :%s\n", sh->path[0]);
		while (sh->path[i])
		{
			free(sh->path[i]);
			i++;
		}
		free(sh->path[i]);
		free(sh->path);
		sh->path = NULL;
		if (sh->path)
			printf("path avant :%s\n", sh->path[0]);
	}
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
				update_path(sh, sh->env_lst->key);
				delete_env(sh->env_lst);
				break ;
			}
			sh->env_lst = sh->env_lst->next;
		}
		sh->env_lst = start;
		i++;
	}
}
