#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	reset_input_output(t_pipe *pipe_lst)
{
	dup2(pipe_lst->cpy_input, 0);
	dup2(pipe_lst->cpy_output, 1);
	close(pipe_lst->cpy_input);
	close(pipe_lst->cpy_output);
   if (pipe_lst->input != 0 && pipe_lst->input != -1)
        close(pipe_lst->input);
    if (pipe_lst->output != 1 && pipe_lst->output != -1)
        close(pipe_lst->output);
}

void	update_input_output(t_pipe *pipe_lst)
{
	pipe_lst->cpy_input = dup(0);
	pipe_lst->cpy_output = dup(1);
	dup2(pipe_lst->input, 0);
	dup2(pipe_lst->output, 1);
}

void	ft_close(int **fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void    ft_free_fd(int **fd, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        free(fd[j]);
        j++;
    }
    free(fd);
}

void exec2(t_pipe *start, t_sh *sh, int **fd, int nb_pipes, char **env_init)
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
			ft_close(fd, nb_pipes);
			execve(start->cmd_verified, start->args, env_init);
		}
		// if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		// 	g_sh.exit = WEXITSTATUS(g_sh.exit);
	}
	else
	{
		write (2, "command not found\n", 19);
		g_sh.exit = 127;
		sh->error = 1;
		return ;
	}
	reset_input_output(start);
}


int	**init_pipe(int nb_pipes)
{
	int	i;
	int	**fd;
	
	fd = ft_calloc(sizeof(int *), nb_pipes);
	i = 0;
	while (i < nb_pipes)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		i++;
	}
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(fd[i]) == - 1)
			return (0);
		i++;
	}
	return (fd);
}

void	ft_switch(int **fd, t_pipe *start, int k, int i)
{
	if (!k)
		dup2(fd[i][1], start->output);
	else if (k && !start->next)
		dup2(fd[i][0], start->input);
	else if (k && start->next)
	{
		dup2(fd[i][0], start->input);
		dup2(fd[i + 1][1], start->output);
	}
}

void	execution_pipe(t_sh *sh, int nb_pipes, char **env_init)
{
	int		i;
	int		k;
	int		**fd;
	t_pipe	*start;

	i = 0;
	k = 0;
	start = sh->pipe_lst;
	fd = init_pipe(nb_pipes);
	while (start)
	{
		update_input_output(start);
		ft_switch(fd, start, k, i);
		exec2(start, sh, fd, nb_pipes, env_init);
		if (k % 2 != 0)
			i++;
		k++;
		start = start->next;
	}
	wait(0);
	ft_close(fd, nb_pipes);
	ft_free_fd(fd, nb_pipes);
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

int	nb_pipe(t_pipe *pipe_lst)
{
	int		nb_pipes;
	t_pipe	*start;

	start = pipe_lst;
	nb_pipes = 0;
	while (start->next)
	{
		nb_pipes++;
		start = start->next;
	}
	return (nb_pipes);
}

void	execution(t_sh *sh, char **env_init)
{
	int		nb_pipes;

	print_pipe_tokens(sh->pipe_lst);
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
			write (2, "command not found\n", 19);
			g_sh.exit = 127;
			sh->error = 1;
			return ;
		}
		reset_input_output(sh->pipe_lst);
	}
	else
		execution_pipe(sh, nb_pipes, env_init);
}
