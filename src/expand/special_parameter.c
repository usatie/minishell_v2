/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_parameter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:38 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 11:11:56 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Special Parameters
	   The shell treats several parameters specially.  These parameters may
	   only be referenced; assignment to them is not allowed.
	   *      Expands to the positional parameters, starting from one.  When
			  the expansion occurs within double quotes, it expands to a single
			  word with the value of each parameter separated by the first
			  character of the IFS special variable.  That is, "$*" is
			  equivalent to "$1c$2c...", where c is the first character of the
			  value of the IFS variable.  If IFS is unset, the parameters are
			  separated by spaces.  If IFS is null, the parameters are joined
			  without intervening separators.
	   @      Expands to the positional parameters, starting from one.  When
			  the expansion occurs within double quotes, each parameter expands
			  to a separate word.  That is, "$@" is equivalent to "$1" "$2" ...
			  If the double-quoted expansion occurs within a word, the
			  expansion of the first parameter is joined with the beginning
			  part of the original word, and the expansion of the last
			  parameter is joined with the last part of the original word.
			  When there are no positional parameters, "$@" and $@ expand to
			  nothing (i.e., they are removed).
       #      Expands to the number of positional parameters in decimal.
	   ?      Expands to the status of the most recently executed foreground
	          pipeline.
	   -      Expands to the current option flags as specified upon invocation,
			  by the set builtin command, or those set by the shell itself
			  (such as the -i option).
	   $      Expands to the process ID of the shell.  In a () subshell, it
			  expands to the process ID of the current shell, not the subshell.
	   !      Expands to the process ID of the most recently executed
	          background (asynchronous) command.
	   0      Expands to the name of the shell or shell script.  This is set at
			  shell initialization.  If bash is invoked with a file of
			  commands, $0 is set to the name of that file.  If bash is started
			  with the -c option, then $0 is set to the first argument after
			  the string to be executed, if one is present.  Otherwise, it is
			  set to the file name used to invoke bash, as given by argument
			  zero.
	   _      At shell startup, set to the absolute pathname used to invoke the
			  shell or shell script being executed as passed in the environment
			  or argument list.  Subsequently, expands to the last argument to
			  the previous command, after expansion.  Also set to the full
			  pathname used to invoke each command executed and placed in the
			  environment exported to that command.  When checking mail, this
			  parameter holds the name of the mail file currently being
			  checked.
*/

bool	is_special_parameter(char *s)
{
	return (s[0] == '$' && s[1] == '?');
}

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

void	expand_special_parameter_str(char **dst, char **rest, char *p)
{
	if (!is_special_parameter(p))
		assert_error("Expected special parameter");
	p += 2;
	append_num(dst, g_ctx.last_status);
	*rest = p;
}
