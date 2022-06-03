/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:53:47 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/03 15:20:15 by fbarrier         ###   ########.fr       */
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
		list = tmp;
	}
}

void	get_path(t_sh	*sh)
{
	t_env	*temp;

	temp = sh->env_lst;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PATH"))
			sh->path = ft_split(temp->value, ':');
		temp = temp->next;
	}
}
