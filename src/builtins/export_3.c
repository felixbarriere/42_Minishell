/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:01:15 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/23 16:18:17 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	is_in_env(char	*key, t_env	*list)
{
	t_env	*temp;

	temp = list;
	while (list != NULL)
	{
		if (!ft_strcmp(key, list->key))
		{
			list = temp;
			return (1);
		}
		list = list->next;
	}
	list = temp;
	return (0);
}
