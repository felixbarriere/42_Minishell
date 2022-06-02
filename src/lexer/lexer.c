/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/02 16:07:48 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	lexer(t_sh *sh)
{
	// t_pipe 	*pipe_start;
	// t_token	*token_start;

	// pipe_start = sh->pipe_lst;

	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	tokenizer(sh);
	// pipe_start = sh->pipe_lst;
	// token_start = sh->token_lst;
	
	check_error_sep(sh->token_lst);
	print_tokens(sh->token_lst);

	pipe_creation(sh);
	
	get_commands1(sh);
	printf("*********************\n");
	while (sh->pipe_lst)
	{
		print_tokens(sh->pipe_lst->token);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	// print_tokens(sh->pipe_lst->token);
	// printf("list length=%d\n", list_length(sh->token_lst));
}
