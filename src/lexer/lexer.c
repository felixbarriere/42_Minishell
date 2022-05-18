/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/18 17:12:29 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*string_token(t_sh *sh, char *prompt)
{
	char *str;
	char *temp;
	int j = 0;

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

char	*ft_strjoin_char_2(char *s1, char c, char take_out)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	// if (s1 == NULL)
	// 	return (NULL);
	dest = ft_calloc(sizeof(char), (ft_strlen(s1) + 2));
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	if (take_out != c)
		dest[i] = c;
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*squote_manager(char *str, int *idx)
{
	char	*new_str;
	
	new_str = NULL;
	(*idx)++;
	while (str[(*idx)] != '\0' && str[(*idx)] != '\'')
	{
		new_str = ft_strjoin_char_2(new_str, str[(*idx)], 39);
		(*idx)++;
	}
	return (new_str);
}

char	*dquote_dollar_manager(char *str, int *idx, t_sh *sh)
{
	char	*key;
	char	*value;
	char	*new_str;

	new_str = NULL;
	key = get_key_dollar(str, (*idx));
	value = get_value_dollar(sh, key);
	(*idx) = (*idx) + ft_strlen(key);
	return (value);
}

char	*dquote_manager(char *str, int *idx, t_sh *sh)
{
	char	*new_str;
	char	*value;
	
	new_str = NULL;
	(*idx)++;
	while (str[(*idx)] != '\0' && str[(*idx)] != '\"')
	{
		printf("INDEX STR = %d\n", *idx);
		if (str[(*idx)] == '$')
		{
			value = dquote_dollar_manager(str, idx, sh);
			if (value != NULL)
			{
				new_str = ft_strjoin(new_str, value);
				printf("INDEX STR dans IF = %d\n", *idx);
			}
			continue;
		}
		new_str = ft_strjoin_char_2(new_str, str[(*idx)], 34);
		(*idx)++;
	}
	return (new_str);
}

char	*noquote_dollar_manager(char *str, int *idx, t_sh *sh)
{
	char	*key;
	char	*value;

	key = get_key_dollar(str, (*idx ));
	value = get_value_dollar(sh, key);
	(*idx) = (*idx) + ft_strlen(key);
	if (value != NULL)
		return (value);
	return (NULL);
}

char	*quotes_manager(char *str, int *idx, t_sh *sh)
{
	char	*new_str;
	
	new_str = NULL;
	
	if (str[(*idx)] == '\'')
		new_str = squote_manager(str, idx);
	else if (str[(*idx)] == '\"')
		new_str = dquote_manager(str, idx, sh);
	return (new_str);
}

int	token_str(t_sh *sh)
{
	char 	*str;
	char 	*new_str;
	char	*temp;
	char	*quote;
	char	*dollar;
	int		idx = 0;
	int		len;

	len = 0;
	temp = NULL;
	new_str = NULL;
	dollar = NULL;
	quote = NULL;
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
			dollar = noquote_dollar_manager(str, &idx, sh);
			printf("DOLLAR = %s\n", dollar);
			// join valeur du dollar
			new_str = ft_strjoin(new_str, dollar);
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
	// char	*str;
	// char	*str_wip = NULL;
	// char	*key;
	// char	*value;

	while(sh->prompt[sh->p_index])
	{
		// printf("p_index = %d\n", sh->p_index);
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
			// int i = 0;
			token_str(sh);
			// sh->p_index += i;
		}
		sh->p_index++;
	}
}





















void	lexer(t_sh *sh)
{
	if (ft_is_quote_ok(sh) != 0)
	{
		ft_putstr_fd("quotes unclosed\n", 2);
		return ;
	}
	// while (sh->prompt[sh->p_index]) 
	// {
	tokenizer(sh);
	// 	sh->p_index++;
	// }
	check_error_sep(sh->token_lst);
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