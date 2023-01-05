/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:48 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 22:27:05 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "ft_printf.h"
#include "minishell.h"

/*
   Here Documents
	   This type of redirection instructs the shell to read input from the
	   current source until a line containing only word (with no trailing
	   blanks) is seen.  All of the lines read up to that point are then used
	   as the standard input for a command.

	   The format of here-documents is:

              <<[-]word
                      here-document
              delimiter

	   No parameter expansion, command substitution, arithmetic expansion, or
	   pathname expansion is performed on word.  If any characters in word are
	   quoted, the delimiter is the result of quote removal on word, and the
	   lines in the here-document are not expanded.  If word is unquoted, all
	   lines of the here-document are subjected to parameter expansion, command
	   substitution, and arithmetic expansion.  In the latter case, the
	   character sequence \<newline> is ignored, and \ must be used to quote
	   the characters \, $, and `.

	   If the redirection operator is <<-, then all leading tab characters are
	   stripped from input lines and the line containing delimiter.  This
	   allows here-documents within shell scripts to be indented in a natural
	   fashion.
*/

static void	readline_heredoc_loop(int pfd[2], const char *delimiter,
		bool is_delim_unquoted)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_ctx.readline_interrupted
			|| ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heredoc_line(line);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
}

int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	g_ctx.readline_interrupted = false;
	readline_heredoc_loop(pfd, delimiter, is_delim_unquoted);
	close(pfd[1]);
	if (g_ctx.readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}
