/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/14 14:34:12 by fbarrier         ###   ########.fr       */
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

int	ft_token_part2(t_sh *sh, char *str)
{
	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)
	{
		if (str != NULL)
			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
		return (1);
	}
	return (0);
}

char	*token_str_2(char *str, int *idx, t_sh *sh)
{
	char	*new_str;
	char	*temp;

	new_str = NULL;
	temp = quotes_manager(str, idx, sh);//externaliser -5 lignes
	if (temp != NULL)
		new_str = ft_strjoin(new_str, temp);
	free(temp);
	return (new_str);
}

void	token_str(t_sh *sh)
{
	char	*str;	//creer une structure a part avec les variables + une fonction pour les init. creer la structure dans "tokenizer" 
	char	*new_str;	//et l'envoyer en arg a token_str
	char	*dollar_value;
	char	*temp;
	int		idx;
	int		i;

	i = 0;
	idx = 0;
	temp = NULL;
	new_str = NULL;
	dollar_value = NULL;
	str = string_token(sh, &sh->prompt[sh->p_index]);
	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)  //externaliser et renvoyer un int. if(fction()== 1), return ;
	{
		if (str != NULL)
			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
		return ;
	}
	while (str[idx])
	{
		if (str[idx] == '\"' || str[idx] == '\'')
		{
			temp = quotes_manager(str, &idx, sh);
			if (temp != NULL)
				new_str = ft_strjoin(new_str, temp);
			free(temp);
		// new_str = token_str_2(str, &idx, sh); attention au cas export ls="ls -la" si on externalise 
		}
		else if (str[idx] == '$')
		{
			if (str[idx + 1] == '\'' || str[idx + 1] == '\"')
			{
				idx++;
				continue ;
			}
			idx = i;
			dollar_value = noquote_dollar_manager(str, &idx, sh);
			if (dollar_value != NULL)
			{
				new_str = severals_wds_value(sh, dollar_value, new_str);
				if (str[i] && str[i + 1] == '?')
					free(dollar_value);
			}
			continue ;
		}
		else
			new_str = ft_strjoin_char(new_str, str[idx]);
		idx++;
	}
	if (new_str != NULL)
		sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	free(str);
}

int	ft_strlen2(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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
