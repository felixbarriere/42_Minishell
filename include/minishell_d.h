#ifndef MINISHELL_D_H
# define MINISHELL_D_H

#include "minishell.h"
#include "minishell_f.h"
#include "minishell_s.h"
#include "minishell_e.h"

/****************** MACROS ******************/
# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
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