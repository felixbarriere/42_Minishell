/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:59:52 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/06 19:55:12 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

static void	close_pipes(t_sh	*sh, t_pipe	*pipe_lst)
{
	t_pipe	*temp;

	temp = sh->pipe_lst;
	while (temp)
	{
		if (temp != pipe_lst)
		{
			if (temp->infile > 2)
				close(temp->infile);
			if (temp->outfile > 2)
				close(temp->outfile);
		}
		temp = temp->next;
	}
}

static void	set_pipefd(t_pipe	*pipe_lst, t_sh	*sh)
{
	while (pipe_lst)
	{
		if (pipe_lst->infile == -2)
			pipe_lst->infile = 0;
		if(pipe_lst->next)
		{
			pipe(sh->pipefd);
		}
		pipe_lst = pipe_lst->next;
	}
}


static void	pipe_1(t_sh *sh, t_pipe	*pipe_lst, char **env_init)
{
	sh->pid1 = fork();


	if (sh->pid1 == 0)
	{
		if (dup2(pipe_lst->infile, STDIN_FILENO) == -1)
		printf("error dup2\n");
		if (pipe_lst->infile > 2)
			close(pipe_lst->infile);
		if (dup2(pipe_lst->outfile, STDOUT_FILENO) == -1)
			printf("error dup2bis\n");
		if (pipe_lst->outfile > 2)
			close(pipe_lst->outfile);
		close_pipes(sh, sh->pipe_lst);


		printf("0\n");
		if (execve(pipe_lst->cmd_verified, pipe_lst->args, env_init) == -1)
			printf("error execve\n");
	}
	else 
		wait(NULL) ;
}

void	execution(t_sh	*sh, char **env_init)
{
	set_pipefd(sh->pipe_lst, sh);
	
	while (sh->pipe_lst->cmd_verified)
	{
		pipe_1(sh, sh->pipe_lst, env_init);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	
	
	// close(sh->pipefd[0]);
	// close(sh->pipefd[1]);
	waitpid(sh->pid1, NULL, 0);
	// waitpid(sh->pid2, NULL, 0);
}


// // void	pipe_2(t_sh *sh, t_pipe	*pipe_lst, char **env_init)
// // {
// // 	sh->pid2 = fork();

// // 	// if (dup2(sh->pipefd[0], STDOUT_FILENO) == -1)
// // 	// 	printf("error dup2bis\n");
// // 	// close(sh->pipefd[1]);

// // 	if (sh->pid2 == 0)
// // 	{
// // 		printf("0\n");
// // 		if (execve(pipe_lst->cmd_verified, pipe_lst->args, env_init) == -1)
// // 			printf("error execve\n");
// // 	}
// // 	else 
// // 		wait(NULL) ;
// // }

// void	execution(t_sh	*sh, char **env_init)
// {
// 	// if (pipe(sh->pipefd) == -1)
// 	// 	printf("error pipe");


// 	pipe_1(sh, sh->pipe_lst, env_init);
	
// 	// if (sh->pipe_lst->next->cmd_verified)
// 	// 	pipe_2(sh, sh->pipe_lst->next, env_init);



// 	// close(sh->pipefd[0]);
// 	// close(sh->pipefd[1]);
// 	waitpid(sh->pid1, NULL, 0);
// 	// waitpid(sh->pid2, NULL, 0);
// }