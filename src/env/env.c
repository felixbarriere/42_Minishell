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

t_env	*create_env_token(char *value, char *key, int index, char *full)
{
	t_env	*elem;

	elem = ft_calloc(1, sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->type = ENV;
	elem->value = ft_strdup(value);
	elem->key = ft_strdup(key);
	elem->index = index;
	elem->full = ft_strdup(full);
	elem->next = NULL;
	return (elem);
}

t_env	*add_back_env_token(t_env *list, char *value, char *key, int index, char *full)
{
	t_env	*new;
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	new = create_env_token(value, key, index, full);
	// printf("New value [%s]\n", new->value);
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
	int	i;
	char *key;
	char *value;
	char **test;

	i = 0;
	test = ft_split (env_init, '=');
	key = test[0];
	value = test[1];

	// printf("key : %s\n", key);
	// printf("value : %s\n", value);
	
	sh->env_lst= add_back_env_token(sh->env_lst, value, key, index, env_init);
	free(test);
	free (key);
	free (value);
}

t_env	*ft_init_env(char **env_init, t_sh *sh)
{
	int		i;

	if (!env_init)
		return (NULL);
	i = 0;
	sh->env_lst = malloc(sizeof(t_env));
	if (!sh->env_lst)
		return (NULL);
	while (env_init[i])
	{
		orchestrate_env_token(env_init[i], sh, i);
		i++;
	}
	// while (sh->env_lst != NULL)
	// {
	// 	printf("\n");
	// 	printf("[%s] ", sh->env_lst->key);
	// 	printf("[%s] ", sh->env_lst->value);
	// 	printf("[Type : %d]\n", sh->env_lst->type);
	// 	sh->env_lst = sh->env_lst->next;
	// }
	return (sh->env_lst);
}
 