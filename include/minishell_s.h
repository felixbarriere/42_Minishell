#ifndef MINISHELL_S_H
# define MINISHELL_S_H

#include "minishell.h"
#include "minishell_d.h"
#include "minishell_f.h"

typedef enum token_type
{
	PIPE = '|',
	RED_LEFT = '<',
	RED_RIGHT = '>',
	DOUBLE_RED_LEFT,
	DOUBLE_RED_RIGHT,
	STR,
} t_token_type;

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
	t_token	*token_lst;
	char	*prompt;
	int		p_index;
} t_sh;

#endif