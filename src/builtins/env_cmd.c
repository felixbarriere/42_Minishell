/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:55:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/22 16:05:06 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	env_command(t_sh	*sh)
{
	t_env	*start;

	start = sh->env_lst;
	while (sh->env_lst != NULL)
	{
		ft_putstr_fd(sh->env_lst->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(sh->env_lst->value, 1);
		ft_putchar_fd('\n', 1);
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = start;
}

