/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 19:52:43 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_equal(char *str, t_sh *sh)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isdigit(str[0])
		&& (ft_isalnum(str[i]) == 1 || str[i] == '_' || (str[i] == '=' && i > 0)
			|| (str[i] == '+' && str[i + 1] == '=' && i > 0)))
	{
		if ((str[i] != '=' && i > 0) && str[i + 1] == '\0')
			return (0);
		else if ((str[i] == '=' && i > 0))
			return (1);
		i++;
	}
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	sh->exit = 1;
	return (0);
}

char	*delete_plus(char *src)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		if (src[i] == '+' && src[i + 1] == '=')
			i++;
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_former_value(char *key, t_env *list)
{
	t_env	*temp;

	temp = list;
	while (list != NULL)
	{
		if (!ft_strcmp(key, list->key))
		{
			return (list->value);
		}
		list = list->next;
	}
	list = temp;
	return (NULL);
}

void	update_value_2(t_env	*list, char	*value, char *key)
{
	t_env	*temp;

	temp = list;
	while (list != NULL)
	{
		if (!ft_strcmp(key, list->key))
		{
			list->value = ft_strdup(value);
			return ;
		}
		list = list->next;
	}
	list = temp;
}

void	global_get_value(char **key_value, t_sh *sh, char *value, char *for_val)
{
	char	**key_value_init;

	if (!ft_strcmp(key_value[1], "(null)") || key_value[1] == NULL)
	{
		update_value_null(sh->env_lst, key_value[0]);
		update_path(sh, key_value[0]);
		return ;
	}
	key_value_init = ft_split(sh->pipe_lst->args[1], '=');
	if (!ft_strcmp(key_value[0], key_value_init[0]))
	{
		value = get_value(key_value);
		update_value(sh->env_lst, value, key_value[0]);
		update_path(sh, key_value[0]);
	}	
	else
	{
		for_val = get_former_value(key_value[0], sh->env_lst);
		value = ft_strjoin(for_val, key_value_init[1]);
		update_value_2(sh->env_lst, value, key_value[0]);
		update_path(sh, key_value[0]);
		free(value);
	}
	ft_free(key_value_init);
}
