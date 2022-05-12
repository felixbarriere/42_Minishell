/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/12 14:37:00 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*get_key_dollar_2(char *str, int i, int j)
{
	int		k;
	char	*key;

	k = 0;
	key = ft_calloc((j + 1), sizeof(char));
	if (!key)
		return (NULL);
	while (j > 0 && str[i])
	{
		key[k] = str[i];
		k++;
		i++;
		j--;
	}
	key[k] = '\0';
	return (key);
}

char	*get_key_dollar(char *str, int i)
{
	int		j;
	char	*key;

	j = 0;
	while (str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
	{
		j++;
		i++;
		if (str[i] == '$')
			break ;
	}
	i = (i - j);
	key = get_key_dollar_2(str, i, j);
	return (key);
}

char	*get_value_dollar(t_sh	*sh, char *key)
{
	char	*key_trim;
	char	*value;

	key_trim = ft_strtrim(key, "$\"|\'");
	value = expander(sh, key_trim);
	return (value);
}

char	*isolate_dollar_in_quote_2(char *str, t_sh *sh)
{
	int		i;
	char	*value;
	char	*str_wip;
	char	*key;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			key = get_key_dollar(str, i);
			value = get_value_dollar(sh, key);
			if (value == NULL)
				i = i + ft_strlen(key) - 1;
			else
			{
				str_wip = ft_strjoin(str_wip, value);
				i = i + ft_strlen(key) - 1;
			}
		}
		else
			str_wip = ft_strjoin_char(str_wip, str[i]);
		i++;
	}
	return (str_wip);
}

char	*dollar_in_quote(char *str, t_sh *sh)
{
	char	*str_wip;

	str_wip = isolate_dollar_in_quote_2(str, sh);
	return (str_wip);
}

/*
char *get_value_dollar(t_sh	*sh, char *str, int i)
{
	int		j;
	int		k;
	char	*key;
	char 	*key_trim;
	char	*value;
	
	j = 0;
	while (str[i] != ' ' && str[i] != '\"')
	{
		j++;
		i++;
		if (str[i] == '$')
			break ;
	}
	i = (i - j);
	key = ft_calloc((j + 1), sizeof(char));
	if (!key)
		return NULL;
	k = 0;
	while (j > 0 && str[i])
	{
		key[k] = str[i];
		k++;
		i++;
		j--;
	}
	key[k] = '\0';
	key_trim = ft_strtrim(key, "$\"|\'");
	value = expander(sh, key_trim);

	return (value);
}
*/