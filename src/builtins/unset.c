/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:18:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/28 15:59:00 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// void	delete_env(t_env *env_lst)  //utiliser une temp?
// {
// 	t_env *temp;

// 	temp = env_lst;
// 	if (temp->prev)
// 	{
// 		printf("prev existe\n");
// 		temp->prev->next = temp->next;
// 	}
// 	if (temp->next)
// 	{
// 		printf("next existe\n");
// 		temp->next->prev = temp->prev;
// 	}
// 	printf("test\n");
// 	if (!temp->prev)
// 	{
// 		printf("test2\n");
// 		printf("temp->key: %s\n", temp->key);
// 		temp = temp->next;
// 		printf("test3\n");
// 		printf("temp->key: %s\n", temp->key);
// 		printf("temp->prev->key: %s\n", temp->prev->key);
// 		free(temp->prev->key);
// 		free(temp->prev->value);
// 		free(temp->prev);
// 		env_lst = temp;
// 		return ;
// 	}
// 	free(temp->key);
// 	free(temp->value);
// 	free(temp);
// 	env_lst = temp;
// }

// void	print_tokens_env(t_env *li)
// {
// 	while (li != NULL)
// 	{
// 		printf("\n");
// 		printf("[%s] = [%s]", li->key, li->value);
// 		li = li->next;
// 	}
// 	printf("\n");
// }

// t_env	*remove_first_env(t_env *env_lst, t_sh *sh)
// {
// 	(void)sh;
// 	// (void)env_lst;
// 	t_env	*first;

// 	first = env_lst->next;
// 	// if (env_lst->key)
// 		free(env_lst->key);
// 	// if (env_lst->value)
// 		free(env_lst->value);
// 	// if (env_lst)
// 	// {
// 		free(env_lst);
// 		env_lst = NULL;
// 	// }
// 	// env_lst = first;
// 	return (first);
// }

void	delete_env(t_env *env_lst)
{
	if (!env_lst->prev)
	{
		printf("pas de prev\n");
		env_lst = env_lst->next;
		free (env_lst->prev->key);
		free (env_lst->prev->value);
		free (env_lst->prev);
		env_lst->prev = NULL;
	}
	else
	{
		printf("prev\n");
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
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
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
	return (1);
}

void	unset_command(t_sh *sh)
{
	t_env	*start;
	int		i;

	i = 0;
	start = sh->env_lst;
	while (sh->pipe_lst->args[i])
	{
		while (sh->env_lst && identifier_is_valid(sh->pipe_lst->args[i], sh))
		{
			if (!ft_strcmp(sh->pipe_lst->args[i], sh->env_lst->key))
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
