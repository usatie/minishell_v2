/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/03/15 17:08:26 by myoshika         ###   ########.fr       */
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
	AND,
	OR,
	REDIR_APPEND,
	HEREDOC,
	REDIR_OUT,
	REDIR_IN,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	PIPE,
	NIL,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_type
{
	SIMPLE_COMMAND,
}	t_type;

// Redirecting output example
//command          : "echo hello; 1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

// typedef struct s_redir
// {
// 	int		infile;
// 	int		outfile;
// 	char	*filename;
// 	int		file_fd;
// 	int		stashed_fd;
// }	t_redir;

typedef struct s_ast_node
{
	t_type			type;
	t_token			*args;
	t_redir			*redir;
	struct ast_node	*parent;
	struct ast_node	*parent;
}	ast_node;

// typedef struct s_node
// {
// 	t_type			type;
// 	t_token			*args;
// 	t_redir			*redir;
// 	struct s_node	*next;
// }	t_node;

t_token	*make_token(char *word, t_token_type type);

void	print_error_and_exit(char *error_message);
void    print_syntax_error(char *unexpected_token);

bool	is_blank(char c);
bool	is_operator(char c);

t_token	*tokenize(char *line);
t_node	*parser(t_token *tok);
void	expand(t_node *node);
void	execute(t_node *node);

void	free_tokens(t_token *tok);
void	free_nodes(t_node *nodes);

#endif
