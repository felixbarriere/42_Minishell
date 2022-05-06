/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_s.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/06 12:13:59 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_S_H
# define MINISHELL_S_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_f.h"
#include "minishell_e.h"

/**************** STRUCTURES ****************/
/* liste chaînée. Chaque token représente un caractère tokenisé, chaîné au token précédent / suivant
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

/* liste chainee representant les variables d'environnement */
typedef struct s_env
{
	t_token_type	type;
	char			*full;
	char			*key;
	char			*value;
	int				index; //?
	struct s_env	*next;
} t_env;

/* structure principale du programe */
typedef struct s_sh
{
	t_env	*env_lst;
	int		e_index;
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
	int		lenght;
	int		state_quote;
} t_sh;

#endif