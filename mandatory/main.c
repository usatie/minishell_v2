/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/01/16 22:00:45 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	print_error_and_exit(char *error_message)
{
	dprintf(STDERR_FILENO, "%s\n", error_message);
	exit(1);
}

int	execute_internal_command(char *line)
{
	pid_t	pid;
	char	*argv[] = {line, NULL};
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	else if (pid == 0)
	{
		execve(line, argv, NULL);
		print_error_and_exit("execve failure");
	}
	else
	{
		wait(&wait_status);
		return (WEXITSTATUS(wait_status));
	}
}

int	main(void)
{
	char	*line;
	int		exit_status;

	rl_outstream = stderr;
	exit_status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			exit_status = execute_internal_command(line);
		}
		free(line);
	}
	return (exit_status);
}
