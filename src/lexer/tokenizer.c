/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/19 18:11:04 by ccalas           ###   ########.fr       */
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

char	*join_dollar_value(char *str, char *new_str, char *dollar_value, int idx)
{
	
	if (ft_strcmp(dollar_value, "$") != 0)
		new_str = ft_strjoin(new_str, dollar_value);
	else if (ft_strcmp(dollar_value, "$") == 0 && (str[idx] != '\'' && str[idx] != '\"'))
		new_str = ft_strjoin(new_str, dollar_value);
	return(new_str);
}




int	token_str(t_sh *sh)
{
	char 	*str;
	char 	*new_str;
	char	*temp;
	char	*dollar_value;
	int		idx;
	int		len;
	char	**value_dollar_split = NULL;

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
			/* retourne une chaine sans quote et change le $ ou pas */
			temp = quotes_manager(str, &idx, sh);
			/* join la chaine */
			new_str = ft_strjoin(new_str, temp);
		}
		else if (str[idx] == '$')
		{
			int i;
			int j;

			i = 0;
			j = 0;
			/* dollar_manager(); retourne une chaine avec la valeur du dollar */
			dollar_value = noquote_dollar_manager(str, &idx, sh);
			// printf("DOLLAR = %s\n", dollar_value);
			if (!dollar_value)
			{
				printf("VALUE NULL: %s\n", dollar_value);
				new_str = ft_strjoin(new_str, temp);
				break;
			}
			value_dollar_split = ft_split(dollar_value, ' ');
			while (value_dollar_split[j])
			{
				j++;
			}
			if (j > 1)
			{
				printf("test1\n");
				new_str = ft_strjoin(new_str, value_dollar_split[i]);
				while (value_dollar_split[i + 1])
				{
					sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
					printf("dollar_str: %s\n", value_dollar_split[i]);
					i++;
					new_str = ft_strdup(value_dollar_split[i]);
				}
				new_str = ft_strdup(value_dollar_split[i]);
			}
			else
			{
				printf("test2\n");
				new_str = ft_strjoin(new_str, value_dollar_split[0]);
			}
			printf("new_str = %s\n", new_str);
			continue;
		}
		else
			new_str = ft_strjoin_char(new_str, str[idx]);
		printf("new_str2 = %s\n", new_str);
		if (idx < len) //protection sans doute plus necessaire a cause du continue 
			idx++;
	}
	sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	return (len);
}


/* 
Ajoute le bon token à la liste chainée des tokens sh->token_lst
*/
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

