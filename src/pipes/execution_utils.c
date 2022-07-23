/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:52:05 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/22 13:56:00 by ccalas           ###   ########.fr       */
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

void	mess_cmd_not_found(t_sh *sh, char *cmd)
{
	if (cmd == NULL)
		return ;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	sh->exit = 127;
	sh->error = 1;
	reset_input_output(sh->pipe_lst);
}

void	init_pipe(t_pipe *start, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(start->fd) == -1)
			return ;
		start = start->next;
		i++;
	}
}

int	nb_pipe(t_pipe *pipe_lst)
{
	int		nb_pipes;
	t_pipe	*start;

	start = pipe_lst;
	nb_pipes = 0;
	while (start->next)
	{
		nb_pipes++;
		start = start->next;
	}
	return (nb_pipes);
}
