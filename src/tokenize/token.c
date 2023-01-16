/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:55 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 01:35:57 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include "minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = xcalloc(1, sizeof(*tok));
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = xstrdup(tok->word);
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

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (ft_strcmp(tok->word, op) == 0);
}
