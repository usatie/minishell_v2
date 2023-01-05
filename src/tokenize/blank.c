/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:52 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 09:22:59 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}
