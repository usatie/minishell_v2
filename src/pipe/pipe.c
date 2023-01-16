/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:48 by susami            #+#    #+#             */
/*   Updated: 2023/01/08 22:00:04 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "xlib.h"
#include "minishell.h"

static void	cpy_pipe(int dst[2], int src[2]);

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	xpipe(node->outpipe);
	cpy_pipe(node->next->inpipe, node->outpipe);
}

void	prepare_pipe_child(t_node *node)
{
	xclose(node->outpipe[0]);
	xdup2(node->inpipe[0], STDIN_FILENO);
	if (node->inpipe[0] != STDIN_FILENO)
		xclose(node->inpipe[0]);
	xdup2(node->outpipe[1], STDOUT_FILENO);
	if (node->outpipe[1] != STDOUT_FILENO)
		xclose(node->outpipe[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->inpipe[0] != STDIN_FILENO)
		xclose(node->inpipe[0]);
	if (node->next)
		xclose(node->outpipe[1]);
}

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}
