/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:32:24 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/09 23:11:39 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"

char	*no_quote(char **no_quote_ptr)
{
	size_t		i;
	char		*unquoted;
	const char	*no_quote = *no_quote_ptr;

	i = 0;
	while (no_quote[i] && no_quote[i] != '\'' && no_quote[i] != '\"')
		i++;
	unquoted = ft_substr(no_quote, 0, i);
	if (!unquoted)
		print_error_and_exit("substr failure");
	*no_quote_ptr += i;
	return (unquoted);
}

char	*quote(char **quote_ptr)
{
	size_t		i;
	size_t		quoted_len;
	char		*quoted;
	const char	*quote = *quote_ptr;

	i = 1;
	quoted_len = 0;
	while (quote[i] && quote[i] != '\'')
	{
		quoted_len++;
		i++;
	}
	if (quote[i] == '\'')
		i++;
	quoted = ft_substr(quote + 1, 0, quoted_len);
	if (!quoted)
		print_error_and_exit("substr failure");
	*quote_ptr += i;
	return (quoted);
}

char	*dquote(char **dquote_ptr)
{
	size_t		i;
	size_t		dquoted_len;
	char		*dquoted;
	const char	*dquote = *dquote_ptr;

	i = 1;
	dquoted_len = 0;
	while (dquote[i] && dquote[i] != '\"')
	{
		dquoted_len++;
		i++;
	}
	if (dquote[i] == '\"')
		i++;
	dquoted = ft_substr(dquote + 1, 0, dquoted_len);
	if (!dquoted)
		print_error_and_exit("substr failure");
	*dquote_ptr += i;
	return (dquoted);
}

//A single quote may not occur between single quotes, even when preceded by a backslash?
void	quote_removal(t_token *tok)
{
	char	*word;
	char	*new_portion;
	char	*expanded;

	word = tok->word;
	expanded = ft_calloc(1, sizeof(char *));
	while (*word)
	{
		if (*word == '\'')
			new_portion = quote(&word);
		else if (*word == '\"')
			new_portion = dquote(&word);
		else
			new_portion = no_quote(&word);
		expanded = ft_strjoin_with_free(expanded, new_portion, FREE_BOTH);
	}
	free(tok->word);
	tok->word = expanded;
}

void	expand(t_token *tok)
{
	while (tok)
	{
		if (tok->type == WORD)
			quote_removal(tok);
		tok = tok->next;
	}
}
