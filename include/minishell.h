#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

// error.c
void	todo(const char *msg) __attribute__((noreturn));
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));

// tokenize.c
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

t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *tok);

// expand.c
void	expand(t_token *tok);

// destructor.c
void	free_tok(t_token *tok);
void	free_argv(char **argv);
#endif
