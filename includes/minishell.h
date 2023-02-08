/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:23:03 by myoshika          #+#    #+#             */
/*   Updated: 2023/02/08 23:11:43 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

typedef enum e_type
{
	WORD,
	BLANK,
	RESERVED,
	OPERATOR,
	EOF,
}	t_type;

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*next;
}	t_token;

void	print_error_and_exit(char *error_message);
t_token	*tokenize(char *line);

#endif
