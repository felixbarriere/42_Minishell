/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/31 14:58:25 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	execution_pipe3(t_sh *sh)
{
	if (sh->exec_pipe_k % 2 != 0)
		sh->exec_pipe_i++;
	sh->exec_pipe_k++;
}

void	exec2(t_pipe *start, t_sh *sh, int nb_pipes, char **env_init)
{
	signal(SIGINT, SIG_IGN);
	start->pid = fork();
	if (start->pid == -1)
		return ;
	if (start->pid == 0)
	{
		ft_signals_orchestrator(1);
		ft_close(sh, nb_pipes);
		if (start->is_builtin == 1)
		{
			index_builtins(sh, start);
			free_free_all(sh);
			exit(sh->exit);
		}
		else if (start->cmd_verified != NULL)
			execve(start->cmd_verified, start->args, env_init);
		else
		{
			mess_cmd_not_found(sh, start->cmd);
			free_free_all(sh);
			exit (sh->exit);
		}
		free_free_all(sh);
	}
	reset_input_output(start);
}

void	execution_pipe2(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init)
{
	if (start->is_builtin == 1)
	{	
		if (!ft_strcmp(start->cmd, "env") || !ft_strcmp(start->cmd, "export")
			|| !ft_strcmp(start->cmd, "unset"))
		{
			if (sh->exit == 127)
				sh->exit = 0;
			index_builtins(sh, start);
			reset_input_output(start);
		}
		else
			exec2(start, sh, nb_pipes, env_init);
	}	
	else
		exec2(start, sh, nb_pipes, env_init);
	sh->exec_nb_cmds_valids++;
}

void	execution_pipe_init(t_sh *sh, t_pipe *start, int nb_pipes)
{
	sh->exec_pipe_k = 0;
	sh->exec_pipe_i = 0;
	sh->exec_nb_cmds_valids = 0;
	init_pipe(start, nb_pipes);
}

void	execution_pipe(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init)
{
	execution_pipe_init(sh, start, nb_pipes);
	while (start)
	{
		if (start->pipe_ok == 1)
		{
			start->pipe_ok = 0;
			start = start->next;
			continue ;
		}
		update_input_output(start);
		ft_switch(start, sh->exec_pipe_k);
		if (start->is_builtin != 1 && start->cmd_verified == NULL)
		{
			start->cmd_ok = 1;
			mess_cmd_not_found(sh, start->cmd);
			reset_input_output(sh->pipe_lst);
			start = start->next;
			continue ;
		}
		execution_pipe2(sh, start, nb_pipes, env_init);
		execution_pipe3(sh);
		start = start->next;
	}
	ft_close(sh, nb_pipes);
	wait_get_status(sh, nb_pipes);
}
