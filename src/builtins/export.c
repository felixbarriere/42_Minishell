/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrier <fbarrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:08:45 by fbarrier          #+#    #+#             */
/*   Updated: 2022/06/23 17:52:04 by fbarrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

// char	**copy_array(t_sh *sh)
// {
// 	char	**env_temp;
// 	int		i;

// 	i = 0;
// 	while(sh->env[i]) //fonction a part?
// 		i++;
// 	env_temp = malloc(sizeof(char *) * (i + 1));
// 	if (!env_temp)
// 		return (NULL);
// 	i = 0;
// 	while (sh->env[i])
// 	{
// 		env_temp[i] = ft_strdup(sh->env[i]);
// 		i++;
// 	}
// 	env_temp[i] = NULL;


// 	// ft_free(env_temp);

// 	return(env_temp);
// }

void	add_array_export(t_sh *sh, char *value)
{
	char	**env_temp;
	int		i;

	i = 0;
	while(sh->env[i]) //fonction a part?
		i++;
	env_temp = malloc(sizeof(char *) * (i + 1));
	if (!env_temp)
		return ;
	i = 0;
	while (sh->env[i])
	{
		env_temp[i] = ft_strdup(sh->env[i]);
		i++;
	}
	env_temp[i] = NULL;
	ft_free(sh->env);
	sh->env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env_temp[++i])
		sh->env[i] = ft_strdup(env_temp[i]);
	sh->env[i++] = ft_strdup(value);
	sh->env[i] = NULL;
	// i = 0;
	printf("array ===> %s\n", env_temp[i - 2]);
	printf("array2 ===> %s\n", sh->env[i - 1]);
	ft_free(env_temp);
}




void	export_command(t_sh *sh)
{
	// (void)sh;
	// char	**key_value;
	// char	*value;
	// char	*key;
	int		index;

	index = 0;
	printf("commande export baby\n");
	if (sh->pipe_lst->token->next)
	{
		printf("==> %s\n", sh->pipe_lst->token->next->value);
		if (contains_equal(sh->pipe_lst->token->next->value))
		{
			printf("contient un =\n");
			orchestrate_env_token(sh->pipe_lst->token->next->value, sh, index);

			add_array_export(sh, sh->pipe_lst->token->next->value);

			// sh->env_lst = add_back_env_token(sh->env_lst, value, key, index);
		}
	}
	else
		env_command(sh);
}