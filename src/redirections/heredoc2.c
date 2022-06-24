#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

extern t_sh	g_sh;

int	contains_charset(char *str, char c)
{
	int	i;

	i = 0;
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

int	contain_space(char	**value)
{
	int i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == ' ')
		{
			return (i);
		}
		i++;
	}
	return (0);
}
char	*expand_env_in_heredoc(char *value)
{
	char	*new_str;
	char	*dollar_value;
	int		idx;

	idx = 0;
	new_str = NULL;
	dollar_value = NULL;
	while (value[idx])
	{
		if (value[idx] == '$')
		{
			dollar_value = noquote_dollar_manager(value, &idx, &g_sh);
			if (dollar_value != NULL)
				new_str = ft_strjoin(new_str, dollar_value);
			continue ;
		}
		else
			new_str = ft_strjoin_char(new_str, value[idx]);
		idx++;
	}
	return (new_str);
}

char	*expand_heredoc(char *str)
{
	char	*temp;

	temp = expand_env_in_heredoc(str);
	free (str);
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
		if (!ft_strncmp(str, limiter, ft_strlen(limiter))
			&& ft_strlen(str) == ft_strlen(limiter))
			return (str);
		else if (contains_charset(str, '$') == SUCCESS)
			str = expand_heredoc(str);
	}
	return (str);
}
