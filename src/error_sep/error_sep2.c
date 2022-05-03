#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	check_error_sep_3(t_token *token_lst)
{
	printf("CHECK 3\n");
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, DR_LEFT)) 
		|| (is_type(token_lst, DR_LEFT)	&& is_type(token_lst->next, DR_LEFT)) 
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, DR_LEFT)) 
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, DR_LEFT)))
	{
		printf("ERROR 3\n");
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_4(t_token *token_lst)
{
	printf("CHECK 4\n");
	if ((is_type(token_lst, R_LEFT) && is_type(token_lst->next, DR_RIGHT)) 
		|| (is_type(token_lst, DR_LEFT) && is_type(token_lst->next, DR_RIGHT))
		|| (is_type(token_lst, R_RIGHT) && is_type(token_lst->next, DR_RIGHT))
		|| (is_type(token_lst, DR_RIGHT) && is_type(token_lst->next, DR_RIGHT)))
	{
		printf("ERROR 4\n");
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_5(t_token *token_lst)
{
	printf("CHECK 5\n");
	if ((is_type(token_lst->prev, BLANK) && is_type(token_lst, R_LEFT) 
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_LEFT)
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, R_RIGHT)
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, BLANK) && is_type(token_lst, DR_RIGHT)
			&& is_type(token_lst->next, BLANK)))
	{
		printf("ERROR 5\n");
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	else if (is_type(token_lst->prev, BLANK) && is_type(token_lst, PIPE)
			&& is_type(token_lst->next, BLANK))
	{
		printf("ERROR 5\n");
		ft_putstr_fd("syntax error near unexpected token `|'", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_error_sep_6(t_token *token_lst)
{
	printf("CHECK 6\n");
	if ((is_type(token_lst->prev, STR) && is_type(token_lst, R_LEFT) 
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, DR_LEFT)
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, R_RIGHT)
			&& is_type(token_lst->next, BLANK)) 
		|| (is_type(token_lst->prev, STR) && is_type(token_lst, DR_RIGHT)
			&& is_type(token_lst->next, BLANK))
		|| (is_type(token_lst, R_LEFT) && is_type(token_lst->next, BLANK)))
	{
		printf("ERROR 6\n");
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}