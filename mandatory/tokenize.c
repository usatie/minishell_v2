/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:11:38 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/10 05:00:26 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include <stdio.h>

t_token	*make_token(char *word, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token *));
	if (!new)
		print_error_and_exit("malloc failure");
	new->word = word;
	new->type = type;
	new->next = NULL;
	return (new);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_operator(char c)
{
	return (c && ft_strchr("|&()<>", c));
}

t_token	*blank(char *line)
{
	char	*blank;
	size_t	blank_len;

	blank_len = 0;
	while (is_blank(line[blank_len]))
		blank_len++;
	blank = ft_substr(line, 0, blank_len);
	if (!blank)
		print_error_and_exit("substr failure");
	return (make_token(blank, BLANK));
}

t_token	*operator(char *line)
{
	int			i;
	char		*operator;
	const char	*operators[] = \
	{"&&", "<<", ">>", "||", "&", "<", ">", "|", "(", ")", NULL};

	i = 0;
	while (ft_strncmp(operators[i], line, ft_strlen(operators[i])))
		i++;
	operator = ft_strdup(operators[i]);
	if (!operator)
		print_error_and_exit("strdup failure");
	return (make_token(operator, OPERATOR));
}

size_t	count_till_closing_quote(char *start_of_quote)
{
	size_t	len;

	len = 1;
	while (start_of_quote[len] && start_of_quote[0] != start_of_quote[len])
		len++;
	if (*(start_of_quote + len) == *start_of_quote)
		len++;
	return (len);
}

t_token	*word(char *line)
{
	char	*word;
	size_t	word_len;

	word_len = 0;
	while (line[word_len] && \
		!is_blank(line[word_len]) && !is_operator(line[word_len]))
	{
		if (line[word_len] == '\'' || line[word_len] == '\"')
			word_len += count_till_closing_quote(&line[word_len]);
		else
			word_len++;
	}
	word = ft_substr(line, 0, word_len);
	if (!word)
		print_error_and_exit("substr failure");
	return (make_token(word, WORD));
}

// void	print_tokens(t_token *tok)
// {
// 	while (tok)
// 	{
// 		printf("[%s]\n", tok->word);
// 		fflush(stdout);
// 		tok = tok->next;
// 	}
// }

t_token	*tokenize(char *line)
{
	t_token	*tok;
	t_token	head;

	tok = &head;
	while (*line)
	{
		if (is_blank(*line))
			tok->next = blank(line);
		else if (is_operator(*line))
			tok->next = operator(line);
		else
			tok->next = word(line);
		tok = tok->next;
		line += ft_strlen(tok->word);
	}
	tok->next = make_token(NULL, EOF);
	//print_tokens(head.next);
	return (head.next);
}

