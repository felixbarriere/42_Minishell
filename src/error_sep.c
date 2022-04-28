#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

int	check_error_sep(t_token *token_lst)
{
	while(token_lst->next)
	{
		// if (token_lst->type == PIPE && token_lst->next->type == PIPE /*&& token_lst->prev->type == PIPE*/ )
		// 	printf("ca va pas du tout\n");
		
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


