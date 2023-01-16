/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:20 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 06:56:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include "minishell.h"

static bool	equal_to_cwd(const char *path)
{
	struct stat	st1;
	struct stat	st2;

	ft_memset(&st1, 0, sizeof(st1));
	ft_memset(&st2, 0, sizeof(st2));
	if (stat(path, &st1) < 0)
		return (false);
	if (stat(".", &st2) < 0)
		fatal_error("stat");
	return (st1.st_ino == st2.st_ino);
}

int	builtin_pwd(char **argv)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)argv;
	pwd = xgetenv("PWD");
	if (pwd == NULL || !equal_to_cwd(pwd))
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			xperror3("pwd", "getcwd", NULL);
			return (1);
		}
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
}
