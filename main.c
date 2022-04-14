#include "include/minishell.h"
#include "include/minishell_d.h"
#include "include/minishell_f.h"
#include "include/minishell_s.h"

void	ft_init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->lenght = 0;
	sh->state_quote = DEFAULT;
	
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_sh sh;

	ft_prompt_init(&sh);
	
	return (0);
}