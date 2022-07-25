/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:50:00 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/25 14:54:47 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	is_in_range(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1 || (i == 0 && str[i] == '-'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_min(char *str)
{
	char	*min;
	int		i;

	while (*str == '0')
		str++;
	if (!*str)
		return (0);
	if (ft_strlen_3(str) > 20)
		return (0);
	if (ft_strlen_3(str) < 20)
		return (1);
	min = ft_strdup("-9223372036854775808");
	if (!min)
		return (1);
	i = 1;
	while (min[i])
	{
		if (str[i] > min[i])
			return (free(min), 0);
		if (str[i] < min[i])
			return (free(min), 1);
		i++;
	}
	return (free(min), 1);
}

int	ft_strlen_3(const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s[i] == '-')
	{
		i = 1;
		j = 1;
	}
	while (s[i] == '0')
		i++;
	while (s[i])
	{
		i++;
		j++;
	}
	return (j);
}
