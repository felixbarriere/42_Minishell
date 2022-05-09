/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/09 18:15:15 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*string_token_2(t_sh *sh, char *prompt)
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
		if (prompt[j] && prompt[j] == '\'')
		{
			j++;
			while(prompt[j] && prompt[j] != '\'')
				j++;
		}
		if (is_in_charset(prompt[j]))
			break;
		j++;
	}
	temp = ft_strndup(prompt, j);
	str = ft_strtrim(temp, CHARSET_SPACE_TABS);
	// printf("%s\n", temp);
	free (temp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}


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
		if (prompt[j] && prompt[j] == '\'')
		{
			j++;
			while(prompt[j] && prompt[j] != '\'')
				j++;
		}
		if (is_in_charset(prompt[j]))
			break;
		j++;
	}
	temp = ft_strndup(prompt, j);
	str = ft_strtrim(temp, CHARSET_SPACE_TABS);
	// printf("%s\n", temp);
	free (temp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == R_LEFT && sh->prompt[sh->p_index + 1] == R_LEFT)
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

char	*isolate_dollar_in_quote(char *str)
{
	int i;
	int	j;
	int k;
	char *dollar = NULL;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			
			while (str[i] != ' ' && str[i] != '\"')
			{
				j++;
				i++;
			}
			i = (i - j);
			dollar = malloc(sizeof(char) * (j + 1));
			if (!dollar)
				return NULL;
			while (j > 0)
			{
				dollar[k] = str[i];
				k++;
				i++;
				j--;
			}
			dollar[k] = '\0';
			break ;
		}
		i++;
	}	
	return (dollar);
	printf("STR = %s\n", str);
	printf("DOLLAR = %s\n", dollar);	
}


// ajoute le bon token à la liste chainée des tokens sh->token_lst
void	tokenizer(t_sh *sh)
{
	char	*str;
	char	*dollar;
	char	*dollar_content;
	char	*test_value;
	char	*dollar2;
	char	*dollar_content2;
	char	*test_value2;
	char	**test;
	int		i;

	str = NULL;
	i = 0;
	ft_find_quote_state(sh, sh->p_index);
	printf("state_quote: %d\n", sh->state_quote);
	if (sh->state_quote == DEFAULT && is_in_charset(sh->prompt[sh->p_index]))
	{
		if (sh->prompt[sh->p_index] == PIPE)
			sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
		else
			process_redirect_token(sh);
	}
	else if ((sh->state_quote == DOUBLE || sh->state_quote == DEFAULT ) 
			&& sh->prompt[sh->p_index] == '$')
	{
		dollar = string_token(sh, &sh->prompt[sh->p_index]);
		dollar_content = ft_strtrim(dollar, "$\"|\'");
		test_value = expander(sh, dollar_content);
		test = ft_split (test_value, ' ');
		i = 0;
		while (test[i])
		{
			if (!is_only_space(dollar))
				sh->token_lst = add_back_token(sh->token_lst, DOLLAR, test[i]);
			i++;
		}
	}
	else 
	{
		str = string_token(sh, &sh->prompt[sh->p_index]);
		
		if (str[0] == '\"' && contains_$(str))
		{
			printf("LA\n");
			dollar2 = isolate_dollar_in_quote(str);
			dollar_content2 = ft_strtrim(dollar2, "$\"|\'");
			test_value2 = expander(sh, dollar_content2);
			printf("dollar2 : %s\n", dollar2);
			printf("Test value 2 %s\n", test_value2);
		}
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
		tokenizer(sh);
		sh->p_index++;
	}
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