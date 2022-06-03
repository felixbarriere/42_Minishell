#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// void	get_commands_args(t_token *lst)
// {
// 	if (!lst)
// 		return ;
// 	while (lst)
// 	{
// 		if (lst->type == STR)
// 		{
// 			lst->type = CMD;
// 			break ;
// 		}
// 		lst = lst->next;
// 	}
// 	while (lst)
// 	{
// 		if (lst->type == STR)
// 			lst->type = ARG;
// 		lst = lst->next;
// 	}
// }

// void	get_commands(t_token *lst)
// {
// 	t_token	*temp = lst;
// 	if (!lst)
// 		return ;
// 	printf("-----AVANT------\n");
// 	print_tokens(temp);
// 	while (lst)
// 	{
// 		if (lst->type == R_LEFT)
// 			lst->next->type = INPUT;
// 		else if (lst->type == R_RIGHT)
// 			lst->next->type = OUTPUT;
// 		else if (lst->type == DR_RIGHT)
// 			lst->next->type = APPEND;
// 		else if (lst->type == STR)
// 			get_commands_args(lst);
// 		lst = lst->next;
// 	}
// 	lst = temp;
// 	printf("------APRES-----\n");
// 	print_tokens(lst);
// }

// void	get_commands1(t_sh *sh)
// {
// 	t_pipe	*temp = sh->pipe_lst;
// 	if (!sh->pipe_lst)
// 		return ;
// 	while (sh->pipe_lst)
// 	{
// 		get_commands(sh->pipe_lst->token);
// 		sh->pipe_lst = sh->pipe_lst->next;
// 	}
// 	sh->pipe_lst = temp;
// }


// void	fill_args(t_token *lst, t_sh *sh, int i)
// {
// 	sh->pipe_lst->args = malloc(sizeof(char) * i + 1);
// 	if (!sh->pipe_lst->args)
// 		return ;
// 	while (lst)
// 	{
// 		if (lst->type == ARG)
// 		{
// 			sh->pipe_lst->args[i] = ft_strdup(lst->value);
// 			i++;
// 		}
// 		lst = lst->next;
// 	}
// 	sh->pipe_lst->args[i] = NULL;
// }

int	args_number(t_token *li)
{
	int	i;
	
	i = 0;
	while (li != NULL)
	{
		if (li->type == ARG || li->type == CMD)
			i++;
		li = li->next;
	}
	return (i);
}

void	update_args(t_pipe **pipe_lst)
{
	t_token	*token;
	int		i;

	token = (*pipe_lst)->token;
	(*pipe_lst)->args = ft_calloc(args_number(token) + 1, sizeof(char *));
	if (!(*pipe_lst)->args)
		return ;
	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			(*pipe_lst)->args[i] = ft_strndup(token->value, ft_strlen(token->value));
			if (!(*pipe_lst)->args[i])
				return ;
			i++;	
		}
		token = token->next;
	}
	(*pipe_lst)->args[i] = NULL;
	return ;
}

void	get_commands_args(t_token *lst, t_sh *sh)
{
	(void)sh;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->type == STR)
		{
			lst->type = CMD;
			sh->pipe_lst->cmd = ft_strdup(lst->value);
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

void	get_commands(t_token *lst, t_sh *sh)
{
	t_token	*temp = lst;
	if (!lst)
		return ;
	// printf("-----AVANT------\n");
	// print_tokens(temp);
	while (lst)
	{
		if (lst->type == R_LEFT)
			lst->next->type = INPUT;
		else if (lst->type == R_RIGHT)
			lst->next->type = OUTPUT;
		else if (lst->type == DR_RIGHT)
			lst->next->type = APPEND;
		else if (lst->type == LIMITER)
			sh->pipe_lst->limiter = ft_strdup(lst->value);
		else if (lst->type == STR)
			get_commands_args(lst, sh);
		lst = lst->next;
	}
	lst = temp;
	// printf("------APRES-----\n");
	// print_tokens(lst);
	update_args(&sh->pipe_lst);
}

void	get_commands1(t_sh *sh)
{
	t_pipe	*temp = sh->pipe_lst;
	if (!sh->pipe_lst)
		return ;
	while (sh->pipe_lst)
	{
		get_commands(sh->pipe_lst->token, sh);
		sh->pipe_lst = sh->pipe_lst->next;
	}
	// printf("*********************\n");
	// int i = 0;
	// printf("COMMAND = %s\n", temp->cmd);
	// while (temp->args[i] != NULL)
	// {
	// 	printf("ARG = %s\n", temp->args[i]);
	// 	i++;
	// }

	sh->pipe_lst = temp;

}
