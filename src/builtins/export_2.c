/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/05 16:08:21 by marvin           ###   ########.fr       */
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
