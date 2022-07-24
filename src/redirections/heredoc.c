/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:09:29 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/23 15:04:36 by ccalas           ###   ########.fr       */
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

int	init_heredoc(t_pipe **pipe_lst)
{
	ft_free_null_str(&(*pipe_lst)->limiter_name);
	(*pipe_lst)->limiter_name = ft_strdup("./heredoc");
	(*pipe_lst)->heredoc_mode = 1;
	(*pipe_lst)->input = open((*pipe_lst)->limiter_name, O_WRONLY
			| O_CREAT | O_TRUNC, 00644);
	if ((*pipe_lst)->input == -1)
		return (1);
	return (0);
}

int	heredoc2(char *limiter, t_pipe **pipe_lst, int quotes)
{
	char	*temp;
	int		i;

	i = 0;
	while (1)
	{
		temp = read_heredoc(pipe_lst, quotes, limiter);
		if (temp)
		{
			if (is_limiter(&temp, &limiter) == SUCCESS)
				break ;
			ft_putstr_fd(temp, (*pipe_lst)->input);
			ft_putstr_fd("\n", (*pipe_lst)->input);
			ft_free_null_str(&temp);
		}
		i++;
	}
	return (g_sh.exit);
}

int	heredoc(char *limiter, t_pipe **pipe_lst)
{
	int		quotes;
	pid_t	pid;

	quotes = 0;
	process_limiter(&limiter, &quotes);
	if (init_heredoc(pipe_lst))
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &heredoc_handler);
		exit(heredoc2(limiter, pipe_lst, quotes));
	}
	if ((0 < waitpid(pid, &g_sh.exit, 0)) && (WIFEXITED(g_sh.exit)))
		g_sh.exit = WEXITSTATUS(g_sh.exit);
	free(limiter);
	close((*pipe_lst)->input);
	if (open_fdin((*pipe_lst)->limiter_name, pipe_lst))
	{
		unlink((*pipe_lst)->limiter_name);
		return (1);
	}
	unlink((*pipe_lst)->limiter_name);
	return (0);
}

/*
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