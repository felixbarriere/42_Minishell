/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_in_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:52:05 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/31 14:57:59 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

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
