/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:47 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 10:50:26 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node(t_node **node, t_node *elm);

/*
control operator
	  A token that performs a control function.  It is one of the following
      symbols:
	  || & && ; ;; ( ) | <newline>
*/
bool	is_control_operator(t_token *tok)
{
	static char *const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")",
		"|", "\n"};
	size_t				i;

	i = 0;
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
		parse_error("append_command_element", &tok, tok);
	*rest = tok;
}
