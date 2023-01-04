#include <unistd.h>
#include "minishell.h"

/*
   Pipelines
	   A pipeline is a sequence of one or more commands separated by the
	   character |.  The format for a pipeline is:

	   [time [-p]] [ ! ] command [ | command2 ... ]

	   The standard output of command is connected via a pipe to the standard
	   input of command2.  This connection is performed before any redirections
	   specified by the command (see REDIRECTION below).

	   The return status of a pipeline is the exit status of the last command,
	   unless the pipefail option is enabled.  If pipefail is enabled, the
	   pipeline's return status is the value of the last (rightmost) command to
	   exit with a non-zero status, or zero if all commands exit successfully.
	   If the reserved word !  precedes a pipeline, the exit status of that
	   pipeline is the logical negation of the exit status as described above.
	   The shell waits for all commands in the pipeline to terminate before
	   returning a value.

	   If the time reserved word precedes a pipeline, the elapsed as well as
	   user and system time consumed by its execution are reported when the
	   pipeline terminates.  The -p option changes the output format to that
	   specified by POSIX.  The TIMEFORMAT variable may be set to a format
	   string that specifies how the timing information should be displayed;
	   see the description of TIMEFORMAT under Shell Variables below.

	   Each command in a pipeline is executed as a separate process (i.e., in a
	   subshell).
*/
t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&tok, tok);
	if (equal_op(tok, "|"))
		node->next = pipeline(&tok, tok->next);
	*rest = tok;
	return (node);
}
