/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:08:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/30 19:47:54 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	add_array_export(t_sh *sh, char *value)
{
	char	**env_temp;
	int		i;

	i = 0;
	while (sh->env[i])
		i++;
	env_temp = malloc(sizeof(char *) * (i + 1));
	if (!env_temp)
		return ;
	i = 0;
	while (sh->env[i])
	{
		env_temp[i] = ft_strdup(sh->env[i]);
		i++;
	}
	env_temp[i] = NULL;
	ft_free(sh->env);
	sh->env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env_temp[++i])
		sh->env[i] = ft_strdup(env_temp[i]);
	sh->env[i++] = ft_strdup(value);
	sh->env[i] = NULL;
	ft_free(env_temp);
}

char	*get_value(char **key_value)
{
	int		i;
	char	*value;
	char	*value_2;

	i = 2;
	value_2 = NULL;
	value = key_value[1];
	if (key_value[2] != NULL)
	{
		value_2 = ft_strdup(value);
		while (key_value[i])
		{
			value_2 = ft_strjoin_char_2(value_2, '=');
			value_2 = ft_strjoin(value_2, key_value[i]);
			i++;
		}
		value = ft_strdup(value_2);
		free(value_2);
	}
	return (value);
}

void	update_value(t_env	*list, char	*value, char *key)
{
	t_env	*temp;

	temp = list;
	while (list != NULL)
	{
		if (!ft_strcmp(key, list->key))
		{
			free(list->value);
			list->value = ft_strdup(value);
			return ;
		}
		list = list->next;
	}
	list = temp;
}

void	export_command_2(t_sh *sh, char *str)
{
	char	**key_value;
	char	*str_2;

	if (str)
		str_2 = delete_plus(str);
	if (str && contains_equal(str, sh))
	{
		key_value = ft_split(str_2, '=');
		if (!is_in_env(key_value[0], sh->env_lst))
		{
			orchestrate_env_token(str_2, sh, 0);
			add_array_export(sh, str_2);
		}
		else
			global_get_value(key_value, sh, NULL, NULL);
		ft_free(key_value);
		if (sh->path == NULL)
			get_path(sh);
		sh->exit = 0;
	}
	if (str)
		free(str_2);
}

void	export_command(t_sh *sh, t_pipe *start)
{
	int	i;

	i = 1;
	if (start->args[0] && !start->args[1])
		env_command_export(sh);
	while (start->args[i])
	{
		export_command_2(sh, start->args[i]);
		i++;
	}
}
