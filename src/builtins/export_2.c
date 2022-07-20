/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:51 by fbarrier          #+#    #+#             */
/*   Updated: 2022/07/20 19:55:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_equal(char *str, t_sh *sh)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isdigit(str[0])
		&&(ft_isalnum(str[i]) == 1 || str[i] == '_' || str[i] == '=' || (str[i] == '+' && str[i + 1] == '=') ))
	{
		if (str[i] == '=' && i > 0)
			return (1);
		i++;
	}
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	sh->exit = 1;
	return (0);
}

// void	update_path_export(t_sh *sh, char *key)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_strcmp(key, "PATH"))
// 	{
// 		printf("test\n");
// 		printf("path avant :%s\n", sh->path[0]);
// 		while (sh->path[i])
// 		{
// 			free(sh->path[i]);
// 			i++;
// 		}
// 		free(sh->path[i]);
// 		free(sh->path);
// 		sh->path = NULL;
// 		if (sh->path)
// 			printf("path avant :%s\n", sh->path[0]);
// 	}
// }

char	*delete_plus(char *src)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		if (src[i] == '+' && src[i + 1] == '=')
		{
			i++;
			// free (dest)
		}

		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
