/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/01 17:19:01 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	print_pipe_tokens(t_pipe *li)
{
	while (li != NULL)
	{
		printf("\n");
		printf("[%s] ", li->token->value);
		// if (li->prev)
		// 	printf("[precedent = %s]", li->prev->value);
		// if  (li->next)
		// 	printf("[suivant = %s]", li->next->value);
		li = li->next;
	}
	printf("\n");
}

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
	print_tokens(sh->token_lst);
	print_pipe_tokens(sh->pipe_lst);

	// print_tokens(sh->token_lst);
	// print_tokens(sh->pipe_lst->next->next->token);
	// sh->pipe_lst = sh->pipe_lst->next; //a enlever apres;
	// print_pipe_tokens(sh->pipe_lst);

	// print_tokens(sh->pipe_lst->token);
	// printf("list length=%d\n", list_length(sh->token_lst));
}
