#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

int	contains_charset(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	process_eof(char **temp, t_pipe **pipe_lst)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
	ft_free_null_str(temp);
	close((*pipe_lst)->input);
	unlink((*pipe_lst)->limiter_name);
	ft_free_null_str(&(*pipe_lst)->limiter_name);
	return (1);
}

char	*expand_env_in_heredoc(char **value)
{
	extern t_sh	g_sh;
	char	*new_str;
	char	*dollar_value;
	int		idx;

	idx = 0;
	new_str = NULL;
	dollar_value = NULL;
	printf("CHAR *VALUE = %s\n", *value);
	while ((*value)[idx])
	{
		printf("VALUE[%d] = %c\n", idx, (*value)[idx]);
		if ((*value)[idx] == '$')
		{
				dollar_value = noquote_dollar_manager((*value), &idx, &g_sh);
				printf("DOLLAR VALUE = %s\n", dollar_value);
				if (dollar_value != NULL)
					new_str = ft_strjoin(new_str, dollar_value);
				continue ;
		}
		else
				new_str = ft_strjoin_char(new_str, (*value)[idx]);
		idx++;
	}
	return (new_str);
}

char	*expand_heredoc(char **str)
{
	char	*temp;

	temp = expand_env_in_heredoc(str);
	ft_free_null_str(str);
	return (temp);
}

char	*read_heredoc(t_pipe **pipe_lst, int quotes, char *limiter)
{
	char	*str;
	str = readline("> ");
	if (!str)
	{
		process_eof(&str, pipe_lst);
		return (NULL);
	}
	if (!quotes)
	{
		if (!ft_strncmp(str, limiter, ft_strlen(limiter)) && ft_strlen(str) == ft_strlen(limiter))
			return (str);
		else if (contains_charset(str, '$') == SUCCESS)
			str = expand_heredoc(&str);
	}
	return (str);
}

// char	*expand_env_in_heredoc(char **value)
// {
// 	char	*s1;
// 	char	*s2;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	s1 = NULL;
// 	printf("CHAR *VALUE = %s\n", *value);
// 	while ((*value)[i])
// 	{
// 		if ((*value)[i] == '$')
// 		{
// 			s2 = ft_strndup(&(*value)[j], i - j);
// 			printf("ICI - ENV\n");
// 			s1 = ft_strjoin_2(&s1, &s2);
// 			printf("ICI - ENV 2\n");
// 			s1 = expand_env(&(*value)[i], &i, &j, &s1);
// 			printf("ICI - ENV 3\n");
// 		}
// 			printf("i = %d\n", i);
// 		i++;
// 	}
// 	printf("i = %d ERREUR BIENTOT ?\n", i);
// 	s2 = ft_strndup(&(*value)[j], i - j);
// 	printf("S2 = %s\n", s2);
// 	// ft_free (value);
// 	return (ft_strjoin_2(&s1, &s2));
// }

// int	token_heredoc(t_sh *sh)
// {
// 	char	*str;
// 	char	*new_str;
// 	char	*temp;
// 	char	*dollar_value;
// 	int		idx;

// 	idx = 0;
// 	temp = NULL;
// 	new_str = NULL;
// 	dollar_value = NULL;
// 	str = string_token(sh, &sh->prompt[sh->p_index]);
// 	if (ft_lstlast_dr_left(sh->token_lst) == SUCCESS)
// 	{
// 		if (str != NULL)
// 			sh->token_lst = add_back_token(sh->token_lst, LIMITER, str);
// 		return (idx);
// 	}
// 	else
// 	{
// 		while (str[idx])
// 		{
// 			if (str[idx] == '\"' || str[idx] == '\'')
// 			{
// 				temp = quotes_manager(str, &idx, sh);
// 				if (temp != NULL)
// 					new_str = ft_strjoin(new_str, temp);
// 				free(temp);
// 			}
// 			else if (str[idx] == '$')
// 			{
// 				if (str[idx + 1] == '\'' || str[idx + 1] == '\"')
// 				{
// 					idx++;
// 					continue ;
// 				}
// 				dollar_value = noquote_dollar_manager(str, &idx, sh);
// 				if (dollar_value != NULL)
// 					new_str = severals_wds_value(sh, dollar_value, new_str);
// 				continue ;
// 			}
// 			else
// 				new_str = ft_strjoin_char(new_str, str[idx]);
// 			idx++;
// 		}
// 	}
// 	if (new_str != NULL)
// 		sh->token_lst = add_back_token(sh->token_lst, STR, new_str);
// 	free(str);
// 	return (new_str);
// }
