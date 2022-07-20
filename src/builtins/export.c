/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:08:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/20 19:52:24 by marvin           ###   ########.fr       */
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

int	is_in_env(char	*key, t_env	*list)
{
	t_env	*temp;

	temp = list;
	while (list != NULL)
	{
		if (!ft_strcmp(key, list->key))
		{
			list = temp;
			return (1);
		}
		list = list->next;
	}
	list = temp;
	return (0);
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
		}
		list = list->next;
	}
	list = temp;
}

void	export_command(t_sh *sh)
{
	char	**key_value;
	char	*value;
	char	*value_2;

	if (sh->pipe_lst->token->next != NULL)
	{
		value_2 = delete_plus(sh->pipe_lst->args[1]);
		printf( "sh->pipe_lst->args[1]: %s\n", sh->pipe_lst->args[1]);
		printf( "sh->pipe_lst->token->next->value: %s\n", sh->pipe_lst->token->next->value);
		printf( "value_2: %s\n", value_2);
		// free(value_2);
	}
	if (sh->pipe_lst->token->next && contains_equal(sh->pipe_lst->args[1], sh))
	{
		key_value = ft_split(value_2, '=');
		if (!is_in_env(key_value[0], sh->env_lst))
		{
			orchestrate_env_token(value_2, sh, 0);
			add_array_export(sh, value_2);
		}
		else
		{
			value = get_value(key_value);
			update_value(sh->env_lst, value, key_value[0]);
			update_path(sh, key_value[0]);
			if (key_value[2] != NULL)
				free(value);
		}
		ft_free(key_value);
		free(value_2);
		if (sh->path == NULL)
			get_path(sh);
	}
	else if (!sh->pipe_lst->token->next)
		env_command_export(sh);
}
