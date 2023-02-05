/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/05 15:56:10 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h> //getenv
#include <stdio.h> //printf

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> //access
#include <stdbool.h>

void	print_error_and_exit(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

//add malloc failure error handling
char	*get_filepath(char *to_execute)
{
	char	*path_env;
	char	*end;
	char	*pathname;

	path_env = getenv("PATH");
	while (*path_env)
	{
		end = strchr(path_env, ':');
		if (end)
			pathname = ft_substr(path_env, 0, end - path_env);
		else
			pathname = ft_strdup(path_env);
		pathname = ft_strjoin_with_free(pathname, "/", FREE_FIRST_PARAM);
		pathname = ft_strjoin_with_free(pathname, to_execute, FREE_FIRST_PARAM);
		if (access(pathname, X_OK) == 0)
			return (pathname);
		else if (!end)
			break ;
		free(pathname);
		path_env = end + 1;
	}
	return (NULL);
}

bool	pathname_is_valid(char *pathname, char *to_execute)
{
	if (!pathname)
	{
		dprintf(STDERR_FILENO, "minishell: %s: command not found\n", to_execute);
		return (false);
	}
	return (true);
}

void	execute(char *pathname, char **argv)
{
	extern char	**environ;

	execve(pathname, argv, environ);
	print_error_and_exit("execve failure");
}

int	execute_internal_command(char *to_execute)
{
	pid_t	pid;
	char	**argv;
	char	*pathname;
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	else if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 2);
		if (!ft_strchr(to_execute, '/'))
			pathname = get_filepath(to_execute);
		else
			pathname = ft_strtrim(to_execute, " ");
		argv[0] = pathname;
		argv[1] = NULL;
		if (pathname_is_valid(pathname, to_execute))
			execute(pathname, argv);
		else
			return (127);
		free(pathname);
		free(argv);
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
