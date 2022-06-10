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

char	*expand_env(char *str, int *i, int *j, char **s1)
{
	extern t_sh	g_sh;
	char	*env_key;
	char	*env_value;

	if (!ft_strncmp(str, "$$", 2))
	{
		*s1 = ft_strjoin(*s1, "$");
		*i = *i + 1;
		*j = *i;
		return (*s1);
	}
	env_key = get_key_dollar(str, *i);
	printf("KEY = %s\n", env_key);
	env_value = get_value_dollar(&g_sh, env_key);
	printf("VALUE = %s\n", env_value);
	if (!env_key)
		*i = *i + 1;
	*i = *i + ft_strlen(env_key);
	*j = *i + 1;
	if (env_value)
		*s1 = ft_strjoin_2(s1, &env_value);
	ft_free_null_str(&env_key);
	return (*s1);
}

char	*expand_env_in_heredoc(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1 = NULL;
	printf("CHAR *VALUE = %s\n", *value);
	while ((*value)[i])
	{
		if ((*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j);
			printf("ICI - ENV\n");
			s1 = ft_strjoin_2(&s1, &s2);
			printf("ICI - ENV 2\n");
			s1 = expand_env(&(*value)[i], &i, &j, &s1);
			printf("ICI - ENV 3\n");
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j);
	printf("S2 = %s\n", s2);
	return (ft_strjoin_2(&s1, &s2));
}

char	*expand_heredoc(char **str)
{
	char	*temp;

	temp = expand_env_in_heredoc(str);
	printf("TEMP = %s\n", temp);
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