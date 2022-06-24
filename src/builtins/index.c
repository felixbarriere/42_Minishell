/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:12:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/24 15:18:52 by ccalas           ###   ########.fr       */
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
}