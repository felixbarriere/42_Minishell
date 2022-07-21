#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

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

int	contain_space(char	**value)
{
	int	i;

	i = 0;
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
