#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

volatile sig_atomic_t	sig = 0;

static int	check_state(void);

void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	handle_sig(SIGINT);
}

void	reset_signal(void)
{
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
}

static int	check_state(void)
{
	if (sig == 0)
		return (0);
	else if (sig == SIGINT)
	{
		sig = 0;
		readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
		return (0);
	}
	return (0);
}
