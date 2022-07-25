/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/25 11:41:24 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	execution_pipe3(t_sh *sh)
{
	if (sh->exec_pipe_k % 2 != 0)
		sh->exec_pipe_i++;
	sh->exec_pipe_k++;
}

void	control_sigquit(t_sh *sh)
{
	if (WIFSIGNALED(sh->exit))
	{
		if (WTERMSIG(sh->exit) == 2)
		{
			sh->error = 1;
			sh->exit = 130;
			ft_putstr_fd("\n", 1);
		}
		else if (WTERMSIG(sh->exit) == 3)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			sh->error = 1;
			sh->exit = 131;
		}
	}
}

void	wait_get_status(t_sh *sh, int nb_pipes, int pid)
{
	int	i;
	int	nb_cmds;

	nb_cmds = nb_pipes + 1;
	i = 0;
	while (i < nb_cmds)
	{
		if ((0 < waitpid(pid, &sh->exit, 0)) && (WIFEXITED(sh->exit)))
			sh->exit = WEXITSTATUS(sh->exit);
		i++;
	}
	control_sigquit(sh);
}
