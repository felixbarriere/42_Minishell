/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:09:29 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 12:50:25 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	ft_close2(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	free_free_all(t_sh *sh)
{
	ft_free(sh->env);
	if (sh->path != NULL)
		ft_free(sh->path);
	if (sh->prompt)
		free(sh->prompt);
	clear_list(sh->token_lst);
	clear_list_pipe(sh->pipe_lst);
	clear_list_env(sh->env_lst);
	ft_close2();
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
