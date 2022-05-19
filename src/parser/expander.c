/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/19 16:45:59 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char *expander(t_sh *sh, char *dollar)
{
    t_env   *tmp;
    // (void)dollar;

    // tmp = NULL;
    tmp = sh->env_lst;
	while (tmp != NULL)
    {
        if (tmp->key && (ft_strcmp(tmp->key, dollar) == 0))
        {
        // printf("%s\n", tmp->value);
            return (tmp->value);
        }
        else 
        {
            // printf("test");
            // return (NULL);
            // return("\n\n");  //attention comportement different si $var est seul ou non 
        }
        tmp = tmp->next;
    }

    return (NULL);
}

//aller dans sh->env.
// dans le char **, parser chaque str et regarder la cle (avant '=');
// comparer avec dollar
// si la variable existe, return un char** de la valeur.
// test git 