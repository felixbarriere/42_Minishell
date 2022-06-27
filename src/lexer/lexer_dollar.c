/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/27 15:27:41 by ccalas           ###   ########.fr       */
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
		if (str[i] == '?')
		{
			key = get_key_dollar_2(str, i, j);
			return (key);
		}
		if (str[i] == '$' || str[i] < 48
			|| (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 95)
			|| (str[i] > 95 && str[i] < 97) || str[i] > 122)
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

	if (ft_strcmp(key, "$") == 0)
		value = ("$");
	else if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(sh->exit);
	else
	{
		key_trim = ft_strtrim(key, "$\"|\'");
		value = expander(sh, key_trim);
		free(key_trim);
	}
	return (value);
}
