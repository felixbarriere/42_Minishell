#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

char	*process_quotes_limiter(char **value)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	printf("VALUE = %s\n", (*value));
	while ((*value)[i])
	{
		if ((*value)[i] == '\"')
			new = ft_strjoin_char_takeout(new, (*value)[i], 34);
		else if ((*value)[i] == '\'')
			new = ft_strjoin_char_takeout(new, (*value)[i], 39);
		else
			new = ft_strjoin_char(new, (*value)[i]);
		i++;
	}
	printf("NEW = %s\n", new);
	return (new);
}

int	contains_any_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	process_limiter(char **limiter, int *quotes)
{
	if (contains_any_quotes(*limiter))
	{
		(*limiter) = process_quotes_limiter(limiter);
		(*quotes) = 1;
	}
	printf("DELIMINATOR PROCES = %s\n", (*limiter));
	printf("QUOTE PROCES = %d\n", (*quotes));
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
	if (!ft_strncmp(*temp, *limiter, ft_strlen(*limiter))
		&& ft_strlen(*temp) == ft_strlen(*limiter))
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
	printf("LIMITER = %s\n", limiter);
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
		{
			printf("ICI LIMITER\n");
			break ;
		}	
		if (i > 0)
			ft_putstr_fd("\n", (*pipe_lst)->input);
		ft_putstr_fd(temp, (*pipe_lst)->input);
		printf("FREE TEMP\n");
		ft_free_null_str(&temp);
		ft_free_null_str(&limiter);
		i++;
	}
	return (0);
}

// char	*ft_strjoin_char_takeout2(char *s1, char c, char take_out, char take_out2)
// {
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	if (!s1)
// 	{
// 		s1 = malloc(sizeof(char) * 1);
// 		s1[0] = '\0';
// 	}
// 	dest = ft_calloc(sizeof(char), (ft_strlen(s1) + 2));
// 	if (!dest)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	if (take_out != c && take_out2 != c)
// 		dest[i] = c;
// 	i++;
// 	dest[i] = '\0';
// 	free(s1);
// 	return (dest);
// }


// char	*trim_quotes(char **value, int *i, int *j)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = NULL;
// 	s2 = NULL;
// 	s1 = ft_strndup(&(*value)[*j], *i - *j);
// 	*i = *i + 1;
// 	*j = *i;
// 	while ((*value)[*i] && (*value)[*i] != '\'' &&  (*value)[*i] != '\"')
// 		*i = *i + 1;
// 	if ((*value)[*i] == '\'' || (*value)[*i] == '\"')
// 		s2 = ft_strndup(&(*value)[*j], *i - *j);
// 	*j = *i + 1;
// 	printf("AVANT I = %d, J = %d\n", (*i), (*j));
	
// 	return (ft_strjoin_2(&s1, &s2));
// }



// char	*process_quotes_limiter(char **value)
// {
// 	char	*str;
// 	char	*temp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	str = NULL;
// 	while ((*value)[i])
// 	{
// 		if ((*value[i] == DOUBLE || (*value)[i] == SIMPLE))
// 		{
// 			temp = trim_quotes(value, &i, &j);
// 			printf("TEMP = %s\n", temp);
	
// 			str = ft_strjoin_2(&str, &temp);
// 		}
// 		i++;
// 		printf("I = %d, J = %d\n", i, j);
// 	}
// 	temp = ft_strndup2(&(*value)[j], i - j);
// 	return (ft_strjoin_2(&str, &temp));
// }


