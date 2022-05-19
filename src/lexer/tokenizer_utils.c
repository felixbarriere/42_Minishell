/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/19 15:32:16 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

/* FONCTIONS UTILES POUR LES QUOTES ET $ DANS LES QUOTES */

char	*squote_manager(char *str, int *idx)
{
	char	*new_str;
	
	new_str = NULL;
	(*idx)++;
	while (str[(*idx)] != '\0' && str[(*idx)] != '\'')
	{
		new_str = ft_strjoin_char_takeout(new_str, str[(*idx)], 39);
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
		if (str[(*idx)] == '$')
		{
			value = dquote_dollar_manager(str, idx, sh);
			if (value != NULL)
				new_str = ft_strjoin(new_str, value);
			continue;
		}
		new_str = ft_strjoin_char_takeout(new_str, str[(*idx)], 34);
		(*idx)++;
	}
	return (new_str);
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