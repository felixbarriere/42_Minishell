/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/09 17:30:46 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	pipe_exec(t_pipe	*pipe, char **env_init)
{
	pid_t	pid;
	// (void)sh;

	printf("commande: %s\n", pipe->cmd_verified);
	if (pipe->is_builtin == 1)
	{
		index_builtins(pipe);
		printf("not build yet!\n"); //si exit ou ctrl-D, reste parfois dans le minishell
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
}

void	execution(t_pipe	*pipe, char **env_init)
{
	t_pipe	*pipe_start;

	pipe_start = pipe;
	while (pipe->cmd != NULL)
	{
		if (pipe->cmd_verified != NULL || pipe->is_builtin == 1)
			pipe_exec(pipe, env_init);
		else
			write (2, "command not found\n", 19);
		pipe = pipe->next;
	}
	pipe = pipe_start;
}