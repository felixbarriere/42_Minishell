/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/27 16:29:30 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	is_builtin(t_pipe	*pipe)
{
	t_pipe	*pipe_start;

	pipe_start = pipe;
	while (pipe)
	{
		if (!ft_strcmp(pipe->cmd, "echo") || !ft_strcmp(pipe->cmd, "cd")
			|| !ft_strcmp(pipe->cmd, "pwd") || !ft_strcmp(pipe->cmd, "export")
			|| !ft_strcmp(pipe->cmd, "unset") || !ft_strcmp(pipe->cmd, "env")
			|| !ft_strcmp(pipe->cmd, "exit"))
				pipe->is_builtin = 1;
		pipe = pipe->next;
	}
	pipe = pipe_start;
}

void	lexer(t_sh *sh)
{
	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	tokenizer(sh);
	if (check_error_sep(sh->token_lst) == FAILURE)
	{
		sh->error = 1;
		return ;
	}
	pipe_creation(sh);
	get_commands_type(sh);
	update_command(sh);
	get_command_path(sh);
	is_builtin(sh->pipe_lst);
}
