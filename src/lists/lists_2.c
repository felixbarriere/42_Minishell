/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:51:18 by fbarrier          #+#    #+#             */
/*   Updated: 2022/05/30 16:09:47 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

bool	is_empty_list(t_token *li)
{
	if (li == NULL)
		return (true);
	return (false);
}

bool	is_empty_list_env(t_env *li)
{
	if (li == NULL)
		return (true);
	return (false);
}

void	ft_set_null_free_elem_2(t_token *elem)
{
	if (!elem)
		return ;
	// printf("%s\n", elem->value);
	// printf("ADRESS = %p\n", elem->value);
	if (ft_strcmp(elem->value, "<<") && ft_strcmp(elem->value, ">>")
		&& ft_strcmp(elem->value, "<") && ft_strcmp(elem->value, ">")
		&& ft_strcmp(elem->value, "|"))
		free(elem->value);
	free(elem);
}
