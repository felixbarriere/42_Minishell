/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/05 18:28:32 by ccalas           ###   ########.fr       */
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

// ajoute le bon token à la liste chainée des tokens sh->token_lst
void	tokenizer(t_sh *sh)
{
	char	*str;
	char	*dollar;
	char	*dollar_content;
	char	*test_value;
	int		i;
	t_env	*tmp;

	str = NULL;
	tmp = NULL;
	i = 0;
	//verifier si le state quote est utile 
	if (sh->state_quote == DEFAULT && is_in_charset(sh->prompt[sh->p_index]))
	{
		if (sh->prompt[sh->p_index] == PIPE)
			sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
		else
			process_redirect_token(sh);
	}
	else if (sh->state_quote == DEFAULT && sh->prompt[sh->p_index] == '$')
	{
		dollar = string_token(sh, &sh->prompt[sh->p_index]);
		dollar_content = ft_strtrim(dollar, "$\"|\'");
		// tmp = sh->env_lst;
		// while (tmp->next != NULL)
		// {
		// 	printf("%s \n", tmp->key);
		// 	tmp = tmp->next;
		// }
		
		test_value = expander(sh, dollar_content);
		// printf("%s", test_value);

		// if (!is_only_space(dollar))
		// 	sh->token_lst = add_back_token(sh->token_lst, DOLLAR, dollar);	

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