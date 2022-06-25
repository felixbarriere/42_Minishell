#include "../../include/minishell.h"
#include "../../include/minishell_d.h"
#include "../../include/minishell_f.h"
#include "../../include/minishell_s.h"

void	open_fdout(t_token *token, t_pipe **pipe_lst)
{
	printf("token value = %s\n", token->value);
	if (token->type == OUTPUT)
	{
		printf("OUPUT BEFORE = %d\n", (*pipe_lst)->output);
		(*pipe_lst)->output = open(token->value, O_WRONLY
				| O_CREAT | O_TRUNC, 00644);
		(*pipe_lst)->append_mode = 0;
		// printf("TEST OPEN FDOUT\n");
		// printf("OUPUT = %d\n", (*pipe_lst)->output);
	}
	else
	{
		(*pipe_lst)->output = open(token->value, O_WRONLY
				| O_CREAT | O_APPEND, 00644);
		(*pipe_lst)->append_mode = 1;
	}
}

int	update_fdout(t_pipe **pipe_lst)
{
	t_token	*temp;

	temp = (*pipe_lst)->token;
	while (temp)
	{
		if (temp->type == OUTPUT || temp->type == APPEND)
		{
			printf("TEST 1\n");
			if ((*pipe_lst)->output != 1)
				close ((*pipe_lst)->output);
			open_fdout(temp, pipe_lst);
			if ((*pipe_lst)->output == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	open_fdin(char	*value, t_pipe **pipe_lst)
{
	(*pipe_lst)->input = open(value, O_RDONLY);
	if ((*pipe_lst)->input == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	close_fdin(t_pipe **pipe_lst)
{
	if ((*pipe_lst)->input != 0)
		close((*pipe_lst)->input);
	if ((*pipe_lst)->heredoc_mode == 1)
	{
		(*pipe_lst)->heredoc_mode = 0;
		unlink((*pipe_lst)->limiter);
	}
}

int	update_fdin(t_pipe **pipe_lst)
{
	t_token	*temp;
	int		error;

	error = 0;
	temp = (*pipe_lst)->token;
	while (temp)
	{
		if (temp->type == INPUT || temp->type == LIMITER)
		{
			if (temp->type == INPUT)
				error = open_fdin(temp->value, pipe_lst);
			else
				error = heredoc(temp->value, pipe_lst);
			if (error)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

	// elem->input = 0;
	// elem->output = 1;
	// elem->append_mode = 0;
	// elem->heredoc_mode = 0;