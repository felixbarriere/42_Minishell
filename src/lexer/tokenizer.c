/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/19 11:27:24 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	len_to_dup(char *prompt)
{
	int	j;

	j = 0;
	while (prompt[j])
	{
		if (prompt[j] && prompt[j] == '\"')
		{
			j++;
			while(prompt[j] && prompt[j] != '\"')
				j++;
		}
		else if (prompt[j] && prompt[j] == '\'')
		{
			j++;
			while(prompt[j] && prompt[j] != '\'')
				j++;
		}
		else if (is_in_charset(prompt[j]))
			break;
		j++;
	}
	return (j);
}

char	*string_token(t_sh *sh, char *prompt)
{
	char *str;
	char *temp;
	int j;

	j = len_to_dup(prompt);
	temp = ft_strndup(prompt, j);
	str = ft_strtrim(temp, CHARSET_SPACE_TABS);
	if (str == NULL)
	{
		printf("str = NULL");
		return (NULL);
	}
	free (temp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (sh->prompt[sh->p_index] == R_LEFT && sh->prompt[sh->p_index + 1] == R_LEFT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DR_LEFT, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == R_RIGHT && sh->prompt[sh->p_index + 1] == R_RIGHT)
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
	char 	*str;
	char 	*new_str;
	char	*temp;
	char	*dollar_value;
	int		idx;
	int		len;
	// char	**value_dollar_split = NULL;
	// int		str_len = 0;

	idx = 0;
	len = 0;
	temp = NULL;
	new_str = NULL;
	dollar_value = NULL;
	str = string_token(sh, &sh->prompt[sh->p_index]);
	len = ft_strlen(str);
	printf("\nSTR EN COURS = %s\n", str);
	while(str[idx])
	{
		if (str[idx] == '\"' || str[idx] == '\'')
		{
			 // retourne une chaine sans quote et change le $ ou pas
			temp = quotes_manager(str, &idx, sh);
			printf("TEMP = %s\n", temp);
			printf("INDEX = %d\n", idx);
			// join la chaine
			new_str = ft_strjoin(new_str, temp);
			printf("QUOTE = %s\n", new_str);

		}
		else if (str[idx] == '$')
		{
			// dollar_manager(); // retourne une chaine avec la valeur du dollar
			// calcul la taille de la str avant le new expand
			// str_len = ft_strlen(new_str);
			dollar_value = noquote_dollar_manager(str, &idx, sh);
			printf("DOLLAR = %s\n", dollar_value);
			// si espace dans la valeur faire un split
			// value_dollar_split = ft_split(dollar_value, ' ');
			
			// join valeur du dollar
			new_str = ft_strjoin(new_str, dollar_value);
			printf("LEN = %d\nIdX = %d\n", len, idx);
			// Prendre notre chaine depuis idx et verifier qu'il n'y a pas d'espace 
			// Si oui - creer un token jusqu'a l'espace puis supprimer
			//
			continue;
		}
		else
			new_str = ft_strjoin_char(new_str, str[idx]);
		printf("new_str = %s\n", new_str);
		if (idx < len)
			idx++;
	}
	sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	return (len);
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
void	tokenizer(t_sh *sh)
{
	while(sh->prompt[sh->p_index])
	{
		while(sh->prompt[sh->p_index] && sh->prompt[sh->p_index] == ' ')
			sh->p_index++;
		if (is_in_charset(sh->prompt[sh->p_index]))
		{
			if (sh->prompt[sh->p_index] == PIPE)
				sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
			else
				process_redirect_token(sh);
		}
		else if (sh->prompt[sh->p_index])
		{
			token_str(sh);
			// sh->p_index += i; INUTILE ?
		}
		sh->p_index++;
	}
}