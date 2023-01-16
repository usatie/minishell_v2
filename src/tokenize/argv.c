/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:52 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 21:51:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

static size_t	argv_len(t_token *tok)
{
	size_t	len;

	len = 0;
	while (tok && !at_eof(tok))
	{
		len++;
		tok = tok->next;
	}
	return (len);
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;
	size_t	i;

	argv = xcalloc(argv_len(tok) + 1, sizeof(char *));
	i = 0;
	while (tok && !at_eof(tok))
	{
		argv[i] = xstrdup(tok->word);
		i++;
		tok = tok->next;
	}
	return (argv);
}
