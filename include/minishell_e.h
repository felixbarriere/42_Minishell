/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_e.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/05 14:48:55 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_E_H
# define MINISHELL_E_H

# include "minishell.h"
# include "minishell_d.h"
# include "minishell_f.h"

typedef enum token_type
{
	PIPE = '|',
	R_LEFT = '<',
	R_RIGHT = '>',
	DR_LEFT,
	DR_RIGHT,
	DOLLAR,
	BLANK,
	ENV,
	END,
	STR,
	CMD,
}	t_token_type;

typedef enum quote_type
{
	DEFAULT,
	SIMPLE = '\'',
	DOUBLE = '\"',
}	t_quote_type;

#endif