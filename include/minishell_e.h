/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_e.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/04/27 15:35:45 by ccalas           ###   ########.fr       */
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
	RED_LEFT = '<',
	RED_RIGHT = '>',
	DOUBLE_RED_LEFT,
	DOUBLE_RED_RIGHT,
	BLANK,
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