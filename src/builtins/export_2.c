/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/15 14:40:55 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]) == 0)
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	update_path_export(t_sh *sh, char *key)
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
