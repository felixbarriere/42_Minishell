/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:12:23 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/13 16:30:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// si "." faire un ch sur pwd
// si ".." couper pwd jusqu'a l'avant dernier "/"

void	cd_command(t_pipe	*pipe)
{
	(void)pipe;
	printf("commande cd!\n");

	printf("commande: %s\n", pipe->cmd);
	printf("options: %s\n", pipe->options); //comment retrouver les options? token?
	if (pipe->token->next != NULL)
		printf("options_2: %s\n", pipe->token->next->value); //fonctionne

	char cwd[256];
	// int	cd;
	// int	i;

	// i = 0;
	// while (cwd[i])
	// 	i++;
	// while (cwd[i] != '/')
	// {
	// 	//delete char ('/' inclu);
	// }


	// if (getcwd(cwd, sizeof(cwd)) == NULL)
	// 	write (2, "error pwd\n", 10);
	
	// cd = chdir(cwd);

}