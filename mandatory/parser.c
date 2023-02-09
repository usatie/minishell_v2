/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:49:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/10 07:22:31 by myoshika         ###   ########.fr       */
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

//recursively move to the end of args list and append
void	append_token_to_args(t_token **args, t_token *tok_to_add)
{
	if (!*args)
	{
		*args = tok_to_add;
		return ;
	}
	append_token_to_args(&(*args)->next, tok_to_add);
}

t_node	*parser(t_token *tok)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node *));
	if (!node)
		print_error_and_exit("calloc failure");
	while (tok && tok->type != EOF)
	{
		if (tok->type == WORD)
			append_token_to_args(&node->args, tokdup(tok));
		//else
			//implement parser
		tok = tok->next;
	}
	return (node);
}
