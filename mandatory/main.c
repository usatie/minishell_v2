/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:26:06 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/28 16:59:14 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//
int	main(void)
{
	char	*line;
	int		wstatus;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		wstatus = system(line);
		free(line);
	}
	return (WEXITSTATUS(wstatus));
}
