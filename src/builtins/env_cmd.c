/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:55:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 13:00:49 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	ft_strchr2(const char *str, int to_find_char)
{
	while (*str && *str != (char)to_find_char)
		str++;
	if (*str == (char)to_find_char)
		return (1);
	return (0);
}

void	env_command(t_sh	*sh, t_pipe *pipe_lst)
{
	t_env	*start;

	start = sh->env_lst;
	if (pipe_lst->args[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(pipe_lst->args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		sh->exit = 127;
		return ;
	}
	while (sh->env_lst != NULL)
	{
		if (sh->env_lst->key)
		{
			ft_putstr_fd(sh->env_lst->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(sh->env_lst->value, 1);
			ft_putchar_fd('\n', 1);
		}
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = start;
	sh->exit = 0;
}

void	env_command_export(t_sh	*sh)
{
	t_env	*start;

	start = sh->env_lst;
	while (sh->env_lst != NULL)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(sh->env_lst->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(sh->env_lst->value, 1);
		ft_putstr_fd("\"\n", 1);
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = start;
}
