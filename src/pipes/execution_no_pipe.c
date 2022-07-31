/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/31 15:15:48 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	wait_get_status_no_pipe(t_sh *sh)
{
	t_pipe	*start;

	start = sh->pipe_lst;
	waitpid(start->pid, &sh->exit, 0);
	if ((sh->exit) && WTERMSIG(sh->exit) == 2)
	{
		ft_putstr_fd("\n", 2);
		sh->exit = 130;
	}
	else if (WIFSIGNALED(sh->exit) && WTERMSIG(sh->exit) == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		sh->exit = 131;
	}
	if (start->pid != -1 && (0 < waitpid(start->pid, &sh->exit, 0))
		&& start->cmd)
		sh->exit = WEXITSTATUS(sh->exit);
	while (sh->exit > 255)
		sh->exit = sh->exit % 255;
}

void	no_pipe_exec(t_sh *sh, char **env_init)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		ft_signals_orchestrator(1);
		execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
		free_free_all(sh);
		exit(sh->exit);
	}
	wait_get_status_no_pipe(sh);
	ft_signals_orchestrator(0);
}
