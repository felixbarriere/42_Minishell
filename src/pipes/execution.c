#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

pid_t exec2(t_pipe *start, t_sh *sh, int nb_pipes, char **env_init)
{
	pid_t	pid = 1;

	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0)
	{
		ft_close(sh, nb_pipes);
		if (start->is_builtin == 1)
		{
			index_builtins(sh);
			exit(0);
		}
		else if (start->cmd_verified != NULL)
			execve(start->cmd_verified, start->args, env_init);
	}
	reset_input_output(start);
	return (pid);
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
	int		i;
	int		k;
	t_pipe	*start;
	pid_t	pid;

	i = 0;
	k = 0;
	start = sh->pipe_lst;
	init_pipe(start, nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(start, k);
		printf("2 / is_builtin = %d et cmd = %s\n", sh->pipe_lst->is_builtin, sh->pipe_lst->cmd_verified);
		if (sh->pipe_lst->is_builtin != 1 && sh->pipe_lst->cmd_verified == NULL)
		{
			mess_cmd_not_found(sh, sh->pipe_lst->cmd);
			reset_input_output(sh->pipe_lst);
			return ;
		}
		else
			pid = exec2(start, sh, nb_pipes, env_init);
		if (k % 2 != 0)
			i++;
		k++;
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











//no pipe fork
// void	no_pipe_exec(t_sh *sh, char **env_init)
// {
// 	pid_t	pid;

// 	// le fork include les builltin sauf s'ils modifient l'env donc env + unset + export ajouter condition
// 	if (sh->pipe_lst->is_builtin == 1 && (!ft_strcmp(sh->pipe_lst->cmd, "export")
// 		|| !ft_strcmp(sh->pipe_lst->cmd, "unset")))
// 			index_builtins(sh);
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			return ;
// 		if (pid == 0)
// 		{
// 			if (sh->pipe_lst->is_builtin == 1)
// 			{
// 			index_builtins(sh);
// 			}
// 			else if (sh->pipe_lst->cmd_verified != NULL)
// 				execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
// 		}
// 		if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 				g_sh.exit = WEXITSTATUS(g_sh.exit);
// 		reset_input_output(sh->pipe_lst);
// 	}
// }

// void	execution(t_sh *sh, char **env_init)
// {
// 	int		nb_pipes;

// 	// print_pipe_tokens(sh->pipe_lst);
// 	nb_pipes = nb_pipe(sh->pipe_lst);
// 	fprintf(stderr, "nb de pipes = %d\n", nb_pipes);
// 	if (nb_pipes == 0)
// 	{
// 		update_input_output(sh->pipe_lst);
// 		printf("1 / is_builtin = %d et cmd = %s\n", sh->pipe_lst->is_builtin, sh->pipe_lst->cmd_verified);
// 		if (sh->pipe_lst->is_builtin != 1 && sh->pipe_lst->cmd_verified == NULL)
// 		{
// 			mess_cmd_not_found(sh, sh->pipe_lst->cmd);
// 			reset_input_output(sh->pipe_lst);
// 			return ;
// 		}
// 		else
// 			no_pipe_exec(sh, env_init);
// 		reset_input_output(sh->pipe_lst);
// 	}
// 	else
// 		execution_pipe(sh, nb_pipes, env_init);
// }











// pid_t exec2(t_pipe *start, t_sh *sh, int nb_pipes, char **env_init)
// {
// 	pid_t	pid = 1;

// 	if (start->is_builtin == 1)
// 			index_builtins(sh);
// 	else if (start->cmd_verified != NULL)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			return -1;
// 		if (pid == 0)
// 		{
// 			ft_close(sh, nb_pipes);
// 			execve(start->cmd_verified, start->args, env_init);
// 		}
// 	}
// 	else
// 	{
// 		mess_cmd_not_found(sh, start->cmd);
// 		reset_input_output(start);
// 		return (pid);
// 	}
// 	reset_input_output(start);
// 	return (pid);
// }

// void	execution_pipe(t_sh *sh, int nb_pipes, char **env_init)
// {
// 	int		i;
// 	int		k;
// 	t_pipe	*start;
// 	pid_t	pid;

// 	i = 0;
// 	k = 0;
// 	start = sh->pipe_lst;
// 	init_pipe(start, nb_pipes);
// 	while (start)
// 	{
// 		update_input_output(start);
// 		ft_switch(start, k);
// 		pid = exec2(start, sh, nb_pipes, env_init);
// 		if (k % 2 != 0)
// 			i++;
// 		k++;
// 		start = start->next;
// 	}
// 	ft_close(sh, nb_pipes);
// 	wait_get_status(sh, nb_pipes, pid);
// }

// void	no_pipe_exec(t_sh *sh, char **env_init)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	// le fork include les builltin sauf s'ils modifient l'env
// 	if (pid == -1)
// 		return ;
// 	if (pid == 0)
// 		execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
// 	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 			g_sh.exit = WEXITSTATUS(g_sh.exit);
// }

// void	execution(t_sh *sh, char **env_init)
// {
// 	int		nb_pipes;

// 	// print_pipe_tokens(sh->pipe_lst);
// 	nb_pipes = nb_pipe(sh->pipe_lst);
// 	fprintf(stderr, "nb de pipes = %d\n", nb_pipes);
// 	if (nb_pipes == 0)
// 	{
// 		update_input_output(sh->pipe_lst);
// 		if (sh->pipe_lst->is_builtin == 1)
// 			index_builtins(sh);
// 		else if (sh->pipe_lst->cmd_verified != NULL)
// 			no_pipe_exec(sh, env_init);
// 		else
// 		{
// 			mess_cmd_not_found(sh, sh->pipe_lst->cmd);
// 			reset_input_output(sh->pipe_lst);
// 			return ;
// 		}
// 		reset_input_output(sh->pipe_lst);
// 	}
// 	else
// 		execution_pipe(sh, nb_pipes, env_init);
// }
