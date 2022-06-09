/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/09 15:13:12 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	is_builtin(t_sh	*sh)
{
	t_pipe	*pipe_start;

	pipe_start = sh->pipe_lst;
	while (sh->pipe_lst)
	{
		if (!ft_strcmp(sh->prompt, "echo") || !ft_strcmp(sh->prompt, "cd") ||
			!ft_strcmp(sh->prompt, "pwd") || !ft_strcmp(sh->prompt, "export") ||
			!ft_strcmp(sh->prompt, "unset") || !ft_strcmp(sh->prompt, "env") ||
			!ft_strcmp(sh->prompt, "exit"))
			{
				sh->pipe_lst->is_builtin = 1;	
			}		
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = pipe_start;
}

void	lexer(t_sh *sh)
{
	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	tokenizer(sh);
	check_error_sep(sh->token_lst);
	print_tokens(sh->token_lst);
	pipe_creation(sh);
	get_commands_type(sh);
	get_command_path(sh);
	// is_builtin(sh);
	printf("*********************\n");
}
