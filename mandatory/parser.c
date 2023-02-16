/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/16 21:49:26 by myoshika         ###   ########.fr       */
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

void	append_token_to_args(t_token **args, t_token *tok_to_add)
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

t_node	*parser(t_token *tok)
{
	t_node	*node;

	node = ft_calloc(2, sizeof(t_node *));
	if (!node)
		print_error_and_exit("calloc failure");
	while (tok && tok->type != NIL)
	{
		if (tok->type == WORD)
		{
			append_token_to_args(&node->args, tokdup(tok));
			tok = tok->next;
		}
		else
		{
			printf("tok->type:%d\n", tok->type);
			print_parser_error(tok->word);
		}
	}
	node->next = NULL;
	return (node);
}
