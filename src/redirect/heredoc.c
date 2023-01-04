#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

#include <string.h>

bool	readline_interrupted = false;

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
int	read_heredoc(const char *delimiter, bool is_delim_unquoted)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	readline_interrupted = false;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (readline_interrupted)
		{
			free(line);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (is_delim_unquoted)
			line = expand_heredoc_line(line);
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close(pfd[1]);
	if (readline_interrupted)
	{
		close(pfd[0]);
		return (-1);
	}
	return (pfd[0]);
}
