#ifndef MINISHELL_H
# define MINISHELL_H

/**************** LIBRAIRIES ****************/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# include "minishell_d.h"
# include "minishell_f.h"
# include "minishell_s.h"

/****************** MACROS ******************/
# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

/******COLORS*******/
# ifndef YELLOW
#  define YELLOW "\033[0;33m"
# endif

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif

# ifndef BLUE
#  define BLUE "\033[0;36m"
# endif

/**************** STRUCTURES ****************/
/* structure principale du programe */
typedef struct s_sh
{
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
} t_sh;

/**************** FUNCTIONS ****************/

#endif