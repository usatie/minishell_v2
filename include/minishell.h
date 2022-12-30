#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
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


// token.c
# define SINGLE_QUOTE_CHAR '\''

t_token	*tokenize(char *line);
char	**token_list_to_argv(t_token *tok);
t_token	*new_token(char *word, t_token_kind kind);
bool   	is_blank(char c);
bool   	consume_blank(char **rest, char *line);
bool   	startswith(const char *s, const char *keyword);
bool   	is_operator(const char *s);
bool   	is_metacharacter(char c);
bool   	is_word(const char *s);
t_token	*operator(char **rest, char *line);
t_token	*word(char **rest, char *line);

// expand.c
void	expand(t_token *tok);

// destructor.c
void	free_tok(t_token *tok);
void	free_argv(char **argv);
#endif
