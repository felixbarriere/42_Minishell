/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 15:37:41 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

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
		if (!ft_strcmp(start->cmd, "export") || !ft_strcmp(start->cmd, "env")
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

void	execution_pipe(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init)
{
	sh->exec_pipe_k = 0;
	sh->exec_pipe_i = 0;
	sh->exec_nb_cmds_valids = 0;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, sh->exec_pipe_k);
		if (start->is_builtin != 1 && start->cmd_verified == NULL)
		{
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
	printf("cmd Valide %d\n", sh->exec_nb_cmds_valids);
	wait_get_status(sh, nb_pipes);
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
	// wait_get_status(sh, 0);
	wait_get_status_no_pipe(sh);
	ft_signals_orchestrator(0);
}

void	execution(t_sh *sh, char **env_init)
{
	int		nb_pipes;
	t_pipe	*start;

	start = sh->pipe_lst;
	nb_pipes = nb_pipe(sh->pipe_lst);
	if (nb_pipes == 0)
	{
		update_input_output(sh->pipe_lst);
		if (sh->pipe_lst->is_builtin == 1)
			index_builtins(sh, start);
		else if (sh->pipe_lst->cmd_verified != NULL)
			no_pipe_exec(sh, env_init);
		else
		{
			mess_cmd_not_found(sh, sh->pipe_lst->cmd);
			reset_input_output(sh->pipe_lst);
			return ;
		}
		reset_input_output(sh->pipe_lst);
	}
	else
		execution_pipe(sh, start, nb_pipes, env_init);
	if (sh->exit == 13)
		sh->exit = 127;
}

/*
void	execution_pipe(t_sh *sh, t_pipe *start, int nb_pipes, char **env_init)
{
	sh->exec_pipe_i = 0;
	sh->exec_pipe_k = 0;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, sh->exec_pipe_k);
		if (!ft_strcmp(start->token->value, "<<"))
		{
			start = start->next;
			reset_input_output(sh->pipe_lst);
			continue ;
		}
		if (start->is_builtin != 1 && start->cmd_verified == NULL)
		{
			mess_cmd_not_found(sh, start->cmd);
			reset_input_output(sh->pipe_lst);
			return ;
		}
		execution_pipe2(sh, start, nb_pipes, env_init);
		execution_pipe3(sh);
		start = start->next;
	}
	ft_close(sh, nb_pipes);
	wait_get_status(sh, nb_pipes, sh->exec_pid);
}
*/