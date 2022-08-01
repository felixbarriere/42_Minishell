/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:12:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 18:21:00 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// void	index_builtins(t_pistart)
// {
// 	if (!ft_strstart->cmd, "cd"))
// 		cd_command(sh);
// 	else if (!ft_strstart->cmd, "pwd"))
// 		pwd_commstart);
// 	else if (!ft_strstart->cmd, "echo"))
// 		echo_commstart);
// 	else if (!ft_strstart->cmd, "env"))
// 		env_command(sh);
// 	else if (!ft_strstart->cmd, "export"))
// 		export_command(sh);
// 	else if (!ft_strstart->cmd, "unset"))
// 		unset_command(sh);
// 	else if (!prompt || !ft_strstart->cmd, "exit"))
// 		exit_command(sh);
// }

void	index_builtins(t_sh	*sh, t_pipe *start)
{
	if (!ft_strcmp(start->cmd, "cd"))
		cd_command(sh, start);
	else if (!ft_strcmp(start->cmd, "pwd"))
		pwd_command(sh, start);
	else if (!ft_strcmp(start->cmd, "echo"))
		echo_command(sh, start);
	else if (!ft_strcmp(start->cmd, "env"))
		env_command(sh, start);
	else if (!ft_strcmp(start->cmd, "export"))
		export_command(sh, start);
	else if (!ft_strcmp(start->cmd, "unset"))
		unset_command(sh, start);
	else if (!sh->prompt || !ft_strcmp(start->cmd, "exit"))
		exit_command(sh, start);
}
