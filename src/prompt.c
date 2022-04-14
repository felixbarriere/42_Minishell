#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void ft_prompt_start(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	// ajouter une gestion d'erreur (check_exit);
	add_history(sh->prompt);
}

void	ft_prompt_init(t_sh *sh)
{
	ft_init_values(sh);
	while (1)
	{
		ft_prompt_start(sh); //générer un prompt avec readline() et enregistrer la commande tapée
		sh->lenght = ft_strlen(sh->prompt);
		
		lexer(sh); //analyse lexicale de la commande
		ft_init_values(sh);
	}
}