/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:12:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/26 16:37:35 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	index_builtins(t_sh	*sh)
{
	if (!ft_strcmp(sh->pipe_lst->cmd, "cd"))
		cd_command(sh);
	else if (!ft_strcmp(sh->pipe_lst->cmd, "pwd"))
		pwd_command(sh->pipe_lst);
	else if (!ft_strcmp(sh->pipe_lst->cmd, "echo"))
		echo_command(sh->pipe_lst);
	else if (!ft_strcmp(sh->pipe_lst->cmd, "env"))
		env_command(sh);
	else if (!ft_strcmp(sh->pipe_lst->cmd, "export"))
		export_command(sh);
	else if (!ft_strcmp(sh->pipe_lst->cmd, "unset"))
		unset_command(sh);
	else if (!sh->prompt || !ft_strcmp(sh->pipe_lst->cmd, "exit"))
		exit_command(sh);
}
