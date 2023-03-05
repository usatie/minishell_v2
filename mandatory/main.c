/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/18 07:36:34 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

#include <stdlib.h> //getenv

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->word);
		free(tmp);
	}
}

void	free_nodes(t_node *nodes)
{
	t_node	*tmp;

	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		free (tmp);
	}
}

int	main(void)
{
	char	*line;
	t_token	*tok;
	t_node	*node;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tok = tokenize(line);
			node = parser(tok);
			expand(node);
			execute(node);
		}
		free(line);
		free_tokens(tok);
		free_nodes(node);
	}
	// return (exit_status);
}
