/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/01 13:12:09 by fbarrier         ###   ########.fr       */
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
	t_pipe 	*pipe_start;
	t_token	*token_start;

	pipe_start = sh->pipe_lst;

	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	tokenizer(sh);
	// pipe_start = sh->pipe_lst;
	token_start = sh->token_lst;
	
	check_error_sep(sh->token_lst);
	print_tokens(sh->token_lst);

	// printf("token: %s\n", sh->token_lst->value);
	// if (token_start->value)
	// printf("token final: %s\n", token_start->value);




	pipe_creation(&sh->token_lst, &sh->pipe_lst, &pipe_start, &token_start);

	// print_tokens(sh->token_lst);
	// print_tokens(sh->pipe_lst->next->next->token);
	sh->pipe_lst = sh->pipe_lst->next; //a enlever apres;
	print_pipe_tokens(sh->pipe_lst);

	// print_tokens(sh->pipe_lst->token);
	// printf("list length=%d\n", list_length(sh->token_lst));
}

// A retravailler en dictionnaire par la suite
/*
int	ft_is_separator(t_sh *sh, int i)
{
	if ((sh->prompt[i] >= 9 && sh->prompt[i] <= 13) || sh->prompt[i] == 32)
		return (BLANK);
	else if (sh->prompt[i] == '|')
		return (PIPE);
	else if (sh->prompt[i] == '<' && sh->prompt[i + 1] == '<')
		return);
	else if (sh->prompt[i] == '>' && sh->prompt[i + 1] == '>')
		return (DOUBLE_R_RIGHT);
	else if (sh->prompt[i] == '<')
		return (R_LEFT);
	else if (sh->prompt[i] == '>')
		return (R_RIGHT);
	else if (sh->prompt[i] == '\0')
		return (END);
	else
		return (0);
}
*/