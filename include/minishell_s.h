/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_s.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/02 17:48:02 by fbarrier         ###   ########.fr       */
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

/* liste chainee representant les commandes autours des pipes */
typedef struct s_pipe
{
	t_token			*token;
	char			*cmd;
	char			*options;
	char			*file; //?
	struct s_pipe	*prev;
	struct s_pipe	*next;
} t_pipe;

/* structure principale du programe */
typedef struct s_sh
{
	char	**path;
	t_env	*env_lst;
	t_pipe	*pipe_lst;
	int		e_index;
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
	int		lenght;
	int		state_quote;
} t_sh;

#endif