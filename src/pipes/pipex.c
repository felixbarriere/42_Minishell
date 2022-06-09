/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/09 15:18:12 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	pipe_exec(t_sh *sh, t_pipe	*pipe, char **env_init)
{
	pid_t	pid;
	(void)sh;


	pid = fork();
	if (pid == 0)
	{	
		if (execve(pipe->cmd_verified, pipe->args, env_init) == -1)
			printf("error execve\n");
	}
	else
		wait(NULL) ;
	return (pid);
}


void	execution(t_sh	*sh, char **env_init)
{	
	(void)env_init;
	// (void)sh;
	// t_pipe	*pipe_start;

	printf("cmd: %s\n", sh->pipe_lst->cmd_verified);

	// pipe_start = sh->pipe_lst;
	while (sh->pipe_lst->cmd_verified)
	{
	// 	// pipe_exec(sh, sh->pipe_lst, env_init);
		printf("test4\n");
		sh->pipe_lst = sh->pipe_lst->next;
	}
	// sh->pipe_lst = pipe_start;
}