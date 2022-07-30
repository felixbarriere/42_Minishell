/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 19:29:04 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	delete_env(t_env *env_lst)
{
	if (!env_lst->prev)
	{
		env_lst = env_lst->next;
		free (env_lst->prev->key);
		free (env_lst->prev->value);
		free (env_lst->prev);
		env_lst->prev = NULL;
	}
	else
	{
		if (env_lst->prev)
		env_lst->prev->next = env_lst->next;
		if (env_lst->next)
			env_lst->next->prev = env_lst->prev;
		free(env_lst->key);
		free(env_lst->value);
		free(env_lst);
	}
}

void	update_path(t_sh *sh, char *key)
{
	int	i;

	i = 0;
	if (!ft_strcmp(key, "PATH"))
	{
		while (sh->path[i])
		{
			free(sh->path[i]);
			i++;
		}
		free(sh->path[i]);
		free(sh->path);
		sh->path = NULL;
	}
}

int	ft_isalnum_2(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| c == ';')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	identifier_is_valid(char *str, t_sh *sh)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[0])
			|| (!ft_isalnum_2(str[i])))
		{
			ft_putstr_fd("unset: \'", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			sh->exit = 1;
			return (0);
		}
		i++;
	}
	sh->exit = 0;
	return (1);
}

void	unset_command(t_sh *sh, t_pipe *pipe_lst)
{
	t_env	*start;
	int		i;

	i = 1;
	start = sh->env_lst;
	while (pipe_lst->args[i])
	{
		while (sh->env_lst && identifier_is_valid(pipe_lst->args[i], sh))
		{
			if (!ft_strcmp(pipe_lst->args[i], sh->env_lst->key))
			{
				if (!sh->env_lst->prev)
					start = start->next;
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

// void	unset_command(t_sh *sh)
// {
// 	t_env	*start;
// 	int		i;

// 	i = 0;
// 	start = sh->env_lst;
// 	while (sh->pipe_lst->args[i])
// 	{
// 		while (sh->env_lst && identifier_is_valid(sh->pipe_lst->args[i], sh))
// 		{
// 			if (!ft_strcmp(sh->pipe_lst->args[i], sh->env_lst->key))
// 			{
// 				update_path(sh, sh->env_lst->key);
// 				delete_env(sh->env_lst, sh);
// 				break ;
// 			}
// 			sh->env_lst = sh->env_lst->next;
// 		}
// 		sh->env_lst = start;
// 		i++;
// 	}
// }
