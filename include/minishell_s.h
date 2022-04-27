/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_s.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/27 15:36:20 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_S_H
# define MINISHELL_S_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_f.h"
#include "minishell_e.h"


/* liste chaînée. Chaque token représente un caractère tokenisé, chaîné au token précédent / suivant
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

/* structure principale du programe */
typedef struct s_sh
{
	char	**env;
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
	int		lenght;
	int		state_quote;
} t_sh;

#endif