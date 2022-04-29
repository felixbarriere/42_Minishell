#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

bool is_type(t_token* current, t_token_type type)
{
	if (current != NULL && current->type == type)
		return (true);
	return (false);
}

// bool is_type(t_token* current, t_token_type type)
// {
// 	if (current != NULL && current->type == type)
// 		return (true);
// 	return (false);
// }

// comment definir BLANK?
int	check_error_sep_0(t_token *token_lst)
{
	if ((is_type(token_lst->prev, R_RIGHT) && is_type(token_lst, PIPE) 
			) ||
			(is_type(token_lst->prev, DR_RIGHT) && is_type(token_lst, PIPE)
			&& is_type(token_lst->next, PIPE)) ||
			(is_type(token_lst->prev, R_LEFT) && is_type(token_lst, PIPE)
			&& is_type(token_lst->next, BLANK)))
	{
		printf("syntax error near unexpected token  `||'\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_1(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
			&& is_type(token_lst->next, R_LEFT)) ||
			(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
			&& is_type(token_lst->next, R_LEFT)))
	{
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
		return (FAILURE);
	}
	else if	((is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
			&& is_type(token_lst->next, R_LEFT)) ||
			(is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
			&& is_type(token_lst->next, R_LEFT)))
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_2(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
		&& is_type(token_lst->next, R_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
		&& is_type(token_lst->next, R_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
		&& is_type(token_lst->next, R_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
		&& is_type(token_lst->next, R_RIGHT)))
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_3(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
		&& is_type(token_lst->next, DR_LEFT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
		&& is_type(token_lst->next, DR_LEFT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
		&& is_type(token_lst->next, DR_LEFT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
		&& is_type(token_lst->next, DR_LEFT)))
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_4(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
		&& is_type(token_lst->next, DR_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
		&& is_type(token_lst->next, DR_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
		&& is_type(token_lst->next, DR_RIGHT)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
		&& is_type(token_lst->next, DR_RIGHT)))
	{
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_5(t_token *token_lst)
{
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
		&& is_type(token_lst->next, BLANK)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
		&& is_type(token_lst->next, BLANK)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
		&& is_type(token_lst->next, BLANK)) ||
		(is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
		&& is_type(token_lst->next, BLANK)))
	{
		ft_putstr_fd("syntax error near unexpected token `\\n'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep(t_token *token_lst)
{
	while(token_lst->next)
	{
		check_error_sep_0(token_lst);
		check_error_sep_1(token_lst);
		// if (is_type(token_lst, PIPE) == true && is_type(token_lst->next, PIPE) == true 
		// 	&& is_type(token_lst->prev, PIPE) == true)
		// {
		// 	printf("parse error near `||'\n");
		// 	return (FAILURE);
		// }
	
		
		token_lst= token_lst->next;
		

		// print_tokens(sh->token_lst);

		// if (token_lst->prev)
		// {
		
		// 	printf("PREV Exists\n");
		// 	return (FAILURE);
		// }
	}
	return (SUCCESS);
}

// int	check_sep_right(t_token *token_lst)

	// static const t_dict	dict[DICT_SIZE] = {{{R_RIGHT, PIP, NUL}, 0},
	// {{DR_RIGHT, PIP, PIP}, 0}, {{R_LEFT, PIP, NONE}, 0},
	// {{NONE, R_LEFT, NUL}, 5}, {{NONE, R_LEFT, R_RIGHT}, 2},
	// {{NONE, R_LEFT, DR_RIGHT}, 4}, {{NONE, R_LEFT, R_LEFT}, 1},
	// {{NONE, R_LEFT, DR_LEFT}, 3}, {{NONE, DR_LEFT, NUL}, 5},
	// {{NONE, DR_LEFT, R_RIGHT}, 2}, {{NONE, DR_LEFT, DR_RIGHT}, 4},
	// {{NONE, DR_LEFT, R_LEFT}, 1}, {{NONE, DR_LEFT, DR_LEFT}, 3},
	// {{NONE, R_RIGHT, NUL}, 5}, {{NONE, R_RIGHT, R_RIGHT}, 2},
	// {{NONE, R_RIGHT, DR_RIGHT}, 4}, {{NONE, R_RIGHT, R_LEFT}, 1},
	// {{NONE, R_RIGHT, DR_LEFT}, 3}, {{NONE, DR_RIGHT, NUL}, 5},
	// {{NONE, DR_RIGHT, R_RIGHT}, 2}, {{NONE, DR_RIGHT, DR_RIGHT}, 4},
	// {{NONE, DR_RIGHT, R_LEFT}, 1}, {{NONE, DR_RIGHT, DR_LEFT}, 3}};