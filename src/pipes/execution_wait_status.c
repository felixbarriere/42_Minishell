/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_wait_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 13:45:30 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	wait_get_status3(t_pipe *start, t_sh *sh)
{
	if (start->pid != -1 && (0 < waitpid(start->pid, &sh->exit, 0))
		&& start->cmd_verified)
		sh->exit = WEXITSTATUS(sh->exit);
	while (sh->exit > 255)
		sh->exit = sh->exit % 255;
}

void	wait_get_status2(int nb_cmds, t_sh *sh)
{
	if (nb_cmds > 1)
		sh->exit = 0;
	else
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		sh->exit = 131;
	}
}

void	err_mess(t_sh *sh)
{
	ft_putstr_fd("\n", 2);
	sh->exit = 0;
}

void	wait_get_status(t_sh *sh, int nb_pipes)
{
	int		i;
	t_pipe	*start;

	start = sh->pipe_lst;
	i = 0;
	while (i < (nb_pipes + 1))
	{
		waitpid(start->pid, &sh->exit, 0);
		if (sh->exec_nb_cmds_valids - 1 == nb_pipes && WIFSIGNALED(sh->exit)
			&& WTERMSIG(sh->exit) == 2)
		{
			err_mess(sh);
			break ;
		}
		else if (sh->exec_nb_cmds_valids -1 == nb_pipes
			&& WIFSIGNALED(sh->exit) && WTERMSIG(sh->exit) == 3)
		{
			sh->exit = 0;
			break ;
		}
		wait_get_status3(start, sh);
		i++;
		start = start->next;
	}
}

// void	wait_get_status(t_sh *sh, int nb_pipes)
// {
// 	int		i;
// 	int		status;
// 	int		nb_cmds;
// 	t_pipe	*start;

// 	status = 0;
// 	start = sh->pipe_lst;
// 	nb_cmds = nb_pipes + 1;
// 	i = 0;
// 	while (i < nb_cmds)
// 	{
// 		if (start->pid != -1 && (0 < waitpid(start->pid, &status, 0))
// 			&& start->cmd_verified)
// 			sh->exit = WEXITSTATUS(status);
// 		if (!ft_strcmp(start->cmd, "cat"))
// 			control_sigquit(sh);
// 		i++;
// 		start = start->next;
// 	}
// }

// void	control_sigquit(t_sh *sh)
// {
// 	if (WIFSIGNALED(sh->exit))
// 	{
// 		if (WTERMSIG(sh->exit) == 2)
// 		{
// 			sh->error = 1;
// 			sh->exit = 130;
// 			ft_putstr_fd("\n", 1);
// 		}
// 		else if (WTERMSIG(sh->exit) == 3)
// 		{
// 			ft_putstr_fd("Quit (core dumped)\n", 2);
// 			sh->error = 1;
// 			sh->exit = 131;
// 		}
// 	}
// }