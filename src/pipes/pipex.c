/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/22 15:30:29 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	pipe_exec(t_pipe	*pipe, char **env_init)
{
	pid_t	pid = 0;
	// (void)sh;

	if (pipe->is_builtin == 1)
	{
		index_builtins(pipe);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{	
			if (execve(pipe->cmd_verified, pipe->args, env_init) == -1)
				printf("error execve\n");	
		}
		else
			wait(NULL) ;
	}
	// A VERIFIER
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		g_sh.exit = WEXITSTATUS (g_sh.exit);
}

void	execution(t_pipe	*pipe, char **env_init)
{
	t_pipe	*pipe_start;


	printf("commande: %s\n", pipe->cmd_verified);
	pipe_start = pipe;
	while (pipe->cmd != NULL)
	{
		if (pipe->cmd_verified != NULL || pipe->is_builtin == 1)
			pipe_exec(pipe, env_init);
		else
		{
			write (2, "command not found\n", 19);
			g_sh.exit = 127;
		}
		pipe = pipe->next;
	}
	pipe = pipe_start;
}