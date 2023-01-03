#include <stdlib.h>
#include "minishell.h"

#include <unistd.h>
#include <string.h>

bool	equal_op(t_token *tok, char *op);
void	append_node(t_node **node, t_node *elm);
t_node	*pipeline(t_token **rest, t_token *tok);
t_node	*simple_command(t_token **rest, t_token *tok);

// <pipeline> = <simple_command> ('|' <pipeline>)
// <simple_command> = <command_element>+
// <command_element> = <word> | <redirection>
// <redirection> = '>' <word>
//               | '<' <word>
//               | '>>' <word>
//               | '<<' <word>
t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}

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

/*
control operator
	  A token that performs a control function.  It is one of the following symbols:
	  || & && ; ;; ( ) | <newline>
*/
bool	is_control_operator(t_token *tok)
{
	static char	*const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
   Simple Commands
	   A simple command is a sequence of optional variable assignments followed
	   by blank-separated words and redirections, and terminated by a control
	   operator.  The first word specifies the command to be executed, and is
	   passed as argument zero.  The remaining words are passed as arguments to
	   the invoked command.

	   The return value of a simple command is its exit status, or 128+n if the
	   command is terminated by signal n.
*/
t_node	*simple_command(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_command_element(node, &tok, tok);
	*rest = tok;
	return (node);
}

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->filename = tokdup(tok->next);
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_append(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_heredoc(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC);
	node->delimiter = tokdup(tok->next);
	if (strchr(node->delimiter->word, SINGLE_QUOTE_CHAR) == NULL
		&& strchr(node->delimiter->word, DOUBLE_QUOTE_CHAR) == NULL)
		node->is_delim_unquoted = true;
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok));
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_in(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_append(&tok, tok));
	else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_heredoc(&tok, tok));
	else
		todo("append_command_element");
	*rest = tok;
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}

void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}
