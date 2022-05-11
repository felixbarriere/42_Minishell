/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccalas <ccalas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:02:57 by ccalas            #+#    #+#             */
/*   Updated: 2022/05/11 16:29:14 by ccalas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

// char	*ft_line(char *line_wip)
// {
// 	char	*str;
// 	int			i;

// 	i = 0;
// 	if (line_wip[i] == '\0')
// 		return (NULL);
// 	while (line_wip[i] && line_wip[i] != '\n')
// 		i++;
// 	str = malloc(sizeof(char) * (i + 2));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (line_wip[i] && line_wip[i] != '\n')
// 	{
// 		str[i] = line_wip[i];
// 		i++;
// 	}
// 	if (line_wip[i] == '\n')
// 	{
// 		str[i] = line_wip[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_new_start(char	*line_wip)
// {
// 	char	*str;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	j = 0;
// 	while (line_wip[i] && line_wip[i] != '\n')
// 		i++;
// 	if (line_wip[i] == '\0')
// 	{
// 		free(line_wip);
// 		return (NULL);
// 	}	
// 	str = malloc(sizeof(char) * (ft_strlen(line_wip) - i + 1));
// 	if (!str)
// 		return (NULL);
// 	i++;
// 	while (line_wip[i])
// 		str[j++] = line_wip[i++];
// 	str[j] = '\0';
// 	free(line_wip);
// 	return (str);
// }

// char	*ft_read_fd(char *str, char *line_wip)
// {
// 	char	*buff;
// 	int		bits;

// 	bits = 1;
// 	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buff)
// 		return (NULL);
// 	while (!ft_strchr(line_wip, '\n') && bits > 0)
// 	{
// 		bits = read(fd, buff, BUFFER_SIZE);
// 		if (bits == -1)
// 		{
// 			free (buff);
// 			return (NULL);
// 		}
// 		buff[bits] = '\0';
// 		line_wip = ft_strjoin(line_wip, buff);
// 	}
// 	free (buff);
// 	return (line_wip);
// }


char *get_value_dollar(t_sh	*sh, char *str, int i)
{
	int		j;
	int		k;
	char	*key;
	char 	*key_trim;
	char	*value;
	
	j = 0;
	while (str[i] != ' ' && str[i] != '\"')
	{
		j++;
		i++;
	}
	i = (i - j);
	key = ft_calloc((j + 1), sizeof(char));
	if (!key)
		return NULL;
	k = 0;
	while (j > 0 && str[i])
	{
		key[k] = str[i];
		k++;
		i++;
		j--;
	}
	key[k] = '\0';
	key_trim = ft_strtrim(key, "$\"|\'");
	value = expander(sh, key_trim);
	printf("value= %s\n", value);

	return (value);
}

char	*isolate_dollar_in_quote_2(char *str, t_sh *sh)
{
	int i;
    int l;
    char	*value = NULL;
    char	*str_wip = NULL;
    // char	*str_wip_2 = NULL;

	(void)sh;
	i = 0;
    l = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
            value = get_value_dollar(sh, str, i);
            printf("value= %s\n", value);
            l = 0;
			printf("%d", i);
			// str_wip = ft_strndup(str, i);
			// printf("%s\n", str_wip);
            str_wip = ft_strjoin(str_wip, value);
            printf("str finale = %s\n", str_wip);
            i = i + ft_strlen(value) - 2; //ft_strlen (str_wip);
        }
		else
		{
			printf("test ");
			str_wip = ft_strjoin_char(str_wip, str[i]);
			printf("%s\n", str_wip);
		}
		i++;
	}
	return (str_wip);
}


// char	*isolate_dollar_in_quote_2(char *str, t_sh *sh)
// {
// 	int i;
// 	int	j;
// 	int k;
//     int l;
// 	char	*dollar = NULL;
//     char	*dollar2 = NULL;
//     char	*value = NULL;
//     char	*str_wip = NULL;
//     char	*str_2 = NULL;

// 	i = 0;
// 	j = 0;
// 	k = 0;
//     l = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			j = 0;
// 			while (str[i] != ' ' && str[i] != '\"')
// 			{
// 				j++;
// 				i++;
// 			}
// 			i = (i - j);
// 			dollar = ft_calloc((j + 1), sizeof(char));
// 			if (!dollar)
// 				return NULL;
//             k = 0;
// 			while (j > 0 && str[i])
// 			{
//                 printf("i = %d, j = %d, k = %d\n", i, j, k);
// 				dollar[k] = str[i];
// 				k++;
// 				i++;
// 				j--;
// 			}
// 			dollar[k] = '\0';
//             printf("DOLLAR = %s\n", dollar);
//             dollar2 = ft_strtrim(dollar, "$\"|\'");
//             printf("DOLLAR2 = %s\n", dollar2);
//             value = expander(sh, dollar2);
//             printf("value= %s\n", value);
//             i = i - ft_strlen(dollar);
//             str_wip = ft_calloc((i + 1), sizeof(char));
//             l = 0;
//             while (l < i && str[l])
//             {
//                 str_wip[l] = str[l];
//                 l++;
//                 // i--;
//             }
//             str_wip[l] = '\0';
//             str_2 = ft_strjoin(str_wip, value);
//             printf("str finale = %s\n", str_2);
//         }
// 		i++;
// 	}	
// 	return (str);
// }


char	*dollar_in_quote(char *str, t_sh *sh)
{
	char		*str_wip;
	// static char	*line_wip;
    // printf("test\n");
	str_wip = isolate_dollar_in_quote_2(str, sh);
    printf("STR_WIP = %s", str_wip);
	// if (!line_wip)
	// 	return (NULL);
	// line = ft_line(line_wip);
	// line_wip = ft_new_start(line_wip);
	return (str_wip);
}