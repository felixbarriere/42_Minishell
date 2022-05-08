#include "../include/minishell.h"
#include "../include/minishell_d.h"
#include "../include/minishell_f.h"
#include "../include/minishell_s.h"

void ft_prompt_start(t_sh *sh)
{
	// ajouter une gestion d'erreur (check_exit);
	sh->prompt = readline("➜ minishell ");
	if ( !sh->prompt || !ft_strcmp(sh->prompt, "exit"))
	{
		clear_list(sh->token_lst);
		exit(0);
	}
	add_history(sh->prompt);
}

void	ft_prompt_init(t_sh *sh, char **env_init)
{
	ft_init_values(sh, env_init);
	ft_init_env(env_init, sh);
	while (1)
	{
		ft_prompt_start(sh); //générer un prompt avec readline() et enregistrer la commande tapée
		sh->lenght = ft_strlen(sh->prompt);
		if (!is_only_space(sh->prompt))
			lexer(sh); //analyse lexicale de la commande
		
		ft_init_values(sh, env_init);
		// ft_init_env(env_init, sh);
	}
}
