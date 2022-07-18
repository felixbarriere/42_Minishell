/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:59:40 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/18 16:17:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

pid_t	exec2(t_pipe *start, t_sh *sh, int nb_pipes, char **env_init)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_close(sh, nb_pipes);
		if (start->is_builtin == 1)
		{
			index_builtins(sh, start);
			exit(0);
		}
		else if (start->cmd_verified != NULL)
			execve(start->cmd_verified, start->args, env_init);
		else
			exit (0);
	}
	reset_input_output(start);
	return (pid);
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
}

void	execution_pipe(t_sh *sh, int nb_pipes, char **env_init)
{
	t_pipe	*start;
	pid_t	pid;

	sh->exec_pipe_i = 0;
	sh->exec_pipe_k = 0;
	start = sh->pipe_lst;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, sh->exec_pipe_k);
		if (sh->pipe_lst->is_builtin != 1 && sh->pipe_lst->cmd_verified == NULL)
		{
			mess_cmd_not_found(sh, sh->pipe_lst->cmd);
			reset_input_output(sh->pipe_lst);
			return ;
		}
		else
			pid = exec2(start, sh, nb_pipes, env_init);
		if (sh->exec_pipe_k % 2 != 0)
			sh->exec_pipe_i++;
		sh->exec_pipe_k++;
		start = start->next;
	}
	ft_close(sh, nb_pipes);
	wait_get_status(sh, nb_pipes, pid);
}

void	no_pipe_exec(t_sh *sh, char **env_init)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
			g_sh.exit = WEXITSTATUS(g_sh.exit);
}

void	execution(t_sh *sh, char **env_init)
{
	int		nb_pipes;
	t_pipe	*start;

	start = sh->pipe_lst;
	nb_pipes = nb_pipe(sh->pipe_lst);
	fprintf(stderr, "nb de pipes = %d\n", nb_pipes);
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
		execution_pipe(sh, nb_pipes, env_init);
}
