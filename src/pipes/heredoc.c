#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*trim_quotes(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != '\'' &&  (*value)[*i] != '\"')
		*i = *i + 1;
	if ((*value)[*i] == '\'' || (*value)[*i] == '\"')
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	printf("JOIN 2 = %s\n", ft_strjoin_2(&s1, &s2));
	return (ft_strjoin_2(&s1, &s2));
}

char	*process_quotes_limiter(char **value)
{
	char	*str;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = NULL;
	while ((*value)[i] != '\0')
	{
		if ((*value[i] == '\'' || (*value)[i] == '\"'))
		{
			temp = trim_quotes(value, &i, &j);
			str = ft_strjoin_2(&str, &temp);
		}
		i++;
	}
	temp = ft_strndup(&(*value)[i], i - j);
	return (ft_strjoin_2(&str, &temp));
}

int	contains_any_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	process_limiter(char **limiter, int *quotes)
{
	if (contains_any_quotes(*limiter) == SUCCESS)
	{
		(*limiter) = process_quotes_limiter(limiter);
		(*quotes) = 1;
	}
}

char	*filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close (file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_2(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	printf("FILENAME 2 = %s\n", filename);
	free (nbr); // ?
	close(file_exists);
	return (filename);
}

int	init_heredoc(t_pipe **pipe_lst)
{
	(*pipe_lst)->limiter_name = filename();
	printf("FILENAME = %s\n", (*pipe_lst)->limiter_name);
	(*pipe_lst)->heredoc_mode = 1;
	(*pipe_lst)->input = open((*pipe_lst)->limiter_name, O_RDWR | O_CREAT | O_APPEND, 00644);
	if ((*pipe_lst)->input == -1)
		return (1);
	return (0);
}

int	is_limiter(char **temp, char **limiter)
{
	if (!strncmp(*temp, *limiter, ft_strlen(*limiter)) && ft_strlen(*temp) == ft_strlen(*limiter))
	{
		ft_free_null_str(temp);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	heredoc(char *limiter, t_pipe **pipe_lst)
{
	char	*temp;
	int		i;
	int		quotes;

	quotes = 0;
	process_limiter(&limiter, &quotes);
	if (init_heredoc(pipe_lst))
		return (1);
	i = 0;
	while (1)
	{
		temp = read_heredoc(pipe_lst, quotes, limiter);
		if (!temp)
			return (1);
		if (is_limiter(&temp, &limiter) == SUCCESS)
			break ;
		if (i > 0)
			ft_putstr_fd("\n", (*pipe_lst)->input);
		ft_putstr_fd(temp, (*pipe_lst)->input);
		ft_free_null_str(&temp);
		i++;
	}
	return (0);
}