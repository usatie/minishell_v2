/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:54 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 09:21:59 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

/*
DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
	   word   A sequence of characters considered as a single unit by the
	          shell.  Also known as a token.
	   name   A word consisting only of alphanumeric characters and
			  underscores, and beginning with an alphabetic character or an
			  underscore.  Also referred to as an identifier.
       metacharacter
			  A character that, when unquoted, separates words.  One of the
              following:
              |  & ; ( ) < > space tab
       control operator
			  A token that performs a control function.  It is one of the
			  following symbols:
              || & && ; ;; ( ) | <newline>
*/

// Check longer operators first
t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {">>", "<<", "||", "&&", ";;", "<", ">",
		"&", ";", "(", ")", "|", "\n"};
	size_t				i;				
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}
