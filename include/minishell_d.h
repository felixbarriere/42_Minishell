/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/06/04 19:26:02 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# include "minishell.h"
# include "minishell_f.h"
# include "minishell_s.h"
# include "minishell_e.h"

/****************** MACROS ******************/
# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef CHARSET_SEP
#  define CHARSET_SEP "<>|"
# endif

# ifndef CHARSET_SPACE_TABS
#  define CHARSET_SPACE_TABS " \n\v\t\f\r"
# endif

/****** COLORS *******/
# ifndef YELLOW
#  define YELLOW "\033[0;33m"
# endif

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif

# ifndef BLUE
#  define BLUE "\033[0;36m"
# endif

#endif