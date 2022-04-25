/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/25 16:50:27 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

char	*string_token(t_sh *sh, char *prompt)
{
	char *str;
	int j = 0;

	while (prompt[j])
	{
		if (is_in_charset(prompt[j]) && sh->state_quote == DEFAULT)
			break;
		j++;
		ft_find_quote_state(sh, j);
	}
	str = ft_strndup(prompt, j);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == RED_LEFT && sh->prompt[sh->p_index + 1] == RED_LEFT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_LEFT, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_RIGHT && sh->prompt[sh->p_index + 1] == RED_RIGHT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_RIGHT, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_LEFT)
		sh->token_lst = add_back_token(sh->token_lst, RED_LEFT, "<");
	else if (sh->prompt[sh->p_index] == RED_RIGHT)
		sh->token_lst = add_back_token(sh->token_lst, RED_RIGHT, ">");
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
void	tokenizer(t_sh *sh)
{
	char	*str;

	str = NULL;
	
	// on verifie si on entre ou sort des quotes
	ft_find_quote_state(sh, sh->p_index);
	
	if (sh->state_quote == DEFAULT && is_in_charset(sh->prompt[sh->p_index]))
	{
		if (sh->prompt[sh->p_index] == PIPE)
			sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
		else
			process_redirect_token(sh);
	}
	else
	{
		str = string_token(sh, &sh->prompt[sh->p_index]);
		if (!is_only_space(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
	}
}
void	lexer(t_sh *sh)
{
	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	while (sh->prompt[sh->p_index])
	{
	
		printf("QUOTE %d\n", sh->state_quote);
		tokenizer(sh);
		sh->p_index++;
	}
	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
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
		return (DOUBLE_RED_LEFT);
	else if (sh->prompt[i] == '>' && sh->prompt[i + 1] == '>')
		return (DOUBLE_RED_RIGHT);
	else if (sh->prompt[i] == '<')
		return (RED_LEFT);
	else if (sh->prompt[i] == '>')
		return (RED_RIGHT);
	else if (sh->prompt[i] == '\0')
		return (END);
	else
		return (0);
}
*/