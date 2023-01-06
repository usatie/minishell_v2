/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:57:48 by susami            #+#    #+#             */
/*   Updated: 2023/01/06 22:03:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
   Word Splitting
	   The shell scans the results of parameter expansion, command
	   substitution, and arithmetic expansion that did not occur within double
	   quotes for word splitting.

	   The shell treats each character of IFS as a delimiter, and splits the
	   results of the other expansions into words on these characters.  If IFS
	   is unset, or its value is exactly <space><tab><newline>, the default,
	   then any sequence of IFS characters serves to delimit words.  If IFS has
	   a value other than the default, then sequences of the whitespace
	   characters space and tab are ignored at the beginning and end of the
	   word, as long as the whitespace character is in the value of IFS (an IFS
	   whitespace character).  Any character in IFS that is not IFS whitespace,
	   along with any adjacent IFS whitespace characters, delimits a field.  A
	   sequence of IFS whitespace characters is also treated as a delimiter.
	   If the value of IFS is null, no word splitting occurs.

	   Explicit null arguments ("" or '') are retained.  Unquoted implicit null
	   arguments, resulting from the expansion of parameters that have no
	   values, are removed.  If a parameter with no value is expanded within
	   double quotes, a null argument results and is retained.

	   Note that if no expansion occurs, no splitting is performed.
*/
static void	expand_word_splitting_tok(t_token *tok);

static void	insert_new_tok(char **new_word, t_token **rest, t_token *tok)
{
	t_token	*new_tok;

	tok->word = *new_word;
	*new_word = ft_calloc(1, sizeof(char));
	if (*new_word == NULL)
		fatal_error("ft_calloc");
	new_tok = new_token(NULL, TK_WORD);
	new_tok->next = tok->next;
	tok->next = new_tok;
	*rest = tok->next;
}

bool	is_default_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_ifs(char c)
{
	char	*ifs;

	ifs = xgetenv("IFS");
	if (ifs == NULL)
		return (is_default_ifs(c));
	if (c == '\0')
		return (false);
	return (ft_strchr(ifs, c) != NULL);
}

bool	consume_ifs(char **rest, char *line)
{
	if (is_ifs(*line))
	{
		line++;
		while (*line && is_ifs(*line) && is_default_ifs(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

static void	expand_word_splitting_tok(t_token *tok)
{
	char	*new_word;
	char	*to_free;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	if (!tok->is_expanded)
		return (expand_word_splitting_tok(tok->next));
	to_free = tok->word;
	p = tok->word;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("ft_calloc");
	while (*p)
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p);
		else if (consume_ifs(&p, p))
			insert_new_tok(&new_word, &tok, tok);
		else
			append_char(&new_word, *p++);
	}
	tok->word = new_word;
	free(to_free);
	expand_word_splitting_tok(tok->next);
}

void	expand_word_splitting(t_node *node)
{
	if (node == NULL)
		return ;
	expand_word_splitting_tok(node->args);
	expand_word_splitting_tok(node->filename);
	expand_word_splitting(node->redirects);
	expand_word_splitting(node->command);
	expand_word_splitting(node->next);
}
