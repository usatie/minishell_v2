/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/03/15 17:15:54 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

#include <stdlib.h> //getenv

void	run_command(char *line)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	node = parser(tok);
	/*
	if (!error)
	{
		//expand(node);
		set_up_redirect(node);
		execute(node);
		reset_redirect(node);
	}
	else
		set_exit_status
	*/
	free_tokens(tok);
	free_nodes(node);
}

int	main(void)
{
	char	*line;

	// rl_outstream = stderr;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			run_command(line);
			free(line);
		}
	}
}
