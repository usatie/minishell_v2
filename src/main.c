/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:39 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 11:16:54 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

t_context	g_ctx = {};

void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (g_ctx.syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok);
		if (g_ctx.syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	initenv();
	setup_signal();
	g_ctx.last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_ctx.last_status);
		free(line);
	}
	exit(g_ctx.last_status);
}
