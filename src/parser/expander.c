/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/05 14:39:11 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char *expander(t_env *env_lst, char *dollar)
{
    t_env   *tmp;

    tmp = env_lst;
	while (env_lst->next)
    {
        if (!ft_strcmp(env_lst->key, dollar))
        {
            return (env_lst->value);
        }
        env_lst = env_lst->next;
    }
    return (NULL);
}

//aller dans sh->env.
// dans le char **, parser chaque str et regarder la cle (avant '=');
// comparer avec dollar
// si la variable existe, return un char** de la valeur.
// test git