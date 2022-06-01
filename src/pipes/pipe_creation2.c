void	pipe_creation(t_token **token_lst,t_pipe **pipe_lst, t_pipe **pipe_start, t_token **token_start)
{	
	// t_pipe	pipe_lst;
	int	i = 0;
	// t_token	*token = sh->pipe_lst->token;
	// t_pipe	*pipe = sh->pipe_lst;
	// t_sh	*sh = sh;
	
	*pipe_lst = NULL;


	while (*token_lst != NULL)
	{
		if ((*token_lst)->type != PIPE)
		{
			printf("PIPE_LIST %d\n", i);
			*pipe_lst = add_back_pipe_token(*pipe_lst, *token_lst);
			printf("pipe: %s\n", (*pipe_lst)->token->value);
			*token_lst = (*token_lst)->next;
		}

		while ((*token_lst) != NULL && (*token_lst)->type != PIPE)
		{
			printf("TOKEN IN PIPE %d\n", i);
			printf("2: %s\n", (*token_lst)->value);
			(*pipe_lst)->token = *token_lst;

			// sh->pipe_lst->token = add_back_token_in_pipe(sh->pipe_lst->token, sh->token_lst);

			printf("%s\n", (*pipe_lst)->token->value);
			// printf("prev: %s\n", sh->pipe_lst->prev->token->value);
			*token_lst = (*token_lst)->next;
			(*pipe_lst)->token = (*pipe_lst)->token->next;
		}
		i++;
		if (*token_lst != NULL)
			*token_lst = (*token_lst)->next;
		if (*pipe_lst)
			*pipe_lst = (*pipe_lst)->next; //normalement pas obligatoire
	}
	*pipe_lst = *pipe_start;
	*token_lst = *token_start;
	// printf("pipe_final: %s\n", sh->pipe_lst->prev->token->value);
	printf("pipe final: %s\n", (*token_lst)->value);
	
	// while (sh->token_lst->prev)
	// {
	// 	// printf("pipe final: %s\n", sh->token_lst->value);
	// }
	// sh->token_lst = sh->token_lst->prev;
	// printf("pipe final: %s\n", sh->token_lst->prev->value);
}


// t_token	*ft_strdup_token(t_token *value)
// {
// 	t_token	*dest;
// 	int		i;

// 	i = 0;
// 	dest = ft_calloc(1, sizeof(t_token));
// 	if (!dest)
// 		return (NULL);
// 	dest->type = value->type;
// 	dest->value = value->value;
// 	dest->prev = value->prev;
// 	dest->next = value->next;
// 	return (dest);
// }