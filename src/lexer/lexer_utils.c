/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/17 16:46:03 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_$(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	contains_quotes(char *str)
{
	int	i;
	i = 0;
	while (str[i] != '\0' && str[i] != '\'')
	{
		if (str[i] == '\"')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	how_many_squote(char *str)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;	
	
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			j++;	
		i++;
	}
	return (i);
}

int	contains_first_squote(char *str)
{
	int	i;
	i = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			return (SUCCESS);
		else if (str[i] == '\"')
			return (FAILURE);
		i++;
	}
	return (FAILURE);
}

int	is_in_charset(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ')
		return (1);
	return (0);
}

int	is_only_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_char(char *s1, char c)
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
	dest[i] = c;
	i++;
	dest[i] = '\0';
	return (dest);
}