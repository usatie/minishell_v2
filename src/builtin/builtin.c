/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:53:03 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 09:25:08 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

int	exec_builtin(t_node *node)
{
	int		status;
	char	**argv;

	do_redirect(node->command->redirects);
	argv = token_list_to_argv(node->command->args);
	if (strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv);
	else if (strcmp(argv[0], "export") == 0)
		status = builtin_export(argv);
	else if (strcmp(argv[0], "unset") == 0)
		status = builtin_unset(argv);
	else if (strcmp(argv[0], "env") == 0)
		status = builtin_env(argv);
	else if (strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv);
	else if (strcmp(argv[0], "echo") == 0)
		status = builtin_echo(argv);
	else if (strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(argv);
	else
		todo("exec_builtin");
	free_argv(argv);
	reset_redirect(node->command->redirects);
	return (status);
}

bool	is_builtin(t_node *node)
{
	const char			*cmd_name;
	static const char	*builtin_commands[] = {"exit", "export", "unset", "env",
		"cd", "echo", "pwd"};
	unsigned int		i;

	if (node == NULL || node->command == NULL | node->command->args == NULL
		|| node->command->args->word == NULL)
		return (false);
	cmd_name = node->command->args->word;
	i = 0;
	while (i < sizeof(builtin_commands) / sizeof(*builtin_commands))
	{
		if (strcmp(cmd_name, builtin_commands[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
