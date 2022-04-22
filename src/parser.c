/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/22 14:15:24 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

char	*string_token_quote(t_sh *sh, char *prompt)
{
	char *str;
	int j = 0;

	while (prompt[j])
		j++;
	str = ft_strndup(prompt, j);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

char	*string_token(t_sh *sh, char *prompt)
{
	char *str;
	int j = 0;

	while (prompt[j])
	{

		if (is_in_charset(prompt[j]))
			break;
		j++;
	}
	str = ft_strndup(prompt, j);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
// fonction a separer en plusieurs sous fonctions (tokenize string, tokenize separators...)
void	tokenizer(t_sh *sh)
{
	char	*str_cmd;

	str_cmd = NULL;
	if (sh->prompt[sh->p_index] == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (sh->prompt[sh->p_index] == RED_LEFT || sh->prompt[sh->p_index] == RED_RIGHT)
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
	else
	{
		// if (sh->state_quote == DOUBLE || sh->state_quote == SIMPLE)

		// if (sh->state_quote == DEFAULT)
		// {
		// 	printf("DEFAULT\n");
		str_cmd = string_token(sh, &sh->prompt[sh->p_index]);
		// }
		// else if (sh->state_quote != DEFAULT)
		// {
		// 	printf("NOT DEFAULT\n");
		// 	str_cmd = string_token_quote(sh, &sh->prompt[sh->p_index]);
		// }

		if (!is_only_space(str_cmd))
		{
			// if (sh->state_quote == DEFAULT)
			sh->token_lst = add_back_token(sh->token_lst, CMD, str_cmd);
			// else if (sh->state_quote == SIMPLE)
			// sh->token_lst = add_back_token(sh->token_lst, STR_SIMPLE, str_cmd);
			// else if (sh->state_quote == DOUBLE)
			// sh->token_lst = add_back_token(sh->token_lst, STR_DOUBLE, str_cmd);
		}
	}
}

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

// la fonction "find_state" permet de definir si on se trouve
// dans une quote ou non.
void	ft_find_quote_state(t_sh *sh, int i)
{
	if (sh->prompt[i] == '\'' && sh->state_quote == DEFAULT)
		sh->state_quote = SIMPLE;
	else if (sh->prompt[i] == '\"' && sh->state_quote == DEFAULT)
		sh->state_quote = DOUBLE;
	else if (sh->prompt[i] == '\'' && sh->state_quote == SIMPLE)
		sh->state_quote = DEFAULT;
	else if (sh->prompt[i] == '\"' && sh->state_quote == DOUBLE)
		sh->state_quote = DEFAULT;
}

int	ft_is_quote_ok(t_sh *sh)
{
	int i;

	i = 0;
	while (sh->prompt[i])
	{
		ft_find_quote_state(sh, i);
		i++;
	}
	if (sh->state_quote != DEFAULT)
		return (FAILURE);
	return (SUCCESS);
}

void	lexer(t_sh *sh)
{
	int	type;
	int	start;

	type = 0;
	start = 0;

	// printf("is quotes ok: %d\n", ft_is_quote_ok(sh));
	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed :(", 2);
		// exit() quitte le programme, trouver un moyen de quitter uniquement le shell.
		// exit(1);
	}
	while (sh->prompt[sh->p_index])
	{
		// ft_find_quote_state(sh, sh->p_index);
		printf("QUOTE %d\n", sh->state_quote);
		if (sh->state_quote == DEFAULT)
		{
			// type = ft_is_separator(sh, sh->p_index); // pas forcement utile
			tokenizer(sh);
		}
		// else if(state == SIMPLE)
		// {

		// }
		// else if(state == DOUBLE)
		// {

		// }
		sh->p_index++;
	}

	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
}
