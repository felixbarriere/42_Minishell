/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/12 18:23:48 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"


char *string_token(t_sh *sh, char *prompt)
{
	char *str;
	int j = 0;

	while (prompt[j])
	{
		if (isin_charset(prompt[j]))
			break;
		j++;
	}
	str = ft_strdup(prompt, j);
	if (j == 0)
		printf("ERROR TO CHECK\n");
	sh->p_index += j - 1;
	return (str);
}



void	tokenizer(t_sh *sh, char first, char second)
{
	(void)sh;
	char	*str;

	str = NULL;
	// ajoute le bon token à la liste chainée des tokens sh->token_lst
	if (first == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (first == RED_LEFT || first == RED_RIGHT)
	{
		//printf("first=%c, second=%c\n", first, second);
		if (first == RED_LEFT && second == RED_LEFT)
			sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_LEFT, "<<");
		else if (first == RED_RIGHT && second == RED_RIGHT)
			sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_RIGHT, ">>");
		else if (first == RED_LEFT)
			sh->token_lst = add_back_token(sh->token_lst, RED_LEFT, "<");
		else if (first == RED_RIGHT)
			sh->token_lst = add_back_token(sh->token_lst, RED_RIGHT, ">");
	}
	else
	{
		str = string_token(sh, &sh->prompt[sh->p_index]);
		if (!isonly_space(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
	}
}



void lexer(t_sh *sh)
{
	int sec;

	while (sh->prompt[sh->p_index])
	{
		//à faire à un moment : gérer les tabulations et les espaces (les virer)
		printf("i=%d\n", sh->p_index);
		sec = ft_parse_red(sh);
		
		tokenizer(sh, sh->prompt[sh->p_index], sec);
		sh->p_index++;
	}
	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
}


