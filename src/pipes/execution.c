#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	list_put_to_start(t_sh *sh)
{
	while (sh->pipe_lst->prev)
		sh->pipe_lst = sh->pipe_lst->prev;
}

void close_fd(t_sh *sh)
{
	t_pipe	*pipe_start;
	
	pipe_start = sh->pipe_lst;
	// while (sh->pipe_lst && sh->pipe_lst->next != NULL)
	while (sh->pipe_lst->next && sh->pipe_lst->next->next)
	{
		close(sh->pipe_lst->fd[0]);
		close(sh->pipe_lst->fd[1]);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
}

int	where_is_pipe(t_pipe *pipe_lst)
{
	if (pipe_lst->prev == NULL)
	{
		// printf("ICI 1 PIPE\n"); 	
		return (3);
	}
	else if (pipe_lst->prev != NULL && pipe_lst->next->next != NULL)
	{
		// printf("ICI 2 PIPE\n");	
		return (4);
	}
	else if (pipe_lst->next->next == NULL)
	{
		// printf("ICI 3 PIPE\n");	
		return (5);
	}
	return (0);
}

int	init_pipe(t_sh *sh)
{
	t_pipe	*pipe_start;
	
	list_put_to_start(sh);
	pipe_start = sh->pipe_lst;
	// while (sh->pipe_lst->next && sh->pipe_lst->next->next)
	while (sh->pipe_lst->cmd)
	{
		printf("ICI PIPES\n");
		if (pipe(sh->pipe_lst->fd) == -1)
			return FAILURE;
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
	return (SUCCESS);
}

void	ft_switch(t_pipe *pipe_lst)
{
	int	nb;

	nb = where_is_pipe(pipe_lst);
	fprintf(stderr, "output = %d\n", pipe_lst->output);
	fprintf(stderr, "input = %d\n", pipe_lst->input);
	if (nb == 3)
	{
		fprintf(stderr, " DEBUT PIPE 1\n");
		// close(pipe_lst->fd[1]);
		dup2(pipe_lst->fd[1], pipe_lst->output);
		fprintf(stderr, "pipe_lst->fd[1] = %d\n", pipe_lst->fd[1]);
	}
	else if (nb == 4)
	{
		fprintf(stderr, "MILIEU PIPE 2\n");
		dup2(pipe_lst->fd[0], pipe_lst->prev->input);
		dup2(pipe_lst->next->fd[1], pipe_lst->output);
	}
	else if (nb == 5)
	{
		fprintf(stderr, "FIN 3\n");
		// close(pipe_lst->fd[1]);
		dup2(pipe_lst->fd[0], pipe_lst->prev->input);
		fprintf(stderr, "pipe_lst->fd[0] = %d\n", pipe_lst->fd[0]);
	}
}

void	pipe_exec2(t_sh *sh, char **env_init)
{
	pid_t	pid = 0;

	pid = fork();
	// printf("4\n");
	// printf("PID = %d\n", pid);
	if (pid == 0)
	{	
		if (execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init) == -1)
			ft_putstr_fd("No such file or directory\n", 2);
		close_fd(sh);
	
	}
	else
	{
		if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
			g_sh.exit = WEXITSTATUS(g_sh.exit);
		wait(0);
	}
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		g_sh.exit = WEXITSTATUS(g_sh.exit);
	if (pid == 0)
		close (pid);
	// printf("pid close\n");
}

int	execution_pipe(t_sh	*sh, char **env_init)
{
	t_pipe	*pipe_start;
	int		cpy_input;
	int		cpy_output;
	int		i;

	i = 0;
	if (init_pipe(sh) == FAILURE)
		return (FAILURE);
	list_put_to_start(sh);
	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst->cmd != NULL)
	{
		update_input_output(&cpy_input, &cpy_output, sh->pipe_lst);
		ft_switch(sh->pipe_lst);
		if (sh->pipe_lst->is_builtin == 1)
		{
			index_builtins(sh);
			close_fd(sh);
		}
		else if (sh->pipe_lst->cmd_verified != NULL)
		{
			// printf("3\n");
			pipe_exec2(sh, env_init);
			close_fd(sh);
		}
		else
		{
			write (2, "command not found\n", 19);
			g_sh.exit = 127;
			sh->error = 1;
			return (FAILURE);
		}
		reset_input_output(cpy_input, cpy_output, sh->pipe_lst);
    sh->pipe_lst = sh->pipe_lst->next;
	}
	close_fd(sh);
	sh->pipe_lst = pipe_start;
	return (SUCCESS);
}

int	nb_pipe(t_sh *sh)
{
	t_pipe *pipe_start;
	int	i;
	
	i = 0;
	list_put_to_start(sh);
	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst->next)
	{	
		i++;
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
	return (i);
}

// void	execution(t_sh	*sh, char **env_init)
// {
// 	int		nb_pipes;
	
// 	nb_pipes = nb_pipe(sh) - 1;
// 	printf("nb_pipes = %d\n", nb_pipes);
// 	if (nb_pipes == 0)
// 	{
// 		if (execution_no_pipe(sh, env_init) == FAILURE)
// 			return ;
// 	}
// 	else if (nb_pipes > 0)
// 	{
// 		if (execution_pipe(sh, env_init) == FAILURE)
// 			return ;
// 	}
// }





// void	execution_no_pipe(t_sh *sh, char **env_init)
// {	
// 	if (sh->pipe_lst->is_builtin == 1)
// 		index_builtins(sh);
// 	else if (sh->pipe_lst->cmd_verified != NULL)
// 		exec_function(sh, env_init);
// 	else
// 	{
// 		write (2, "command not found\n", 19);
// 		g_sh.exit = 127;
// 	}
// }

// void	exec_function(t_sh *sh, char **env_init)
// {
// 	pid_t	pid = 0;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		sh->error = 1;
// 		return ;
// 	}
// 	else if (pid == 0)
// 	{	
// 		if (execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init) == -1)
// 			ft_putstr_fd("No such file or directory\n", 2);
// 	}
// 	else
// 	{
// 		if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 			g_sh.exit = WEXITSTATUS(g_sh.exit);
// 		wait(NULL);
// 	}
// 	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 		g_sh.exit = WEXITSTATUS(g_sh.exit);
// 	if (pid == 0)
// 		close (pid);
// }

// void	execution_pipe(t_sh	*sh, char **env_init)
// {
// 	t_pipe	*pipe_start;
// 	pid_t	pid;
// 	int		cpy_input;
// 	int		cpy_output;
// 	(void)env_init;
// 	int		i;

// 	i = 0;
// 	if (init_pipe(sh) == FAILURE)
// 		return ;
// 	list_put_to_start(sh);
// 	pipe_start = sh->pipe_lst;
// 	print_pipe_tokens(sh->pipe_lst);
// 	while (sh->pipe_lst->cmd != NULL)
// 	{
// 		// printf("here\n");
// 		update_input_output(&cpy_input, &cpy_output, sh->pipe_lst);
// 		ft_switch(sh->pipe_lst);
// 		if (sh->pipe_lst->is_builtin == 1)
// 		{
// 			index_builtins(sh);
// 			// close_fd(sh); PAS NECESSAIRE CAR DS PARENT
// 		}
// 		else if (sh->pipe_lst->cmd_verified != NULL)
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				return ;
// 			if (pid == 0)
// 			{
// 				execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init);
// 				close_fd(sh);				
// 			}
// 			else
// 			{
// 				if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 				{
// 					g_sh.exit = WEXITSTATUS(g_sh.exit);
// 					// printf("WEXIT = %d\n", g_sh.exit);
// 				}
// 				wait(NULL);
// 				// printf("ICI 2\n");
// 			}
// 		}
// 		else
// 		{
// 			write (2, "command not found\n", 19);
// 			g_sh.exit = 127;
// 		}
// 		reset_input_output(cpy_input, cpy_output, sh->pipe_lst);
// 		sh->pipe_lst = sh->pipe_lst->next;
// 	}
// 	// printf("INPUT = %d | OUPUT = %d\n", sh->pipe_lst->input, sh->pipe_lst->output);
// 	sh->pipe_lst = pipe_start;
// 	close_fd(sh);
// }
