/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 09:17:34 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 09:17:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdbool.h>
# include <signal.h>

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_OPEN_REDIR 1
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'

typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;
typedef enum e_node_kind	t_node_kind;
typedef struct s_node		t_node;
typedef struct s_map		t_map;
typedef struct s_item		t_item;

extern int						last_status;
extern bool						syntax_error;
extern bool						readline_interrupted;
extern volatile sig_atomic_t	sig;
extern t_map	*envmap;

// error.c
void	perror_prefix(void);
void	todo(const char *msg) __attribute__((noreturn));
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *tok);
void	xperror(const char *location);
void	builtin_error(const char *func, const char *name, const char *err);

typedef struct s_token		t_token;
enum e_token_kind {
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind	t_token_kind;

// `word` is zero terminated string.
struct s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

enum e_node_kind {
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};
typedef enum e_node_kind	t_node_kind;

typedef struct s_node	t_node;
struct s_node {
	t_node_kind	kind;
	t_node		*next;
	// CMD
	t_token		*args;
	t_node		*redirects;
	// REDIR
	int			targetfd;
	t_token		*filename;
	t_token		*delimiter;
	bool		is_delim_unquoted;
	int			filefd;
	int			stashed_targetfd;
	// PIPELINE
	int			inpipe[2];
	int			outpipe[2];
	t_node		*command;
};

// Redirecting output example
// command          : "echo hello 1 > out"
// targetfd         : 1
// filename         : "out"
// filefd           : open("out")
// stashed_targetfd : dup(targetfd)

#define ERROR_PARSE 258

# define ATTR_EXPORT 0x0000001
struct s_item {
	char	*name;
	char	*value;
	int		attributes;
	t_item	*next;
};

struct s_map {
	t_item	item_head;
};

// tokenize.c
t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *tok);
bool   	is_blank(char c);
bool   	consume_blank(char **rest, char *line);
bool   	startswith(const char *s, const char *keyword);
bool   	is_operator(const char *s);
bool   	is_metacharacter(char c);
bool   	is_word(const char *s);
t_token	*operator(char **rest, char *line);
t_token	*word(char **rest, char *line);
// tokenize/token.c
t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokdup(t_token *tok);
void	append_tok(t_token **tokens, t_token *tok);
bool	at_eof(t_token *tok);
bool	equal_op(t_token *tok, char *op);
// tokenize/name.c
bool	is_identifier(const char *s);
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);

// expand/expand.c
void	expand(t_node *node);
void	append_char(char **s, char c);
// expand/expand_quote_removal.c
void	expand_quote_removal(t_node *node);
// expand/expand_parameter.c
void	expand_variable(t_node *node);
// expand/variable.c
bool	is_variable(char *s);
void	expand_variable_str(char **dst, char **rest, char *p);
// expand/special_parameter.c
bool	is_special_parameter(char *s);
void	expand_special_parameter_str(char **dst, char **rest, char *p);
// expand/expand_heredoc.h
char	*expand_heredoc_line(char *line);

// destructor.c
void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

// parse.c
t_node	*parse(t_token *tok);
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
t_node	*new_node(t_node_kind kind);

t_node	*pipeline(t_token **rest, t_token *tok);
t_node	*simple_command(t_token **rest, t_token *tok);
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);


// redirect.c
void	do_redirect(t_node *redirects);
void	reset_redirect(t_node *redirects);

// redirect/stashfd.c
int	stashfd(int fd);
// redirect/open_redir_file.c
int		open_redir_file(t_node *node);
// redirect/heredoc.c
int	read_heredoc(const char *delimiter, bool is_delim_unquoted);

// pipe.c
void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

// exec/*.c
int		exec(t_node *node);
char	*search_path(const char *filename);

// signal/signal.c
void	setup_signal(void);
void	reset_signal(void);

// signal/signal_handle.c
void	reset_sig(int signum);
void	ignore_sig(int signum);
void	handle_sig(int signum);

// builtin.c
bool	is_builtin(t_node *node);
int		exec_builtin(t_node *node);

// builtin_exit.c
bool	is_numeric(char *s);
int		builtin_exit(char **argv);

// builtin_export.c
int		builtin_export(char **argv);

// builtin_unset.c
int		builtin_unset(char **argv);

// builtin_env.c
int		builtin_env(char **argv);

// builtin_cd.c
int		builtin_cd(char **argv);

// builtin_echo.c
int		builtin_echo(char **argv);

// builtin_pwd.c
int		builtin_pwd(char **argv);

// map.c
t_item	*item_new(char *name, char *value, int attr);
char	*item_get_string(t_item *item);
bool	item_exported(t_item *item);
t_map	*map_new(void);
t_item	*map_get(t_map *map, const char *name);
int		map_put(t_map *map, const char *string, bool allow_empty_value, int attr);
int		map_set(t_map *map, const char *name, const char *value);
int		map_set_attr(t_map *map, const char *name, const char *value, int attr);
int		map_unset(t_map *map, const char *name);
size_t	map_len(t_map *map, bool count_null_value);
void	map_printall(t_map *map);

// env.c
char	*xgetenv(const char *name);
void	initenv(void);
char	**get_environ(t_map *map);

#endif
