/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:35 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 08:56:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char	*expand_heredoc_line(char *line)
{
	char	*new_word;
	char	*p;

	p = line;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p);
		else
			append_char(&new_word, *p++);
	}
	free(line);
	return (new_word);
}
