/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:53:47 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/02 17:59:29 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	str = NULL;
}

void	ft_free_2(char *str)
{
	free(str);
	str = NULL;
}

void	ft_free_3(t_env *list)
{
	t_env	*tmp;

	printf("test leaks");
	while (list)
	{
		tmp = list->next;
		free(list);
		// free(list->key);
		// free(list->value);
		// free(list->full);
		list = tmp;
	}
}

void	get_path(t_sh	*sh)
{
	// char *path_to_split;
	int i = 0;
	
	while (sh->env_lst)
	{
		if (!ft_strcmp(sh->env_lst->key, "PATH"))
		{
			printf("success\n");
			// path_to_split = ft_strdup();
			sh->path = ft_split(sh->env_lst->value, ':');
		}
		sh->env_lst = sh->env_lst->next;
	}
	// while(sh->path[i])
	// {
	// 	printf("%s\n",sh->path[i]);
	// 	i++;
	// }
}
