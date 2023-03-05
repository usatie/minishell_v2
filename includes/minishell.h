/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/03/06 03:04:19 by myoshika         ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
}	t_node_type;

// Redirecting output example
command          : "echo hello; 1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

typedef struct s_redir
{
	int	infile;
	int	outfile;
}	t_redir;
typedef struct s_node
{
	t_node_type		type;
	t_token			*args;
	t_redir			*redir;
	struct s_node	*next;
}	t_node;

t_token	*make_token(char *word, t_token_type type);
void	print_error_and_exit(char *error_message);

bool	is_blank(char c);
bool	is_operator(char c);

t_token	*tokenize(char *line);
t_node	*parser(t_token *tok);
void	expand(t_node *node);
void	execute(t_node *node);

#endif
