/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/09 17:04:23 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	pipe_exec(t_sh *sh, t_pipe	*pipe, char **env_init)
{
	pid_t	pid;
	(void)sh;

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

void	execution(t_sh	*sh, char **env_init)
{
	t_pipe	*pipe_start;

	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst)
	{
		if (sh->pipe_lst->cmd_verified != NULL)
			pipe_exec(sh, sh->pipe_lst, env_init);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
}