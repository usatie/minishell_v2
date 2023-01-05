/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:39 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 10:51:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
PARAMETERS
	   A parameter is an entity that stores values.  It can be a name, a
	   number, or one of the special characters listed below under Special
	   Parameters.  A variable is a parameter denoted by a name.  A variable
	   has a value and zero or more attributes.  Attributes are assigned using
	   the declare builtin command (see declare below in SHELL BUILTIN
	   COMMANDS).

	   A parameter is set if it has been assigned a value.  The null string is
	   a valid value.  Once a variable is set, it may be unset only by using
	   the unset builtin command (see SHELL BUILTIN COMMANDS below).

	   A variable may be assigned to by a statement of the form

              name=[value]

	   If value is not given, the variable is assigned the null string.  All
	   values undergo tilde expansion, parameter and variable expansion,
	   command substitution, arithmetic expansion, and quote removal (see
	   EXPANSION below).  If the variable has its integer attribute set, then
	   value is evaluated as an arithmetic expression even if the $((...))
	   expansion is not used (see Arithmetic Expansion below).  Word splitting
	   is not performed, with the exception of "$@" as explained below under
	   Special Parameters.  Pathname expansion is not performed.  Assignment
	   statements may also appear as arguments to the alias, declare, typeset,
	   export, readonly, and local builtin commands.

	   In the context where an assignment statement is assigning a value to a
	   shell variable or array index, the += operator can be used to append to
	   or add to the variable's previous value.  When += is applied to a
	   variable for which the integer attribute has been set, value is
	   evaluated as an arithmetic expression and added to the variable's
	   current value, which is also evaluated.  When += is applied to an array
	   variable using compound assignment (see Arrays below), the variable's
	   value is not unset (as it is when using =), and new values are appended
	   to the array beginning at one greater than the array's maximum index.
	   When applied to a string-valued variable, value is expanded and appended
	   to the variable's value.
*/
bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

void	expand_variable_str(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	if (*p != '$')
		assert_error("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		assert_error("Variable must starts with alphabets or underscore.");
	append_char(&name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++);
	value = xgetenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}
