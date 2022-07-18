/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/18 13:39:58 by marvin           ###   ########.fr       */
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

// int	ft_token_part2(t_sh *sh, char *str)
// {
// 	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)
// 	{
// 		if (str != NULL)
// 			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
// 		return (1);
// 	}
// 	return (0);
// }

char	*token_str_3(char *str, char *new_str, int *idx, t_sh *sh)
{
	char	*temp;

	temp = quotes_manager(str, idx, sh);
	printf("temp: %s\n", temp);
	if (temp != NULL)
		new_str = ft_strjoin(new_str, temp);
	printf("new_str: %s\n", new_str);
	free(temp);
	return (new_str);
}

char	*token_str_2(char *str, char *new_str, t_sh *sh, char *dol_val)
{
	while (str[sh->ts_idx])
	{
		if (str[sh->ts_idx] == '\"' || str[sh->ts_idx] == '\'')
			new_str = token_str_3(str, new_str, &sh->ts_idx, sh);
		else if (str[sh->ts_idx] == '$')
		{
			if (str[sh->ts_idx + 1] == '\'' || str[sh->ts_idx + 1] == '\"')
			{
				sh->ts_idx++;
				continue ;
			}
			sh->ts_i = sh->ts_idx;
			dol_val = noquote_dollar_manager(str, &sh->ts_idx, sh);
			if (dol_val != NULL)
				new_str = severals_wds_value(sh, dol_val, new_str);
			if (dol_val != NULL && (str[sh->ts_i] && str[sh->ts_i + 1] == '?'))
			{
				printf("i: %c", str[sh->ts_i]);
				printf("i + 1: %c", str[sh->ts_i + 1]);
				free(dol_val);
			}
			continue ;
		}
		else
			new_str = ft_strjoin_char(new_str, str[sh->ts_idx]);
		sh->ts_idx++;
	}
	return (new_str);
}

void	token_str(t_sh *sh)
{
	char	*str;
	char	*new_str;
	char	*dollar_value;
	char	*temp;

	sh->ts_idx = 0;
	sh->ts_i = 0;
	temp = NULL;
	new_str = NULL;
	dollar_value = NULL;
	str = string_token(sh, &sh->prompt[sh->p_index]);
	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)
	{
		if (str != NULL)
			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
		return ;
	}
	new_str = token_str_2(str, new_str, sh, dollar_value);
	if (new_str != NULL)
		sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	free(str);
}

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
		if (ft_strlen2(sh->prompt) <= sh->p_index)
			break ;
		sh->p_index++;
	}
}
