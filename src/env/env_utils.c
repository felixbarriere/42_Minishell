/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:53:47 by fbarrier          #+#    #+#             */
/*   Updated: 2022/05/27 18:18:56 by fbarrier         ###   ########.fr       */
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
