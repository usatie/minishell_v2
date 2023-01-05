/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:45 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 08:56:45 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

// <pipeline> = <simple_command> ('|' <pipeline>)
// <simple_command> = <command_element>+
// <command_element> = <word> | <redirection>
// <redirection> = '>' <word>
//               | '<' <word>
//               | '>>' <word>
//               | '<<' <word>
t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}
