/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_e.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/04 19:20:53 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_E_H
# define MINISHELL_E_H

# include "minishell.h"
# include "minishell_d.h"
# include "minishell_f.h"

/**************** ENUMERATIONS ****************/

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
	INPUT,
	OUTPUT,
	APPEND,
	ARG,
	CMD,
	LIMITER,
}	t_token_type;

typedef enum quote_type
{
	DEFAULT,
	DOUBLE = '\"',
	SIMPLE = '\'',
}	t_quote_type;

#endif