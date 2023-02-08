/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/08 23:54:16 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
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
		if (!pathname)
			print_error_and_exit("malloc failure");
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

void	execve_func(char *pathname, char **argv)
{
	extern char	**environ;

	execve(pathname, argv, environ);
	print_error_and_exit("execve failure");
}

int	token_count(t_token *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		count++;
		tok = tok->next;
	}
	return (count);
}

char	**make_argv(t_token *tok)
{
	int		i;
	char	**argv;

	i = 0;
	argv = ft_calloc(sizeof(char *), token_count(tok));
	if (!argv)
		print_error_and_exit("malloc failure");
	while (tok)
	{
		if (tok->type != BLANK)
		{
			argv[i] = tok->word;
			i++;
		}
		tok = tok->next;
	}
	return (argv);
}

int	exec(t_token *tok)
{
	char	**argv;
	char	*pathname;
	char	*to_execute;

	to_execute = tok->word;
	if (!ft_strchr(to_execute, '/'))
		pathname = get_filepath(to_execute);
	else
		pathname = ft_strtrim(to_execute, " ");
	argv = make_argv(tok);
	if (pathname_is_valid(pathname, to_execute))
		execve_func(pathname, argv);
	else
		return (127);
	free(pathname);
	free(argv);
	return (0);
}

int	execute(t_token *tok)
{
	pid_t	pid;
	int		wait_status;

	pid = fork();
	if (pid == -1)
		print_error_and_exit("fork failure");
	else if (pid == 0)
		exec(tok);
	else
	{
		wait(&wait_status);
		return (WEXITSTATUS(wait_status));
	}
}

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

int	main(void)
{
	char	*line;
	t_token	*tok;
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
			tok = tokenize(line);
			exit_status = execute(tok);
		}
		free(line);
		free_tokens(tok);
	}
	return (exit_status);
}