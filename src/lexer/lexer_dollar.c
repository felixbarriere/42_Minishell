/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/09 18:11:36 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*isolate_dollar_in_quote(char *str)
{
	int i;
	int	j;
	int k;
	char *dollar = NULL;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			
			while (str[i] != ' ' && str[i] != '\"')
			{
				j++;
				i++;
			}
			i = (i - j);
			dollar = malloc(sizeof(char) * (j + 1));
			if (!dollar)
				return NULL;
			while (j > 0)
			{
				dollar[k] = str[i];
				k++;
				i++;
				j--;
			}
			dollar[k] = '\0';
			break ;
		}
		i++;
	}	
	return (dollar);
	printf("STR = %s\n", str);
	printf("DOLLAR = %s\n", dollar);	
}
