/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:03:42 by marvin            #+#    #+#             */
/*   Updated: 2022/04/20 18:03:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// char	*ft_strdup_env(char *src)
// {
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
// 	if (!dest)
// 		return (NULL);
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

t_env	*create_env_token(char *value, char *key, int index)
{
	t_env	*elem;

	elem = NULL;
	elem = ft_calloc(1, sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->type = ENV;
	elem->key = ft_strdup(key);
	if (value)
		elem->value = ft_strdup(value);
	elem->index = index;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

t_env	*add_back_env_token(t_env *list, char *value, char *key, int index)
{
	t_env	*new;
	t_env	*tmp;

	tmp = NULL;
	new = create_env_token(value, key, index);
	if (!new)
		return (NULL);
	if (!list)
		return (new);
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (list);
}

char	*get_key(char *full)
{
	char	*key;
	int		i;

	i = 0;
	while (full[i] != '=' && full[i])
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (full[i] != '=' && full[i])
	{
		key[i] = full[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	orchestrate_env_token(char *env_init, t_sh *sh, int index)
{
	char	*key;
	char	*value;

	key = get_key(env_init);
	value = ft_substr(env_init, (ft_strlen(key) + 1), ft_strlen(env_init));
	sh->env_lst = add_back_env_token(sh->env_lst, value, key, index);
	if (value)
		free(value);
	free(key);
}

void	ft_init_env(char **env_init, t_sh *sh)
{
	int		i;

	i = 0;
	if (!env_init)
		return ;
	while (env_init[i])
	{
		orchestrate_env_token(env_init[i], sh, i);
		i++;
	}
}

// void	orchestrate_env_token(char *env_init, t_sh *sh, int index)
// {
// 	char	*key;
// 	char	*value;
// 	char	*value_2;
// 	char	**key_value;
// 	int		i;

// 	i = 2;
// 	value_2 = NULL;
// 	key_value = ft_split (env_init, '=');
// 	key = key_value[0];
// 	value = key_value[1];
// 	if (key_value[2] != NULL)
// 	{
// 		value_2 = ft_strdup(value);
// 		while (key_value[i])
// 		{
// 			value_2 = ft_strjoin_char_2(value_2, '=');
// 			value_2 = ft_strjoin(value_2, key_value[i]);
// 			// free(key_value[i]);
// 			i++;
// 		}
// 		value = ft_strdup(value_2);
// 		free(value_2);
// 	}
// 	sh->env_lst = add_back_env_token(sh->env_lst, value, key, index);
// 	if (key_value[2] != NULL)
// 		free(value);
// 	ft_free(key_value);
// }