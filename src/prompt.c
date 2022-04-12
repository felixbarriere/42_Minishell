#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	//printf("sh->prompt: %s\n", sh->prompt);
	//il faut stocker la commande entrée dans le prompt dans l'historique, voir la fonction
}

void	ft_prompt_init(t_sh *sh)
{
	ft_init_values(sh);
	while (1)
	{
		ft_prompt_start(sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(sh); //analyse lexicale de la commande
		ft_init_values(sh);
	}
}