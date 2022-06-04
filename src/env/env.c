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

t_env	*create_env_token(char *value, char *key, int index)
{
	t_env	*elem;

	elem = ft_calloc(1, sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->type = ENV;
	elem->key = ft_strdup(key);
	elem->value = ft_strdup(value);
	elem->index = index;
	elem->next = NULL;
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
	}
	return (list);
}

void	orchestrate_env_token(char *env_init, t_sh *sh, int index)
{
	int		i;
	char	*key;
	char	*value;
	char	**key_value;

	i = 0;
	key_value = ft_split (env_init, '=');
	key = key_value[0];
	value = key_value[1];
	sh->env_lst = add_back_env_token(sh->env_lst, value, key, index);
	ft_free(key_value);
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
