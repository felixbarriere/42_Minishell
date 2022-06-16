/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:12:23 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/16 10:46:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	cd_command(t_pipe	*pipe)
{
	char	*wrong_path;
	char	old_path[256];
	char	path[256];

	getcwd(old_path, sizeof(old_path));
	printf("commande: %s\n", pipe->cmd);
	printf("options: %s\n", pipe->options); //comment retrouver les options? token?
	if (pipe->token->next != NULL)
	{
		printf("options_2: %s\n", pipe->token->next->value); //fonctionne
		if (chdir(pipe->token->next->value) == -1)
		{
			wrong_path = pipe->token->next->value;
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(wrong_path, 2);
			ft_putchar_fd('\n', 2);
		}
	}
	else 
		ft_putstr_fd("cd: no path\n", 2);

	getcwd(path, sizeof(path));

	//changer les var d'environnement. Faire un cwd apres l'execution pour avoir 
	// le nouveau repertoire et remplacer la var PATH avec.
	// faire un nouveau cwd et le mettre en value de PATH.
	// egalement modifier OLD_PATH.
	// attention à ce que les variables ne se réinitialisent pas à chaque prompt.
	//les valeurs sont deja dans old_path et path;

}