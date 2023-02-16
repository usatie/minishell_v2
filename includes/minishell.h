/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/16 21:49:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>

// extern bool	g_syntax_error;

typedef enum e_token_type
{
	WORD,
	RESERVED,
	OPERATOR,
	NIL,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	SIMPLE_COMMAND,
}	t_node_type;

typedef struct s_node
{
	t_token			*args;
	t_node_type		type;
	struct s_node	*next;
}	t_node;

t_token	*make_token(char *word, t_token_type type);
void	print_error_and_exit(char *error_message);

bool	is_blank(char c);
bool	is_operator(char c);

t_token	*tokenize(char *line);
void	expand(t_node *node);
t_node	*parser(t_token *tok);

#endif
