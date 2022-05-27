/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:20:48 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/27 17:20:29 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (sh->prompt[sh->p_index] == R_LEFT
		&& sh->prompt[sh->p_index + 1] == R_LEFT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DR_LEFT, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == R_RIGHT
		&& sh->prompt[sh->p_index + 1] == R_RIGHT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DR_RIGHT, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == R_LEFT)
		sh->token_lst = add_back_token(sh->token_lst, R_LEFT, "<");
	else if (sh->prompt[sh->p_index] == R_RIGHT)
		sh->token_lst = add_back_token(sh->token_lst, R_RIGHT, ">");
}

int	token_str(t_sh *sh)
{
	char	*str;
	char	*new_str;
	char	*temp;
	char	*dollar_value;
	int		idx;

	idx = 0;
	temp = NULL;
	new_str = NULL;
	dollar_value = NULL;
	str = string_token(sh, &sh->prompt[sh->p_index]);
	printf("\nSTR EN COURS = %s\n", str);
	while (str[idx])
	{
		if (str[idx] == '\"' || str[idx] == '\'')
		{
			temp = quotes_manager(str, &idx, sh);
			if (temp != NULL)
				new_str = ft_strjoin(new_str, temp);
			free(temp);
		}
		else if (str[idx] == '$')
		{
			dollar_value = noquote_dollar_manager(str, &idx, sh);
			printf("VALUE : %s\n", dollar_value);
			if (dollar_value != NULL)
				new_str = severals_wds_value(sh, dollar_value, new_str);
			printf("new_str = %s\n", new_str);
			continue ;
		}
		else
			new_str = ft_strjoin_char(new_str, str[idx]);
		idx++;
	}
	sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
	free(str);
	return (idx);
}

/* 
Ajoute le bon token à la liste chainée des tokens sh->token_lst
*/
void	tokenizer(t_sh *sh)
{
	while (sh->prompt[sh->p_index])
	{
		while (sh->prompt[sh->p_index] && sh->prompt[sh->p_index] == ' ')
			sh->p_index++;
		if (is_in_charset(sh->prompt[sh->p_index]))
		{
			if (sh->prompt[sh->p_index] == PIPE)
				sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
			else
				process_redirect_token(sh);
		}
		else if (sh->prompt[sh->p_index])
			token_str(sh);
		sh->p_index++;
	}
}


// AU CAS OU  AVANT NORME

// int	token_str(t_sh *sh)
// {
// 	char 	*str;
// 	char 	*new_str;
// 	char	*temp;
// 	char	*dollar_value;
// 	int		idx;
// 	int		len;

// 	idx = 0;
// 	temp = NULL;
// 	new_str = NULL;
// 	dollar_value = NULL;
// 	str = string_token(sh, &sh->prompt[sh->p_index]);
// 	len = ft_strlen(str);
// 	printf("\nSTR EN COURS = %s\n", str);
// 	while(str[idx])
// 	{
// 		if (str[idx] == '\"' || str[idx] == '\'')
// 		{
// 			/* retourne une chaine sans quote et change le $ ou pas */
// 			temp = quotes_manager(str, &idx, sh);
// 			/* join la chaine */
// 			if (temp != NULL)
// 				new_str = ft_strjoin(new_str, temp);
// 			// FREE TEMP ?
// 			free(temp);
// 		}
// 		else if (str[idx] == '$')
// 		{
// 			/* dollar_manager(); retourne une chaine avec la valeur du dollar */
// 			dollar_value = noquote_dollar_manager(str, &idx, sh);
// 			// if (!dollar_value)
// 			// {
// 			// 	printf("VALUE NULL: %s\n", dollar_value);
// 			// 	new_str = ft_strjoin(new_str, temp);
// 			// 	// free(dollar_value);
// 			// 	break;
// 			// }
// 			printf("VALUE : %s\n", dollar_value);
// 			if (dollar_value != NULL)
// 				new_str = severals_wds_value(sh, dollar_value, new_str);
// 			// if (ft_strcmp(dollar_value, "$"))
// 				// free(dollar_value);
// 			printf("new_str = %s\n", new_str);
// 			continue;
// 		}
// 		else
// 			new_str = ft_strjoin_char(new_str, str[idx]);
// 		printf("new_str2 = %s\n", new_str);
// 		// if (idx < len) //protection sans doute plus necessaire a cause du continue 
// 			idx++;
// 	}
// 	sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
// 	free(str);
	
// 	return (len);
// }