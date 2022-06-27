/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:53:47 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/27 19:45:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	str = NULL;
}

void	ft_free_2(char *str)
{
	free(str);
	str = NULL;
}

void	ft_free_3(t_env *list)
{
	t_env	*tmp;

	printf("test leaks");
	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	get_path(t_sh	*sh)
{
	t_env	*temp;

	temp = sh->env_lst;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PATH"))
		{
			// printf("temp->value: %s\n", temp->value);
			sh->path = ft_split(temp->value, ':');
		}
		// else
		// 	sh->path = NULL;
		temp = temp->next;
	}
}

char	*ft_strjoin_char_2(char *s1, char c)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
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
	free(s1);
	return (dest);
}