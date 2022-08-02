/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_in_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:52:05 by fbarrier          #+#    #+#             */
/*   Updated: 2022/08/02 12:53:26 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

void	ft_switch(t_pipe *start, int k)
{	
	if (!k)
		dup2(start->fd[1], start->output);
	else if (k && !start->next)
		dup2(start->prev->fd[0], start->input);
	else if (k && start->next)
	{
		dup2(start->prev->fd[0], start->input);
		dup2(start->fd[1], start->output);
	}
}

void	reset_input_output(t_pipe *pipe_lst)
{
	dup2(pipe_lst->cpy_input, 0);
	dup2(pipe_lst->cpy_output, 1);
	close(pipe_lst->cpy_input);
	close(pipe_lst->cpy_output);
	if (pipe_lst->input != 0 && pipe_lst->input != -1)
		close(pipe_lst->input);
	if (pipe_lst->output != 1 && pipe_lst->output != -1)
		close(pipe_lst->output);
}

void	update_input_output(t_pipe *pipe_lst)
{
	pipe_lst->cpy_input = dup(0);
	pipe_lst->cpy_output = dup(1);
	dup2(pipe_lst->input, 0);
	dup2(pipe_lst->output, 1);
}
