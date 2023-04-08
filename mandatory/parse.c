/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/03/14 20:46:54 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

t_token	*tokdup(t_token *tok)
{
	char	*word_dup;

	word_dup = ft_strdup(tok->word);
	if (!word_dup)
		print_error_and_exit("strdup failure");
	return (make_token(word_dup, tok->type));
}

t_token	*arg_last(t_token *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void	append_token(t_token **args, t_token *tok_to_add)
{
	t_token	*last_arg;

	if (!*args)
		*args = tok_to_add;
	else
	{
		last_arg = arg_last(*args);
		last_arg->next = tok_to_add;
	}
}

void	print_parser_error(char *location)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

t_node	*make_node(t_type type)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node *));
	if (!node)
		print_error_and_exit("calloc failure");
	node->type = type;
	node->args = NULL;
	node->redir = NULL;
	node->next = NULL;
}

t_redir	*make_redir(t_type)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir *));
	if (!redir)
		print_error_and_exit("calloc failure");
	redir->type = type;
	redir->next = NULL;
}

t_redir	*make_redir_struct(void)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir *));
	if (!redir)
		print_error_and_exit("calloc failure");
	redir->infile_fd = STDIN_FILENO;
	redir->outfile = STDOUT_FILENO;
	return (redir);
}

t_node	*redir_in_node(t_token *tok)
{
	t_node	*redir_in;

	redir_in = make_node(REDIR_IN);
	redir_in->redir = make_redir_struct();
	return (redir_in);
}

t_node	*redir_out_node(t_token *tok)
{
	t_node	*redir_out;

	redir_out = make_node(REDIR_OUT);
	redir_out->redir = make_redir_struct();
	return (redir_out);
}

t_node	*redir_append_node(t_token *tok)
{
	t_node	*redir_append;

	redir_append = make_node(REDIR_APPEND);
	redir_append->redir = make_redir_struct();
	return (redir_append);
}

t_node	*last_node(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	append_node(t_node *node, t_token *tok)
{
	t_node	*new_node;
	t_node	*last_node;

	last_node = node_last(*node);
	if (!ft_strcmp("<", tok->word))
		new_node = redir_in_node(tok);
	else if (!ft_strcmp(">", tok->word))
		new_node = redir_out_node(tok);
	else if (!ft_strcmp(">>", tok->word))
		new_node = redir_append_node(tok);
	// else if (!ft_strcmp("<<", tok->word))
	last_node->next = new_node;
}

//"<<", ">>", "<", ">", "|", 		"(", ")", "&&", "||"
t_node	*parser(t_token *tok)
{
	t_node	*new_node;

	new_node = make_node(SIMPLE_COMMAND);
	node_head = node;
	while (tok && tok->type != NIL)
	{
		if (tok->type == WORD)
			append_token(&node->args, tokdup(tok));
		else
		{
			append_node(node, tok);
			tok = tok->next;
		}
		// if (tok)
			tok = tok->next;
	}
	return ();
}
