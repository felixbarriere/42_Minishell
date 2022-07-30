/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:09:29 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 17:48:51 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

char	*filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close (file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_2(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	if (file_exists != -1)
		close(file_exists);
	return (filename);
}

int	wait_heredoc(pid_t pid, int *status, t_pipe *pipe_lst)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (WEXITSTATUS(*status))
		{
			g_sh.exit = WEXITSTATUS(*status);
			g_sh.error = 1;
			close(pipe_lst->input);
			return (1);
		}
	}
	return (0);
}

void	heredoc_child(char *limiter, t_pipe **pipe_lst, int quotes)
{
	signal(SIGINT, &heredoc_handler);
	heredoc2(limiter, pipe_lst, quotes);
	free(limiter);
	free_free_all(&g_sh);
	exit(g_sh.exit);
}

int	heredoc_bis(char *limiter, t_pipe **pipe_lst)
{
	ft_signals_orchestrator(0);
	free(limiter);
	if ((*pipe_lst)->input)
		close((*pipe_lst)->input);
	if (open_fdin((*pipe_lst)->limiter_name, pipe_lst))
	{
		unlink((*pipe_lst)->limiter_name);
		return (1);
	}
	unlink((*pipe_lst)->limiter_name);
	return (0);
}

int	heredoc(char *limiter, t_pipe **pipe_lst)
{
	int		quotes;
	int		status;
	pid_t	pid;

	quotes = 0;
	process_limiter(&limiter, &quotes);
	g_sh.limiter = limiter;
	if (init_heredoc(pipe_lst))
		return (1);
	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(limiter, pipe_lst, quotes);
	if (wait_heredoc(pid, &status, *pipe_lst))
	{
		free(limiter);
		if (g_sh.exit == 130)
			return (2);
		return (1);
	}
	return (heredoc_bis(limiter, pipe_lst));
}

/*
int	heredoc(char *limiter, t_pipe **pipe_lst)
{
	int		quotes;
	int		status;
	pid_t	pid;
	quotes = 0;
	process_limiter(&limiter, &quotes);
	if (init_heredoc(pipe_lst))
		return (1);
	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &heredoc_handler);
		heredoc2(limiter, pipe_lst, quotes);
		free (limiter);
		
		ft_free(g_sh.env);
		clear_list(g_sh.token_lst);
		clear_list_pipe(g_sh.pipe_lst);
		clear_list_env(g_sh.env_lst);
		ft_close2();
		// ft_close_final();
	
		exit(g_sh.exit);
	}
	if (wait_heredoc(pid, &status, *pipe_lst))
	{
		free(limiter);
		if (g_sh.exit == 130)
			return (2);
		return (1);
	}
	ft_signals_orchestrator(0);
	free(limiter);
	if ((*pipe_lst)->input)
		close((*pipe_lst)->input);
	if (open_fdin((*pipe_lst)->limiter_name, pipe_lst))
	{
		unlink((*pipe_lst)->limiter_name);
		return (1);
	}
	unlink((*pipe_lst)->limiter_name);
	return (0);
}
int	init_heredoc(t_pipe **pipe_lst)
{
	ft_free_null_str(&(*pipe_lst)->limiter_name);
	(*pipe_lst)->limiter_name = filename();
	(*pipe_lst)->heredoc_mode = 1;
	// (*pipe_lst)->input = open((*pipe_lst)->limiter_name, O_RDWR
	// 		| O_CREAT | O_APPEND, 00644);
	(*pipe_lst)->input = open((*pipe_lst)->limiter_name, O_WRONLY
			| O_CREAT | O_TRUNC, 00644);
	if ((*pipe_lst)->input == -1)
		return (1);
	return (0);
}
*/