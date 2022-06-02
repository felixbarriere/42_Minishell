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
	t_token	*temp = lst;
	if (!lst)
		return ;
	printf("-----AVANT------\n");
	print_tokens(temp);
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
	lst = temp;
	printf("------APRES-----\n");
	print_tokens(lst);
}

void	get_commands1(t_sh *sh)
{
	t_pipe	*temp = sh->pipe_lst;
	if (!sh->pipe_lst)
		return ;
	while (sh->pipe_lst)
	{
		get_commands(sh->pipe_lst->token);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	sh->pipe_lst = temp;
}
