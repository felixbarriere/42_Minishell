/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/22 18:52:20 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	pipe_exec(t_sh *sh, char **env_init)
{
	pid_t	pid = 0;
	// (void)sh;

	if (sh->pipe_lst->is_builtin == 1)
	{
		index_builtins(sh);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{	
			if (execve(sh->pipe_lst->cmd_verified, sh->pipe_lst->args, env_init) == -1)
				ft_putstr_fd("error execve\n", 2);
		}
		else
			wait(NULL) ;
	}
	// A VERIFIER
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		g_sh.exit = WEXITSTATUS (g_sh.exit);
}

void	execution(t_sh	*sh, char **env_init)
{
	t_pipe	*pipe_start;

	printf("commande: %s\n", sh->pipe_lst->cmd_verified);
	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst->cmd != NULL)
	{
		if (sh->pipe_lst->cmd_verified != NULL || sh->pipe_lst->is_builtin == 1)
			pipe_exec(sh, env_init);
		else
		{
			write (2, "command not found\n", 19);
			g_sh.exit = 127;
		}
    sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
}