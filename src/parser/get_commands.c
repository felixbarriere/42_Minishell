#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"


void	get_commands_args(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == STR)
		{
			lst->type = CMD;
			break ;
		}
		lst = lst->next;
	}
	while (lst)
	{
		if (lst->type == STR)
			lst->type = ARG;
		lst = lst->next;
	}
}

void	get_commands(t_token *lst)
{
	int	counter;

	counter = 0;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == R_LEFT)
			lst->next->type = INPUT;
		else if (lst->type == R_RIGHT)
			lst->next->type = OUTPUT;
		else if (lst->type == DR_RIGHT)
			lst->next->type = APPEND;
		else if (lst->type == STR)
			get_commands_args(lst);
		lst = lst->next;
	}
}
