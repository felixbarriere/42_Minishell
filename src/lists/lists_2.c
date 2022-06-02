/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:51:18 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/02 11:35:45 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

t_token	*new_list(void)
{
	return (NULL);
}

t_env	*new_list_env(void)
{
	return (NULL);
}

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
