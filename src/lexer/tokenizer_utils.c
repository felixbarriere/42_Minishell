/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/07/15 16:02:10 by fbarrier         ###   ########.fr       */
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
			while (prompt[j] && prompt[j] != '\"')
				j++;
		}
		else if (prompt[j] && prompt[j] == '\'')
		{
			j++;
			while (prompt[j] && prompt[j] != '\'')
				j++;
		}
		else if (is_in_charset(prompt[j]))
			break ;
		j++;
	}
	return (j);
}

char	*string_token(t_sh *sh, char *prompt)
{
	char	*str;
	char	*temp;
	int		j;

	j = len_to_dup(prompt);
	temp = ft_strndup(prompt, j);
	str = ft_strtrim(temp, CHARSET_SPACE_TABS);
	if (str == NULL)
		return (NULL);
	free (temp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

char	*join_dollar_value(char *str, char *new_str,
			char *dollar_value, int idx)
{
	if (ft_strcmp(dollar_value, "$") != 0)
		new_str = ft_strjoin(new_str, dollar_value);
	else if (ft_strcmp(dollar_value, "$") == 0
		&& (str[idx] != '\'' && str[idx] != '\"'))
		new_str = ft_strjoin(new_str, dollar_value);
	return (new_str);
}

char	*severals_wds_value(t_sh *sh, char *dollar_value, char	*new_str)
{
	int		i;
	int		j;
	char	**value_dollar_split;

	i = 0;
	j = 0;
	value_dollar_split = ft_split(dollar_value, ' ');
	while (value_dollar_split[j])
		j++;
	if (j > 1)
	{
		new_str = ft_strjoin(new_str, value_dollar_split[i]);
		while (value_dollar_split[i + 1])
		{
			sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
			i++;
			new_str = ft_strdup(value_dollar_split[i]);
		}
		free(new_str);
		new_str = ft_strdup(value_dollar_split[i]);
	}
	else
		new_str = ft_strjoin(new_str, value_dollar_split[0]);
	ft_free(value_dollar_split);
	return (new_str);
}

int	ft_strlen2(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
