/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_limiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:36:31 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/23 16:40:57 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*process_quotes_limiter(char **value)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while ((*value)[i])
	{
		if (!((*value)[i] == '\"' || (*value)[i] == '\''))
		{
			new = ft_strjoin_char(new, (*value)[i]);
		}
		i++;
	}
	return (new);
}

int	limiter_has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	process_limiter(char **limiter, int *quotes)
{
	if (limiter_has_quotes(*limiter))
	{
		(*limiter) = process_quotes_limiter(limiter);
		(*quotes) = 1;
	}
	else
		(*limiter) = ft_strdup(*limiter);
}

int	is_limiter(char **temp, char **limiter)
{
	if (!ft_strncmp(*temp, *limiter, ft_strlen(*limiter))
		&& ft_strlen(*temp) == ft_strlen(*limiter))
	{
		ft_free_null_str(temp);
		return (SUCCESS);
	}
	return (FAILURE);
}
