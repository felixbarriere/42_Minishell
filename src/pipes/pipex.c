/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/24 19:18:58 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	reset_input_output(int cpy_input, int cpy_output, t_pipe *pipe_lst)
{
	dup2(cpy_input, 0);
	dup2(cpy_output, 1);
	close(cpy_input);
	close(cpy_output);
	if (pipe_lst->input != 0)
		close (pipe_lst->input);
	if (pipe_lst->output != 1)
		close (pipe_lst->output);
}

void	update_input_output(int *cpy_input, int *cpy_output, t_pipe *pipe_lst)
{
	*cpy_input = dup(0);
	*cpy_output = dup(1);
	dup2(pipe_lst->input, 0);
	dup2(pipe_lst->output, 1);
}

void	pipe_exec(t_sh *sh, char **env_init)
{
	pid_t	pid = 0;

	pid = fork();
	if (pid == 0)
	{	
		if (execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init) == -1)
			ft_putstr_fd("error execve\n", 2);
	}
	else
		wait(NULL);
	// A VERIFIER
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		g_sh.exit = WEXITSTATUS (g_sh.exit);
	close (pid);
}

void	execution(t_sh	*sh, char **env_init)
{
	t_pipe	*pipe_start;
	int	cpy_input;
	int	cpy_output;

	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst->cmd != NULL)
	{
		update_input_output(&cpy_input, &cpy_output, sh->pipe_lst);
		if (sh->pipe_lst->is_builtin == 1)
			index_builtins(sh);
		else if (sh->pipe_lst->cmd_verified != NULL)
			pipe_exec(sh, env_init);
		else
		{
			write (2, "command not found\n", 19);
			g_sh.exit = 127;
		}
		reset_input_output(cpy_input, cpy_output, sh->pipe_lst);
    sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
}



// void	pipe_exec(t_sh *sh, char **env_init)
// {
// 	pid_t	pid = 0;
// 	// (void)sh;

// 	if (sh->pipe_lst->is_builtin == 1)
// 	{
// 		index_builtins(sh);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{	
// 			if (execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init) == -1)
// 				ft_putstr_fd("error execve\n", 2);
// 		}
// 		else
// 			wait(NULL) ;
// 		// A VERIFIER
// 		if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
// 			g_sh.exit = WEXITSTATUS (g_sh.exit);
// 	}
// }

// void	execution(t_sh	*sh, char **env_init)
// {
// 	t_pipe	*pipe_start;

// 	printf("commande: %s\n", sh->pipe_lst->cmd_verified);
// 	pipe_start = sh->pipe_lst;
// 	while (sh->pipe_lst->cmd != NULL)
// 	{
// 		if (sh->pipe_lst->cmd_verified != NULL || sh->pipe_lst->is_builtin == 1)
// 			pipe_exec(sh, env_init);
// 		else
// 		{
// 			write (2, "command not found\n", 19);
// 			g_sh.exit = 127;
// 		}
//     sh->pipe_lst = sh->pipe_lst->next;
// 	}
// 	sh->pipe_lst = pipe_start;
// }