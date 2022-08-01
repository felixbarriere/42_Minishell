/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:39:55 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/01 16:38:22 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	open_fdout(t_token *token, t_pipe **pipe_lst)
{
	if (token->type == OUTPUT)
	{
		if ((*pipe_lst)->output != 1)
			close ((*pipe_lst)->output);
		(*pipe_lst)->output = open(token->value, O_WRONLY
				| O_CREAT | O_TRUNC, 00644);
		(*pipe_lst)->append_mode = 0;
	}
	else if (token->type == APPEND)
	{
		if ((*pipe_lst)->output != 1)
			close ((*pipe_lst)->output);
		(*pipe_lst)->output = open(token->value, O_WRONLY
				| O_CREAT | O_APPEND, 00644);
		(*pipe_lst)->append_mode = 1;
	}
}

int	open_fdin(char	*value, t_pipe **pipe_lst)
{
	if ((*pipe_lst)->input != 0)
		close ((*pipe_lst)->input);
	(*pipe_lst)->input = open(value, O_RDONLY);
	if ((*pipe_lst)->input == -1)
	{
		(*pipe_lst)->input = 0;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		(*pipe_lst)->pipe_ok = 1;
		g_sh.exit = 1;
		g_sh.error = 3;
		return (3);
	}
	return (0);
}

void	close_fdin(t_pipe **pipe_lst)
{
	if ((*pipe_lst)->input != 0)
		close((*pipe_lst)->input);
	if ((*pipe_lst)->heredoc_mode == 1)
		(*pipe_lst)->heredoc_mode = 0;
}

int	update_error(int error)
{
	if (error == 2)
		return (2);
	else if (error)
		return (1);
	return (0);
}

int	update_fdin(t_pipe **pipe_lst)
{
	t_token	*temp;
	int		error;

	error = 0;
	temp = (*pipe_lst)->token;
	while (temp)
	{
		if (temp->type == INPUT || temp->type == LIMITER)
		{
			error = update_fdin_error(temp, *pipe_lst);
			if (error)
				return (error);
		}
		else if (temp->type == OUTPUT || temp->type == APPEND)
		{
			if ((*pipe_lst)->output != 1)
				close ((*pipe_lst)->output);
			open_fdout(temp, pipe_lst);
			if ((*pipe_lst)->output == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

/*
int	update_fdout(t_pipe **pipe_lst)
{
	t_token	*temp;

	temp = (*pipe_lst)->token;
	while (temp)
	{
		if (temp->type == OUTPUT || temp->type == APPEND)
		{
			if ((*pipe_lst)->output != 1)
				close ((*pipe_lst)->output);
			open_fdout(temp, pipe_lst);
			if ((*pipe_lst)->output == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}
*/