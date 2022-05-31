/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/31 16:48:44 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

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