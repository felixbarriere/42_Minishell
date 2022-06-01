/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/31 17:18:20 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (sh->prompt[sh->p_index] == R_LEFT
		&& sh->prompt[sh->p_index + 1] == R_LEFT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DR_LEFT, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == R_RIGHT
		&& sh->prompt[sh->p_index + 1] == R_RIGHT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DR_RIGHT, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == R_LEFT)
		sh->token_lst = add_back_token(sh->token_lst, R_LEFT, "<");
	else if (sh->prompt[sh->p_index] == R_RIGHT)
		sh->token_lst = add_back_token(sh->token_lst, R_RIGHT, ">");
}

int	token_str(t_sh *sh)
{
	char	*str;
	char	*new_str;
	char	*temp;
	char	*dollar_value;
	int		idx;

	idx = 0;
	temp = NULL;
	new_str = NULL;
	dollar_value = NULL;
	str = string_token(sh, &sh->prompt[sh->p_index]);
	printf("\nSTR EN COURS = %s\n", str);
	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)
	{
		if (str != NULL)
			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
		return (idx);
	}
	else
	{
		while (str[idx])
		{
			if (str[idx] == '\"' || str[idx] == '\'')
			{
				temp = quotes_manager(str, &idx, sh);
				if (temp != NULL)
					new_str = ft_strjoin(new_str, temp);
				free(temp);
			}
			else if (str[idx] == '$')
			{
				/* dollar_manager(); retourne une chaine avec la valeur du dollar */
				if (str[idx + 1] == '\'' || str[idx + 1] == '\"')
				{
					idx++;
					continue ;
				}
				dollar_value = noquote_dollar_manager(str, &idx, sh);
				printf("VALUE : %s\n", dollar_value);
				if (dollar_value != NULL)
					new_str = severals_wds_value(sh, dollar_value, new_str);
				printf("new_str = %s\n", new_str);
				continue ;
			}
			else
				new_str = ft_strjoin_char(new_str, str[idx]);
			idx++;
		}
	}
	if (new_str != NULL)
		sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	free(str);
	return (idx);
}

/* 
Ajoute le bon token à la liste chainée des tokens sh->token_lst
*/
void	tokenizer(t_sh *sh)
{
	while (sh->prompt[sh->p_index])
	{
		while (sh->prompt[sh->p_index] && sh->prompt[sh->p_index] == ' ')
			sh->p_index++;
		if (is_in_charset(sh->prompt[sh->p_index]))
		{
			if (sh->prompt[sh->p_index] == PIPE)
				sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
			else
				process_redirect_token(sh);
		}
		else if (sh->prompt[sh->p_index])
			token_str(sh);
		sh->p_index++;
	}
}
