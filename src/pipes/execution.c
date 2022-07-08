#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void exec2(t_pipe *start, t_sh *sh, int nb_pipes, char **env_init)
{
	pid_t	pid;

	if (start->is_builtin == 1)
			index_builtins(sh);
	else if (start->cmd_verified != NULL)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			ft_close(sh, nb_pipes);
			execve(start->cmd_verified, start->args, env_init);
		}
		// if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		// 	g_sh.exit = WEXITSTATUS(g_sh.exit);
	}
	else
	{
		mess_cmd_not_found(sh, start->cmd);
		reset_input_output(start);
		return ;
	}
	reset_input_output(start);
}

void	ft_switch(t_pipe *start, int k)
{
	if (!k)
		dup2(start->fd[1], start->output);
	else if (k && !start->next)
		dup2(start->prev->fd[0], start->input);
	else if (k && start->next)
	{
		dup2(start->prev->fd[0], start->input);
		dup2(start->fd[1], start->output);
	}
}

void	execution_pipe(t_sh *sh, int nb_pipes, char **env_init)
{
	int		i;
	int		k;
	t_pipe	*start;

	i = 0;
	k = 0;
	start = sh->pipe_lst;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, k);
		exec2(start, sh, nb_pipes, env_init);
		if (k % 2 != 0)
			i++;
		k++;
		start = start->next;
	}
	ft_close(sh, nb_pipes);
	wait(0);
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

	// print_pipe_tokens(sh->pipe_lst);
	nb_pipes = nb_pipe(sh->pipe_lst);
	fprintf(stderr, "nb de pipes = %d\n", nb_pipes);
	if (nb_pipes == 0)
	{
		update_input_output(sh->pipe_lst);
		if (sh->pipe_lst->is_builtin == 1)
			index_builtins(sh);
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
