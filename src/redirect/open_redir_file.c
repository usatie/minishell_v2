/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 08:56:49 by susami            #+#    #+#             */
/*   Updated: 2023/01/05 17:59:36 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

static int	openfd(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (node->kind == ND_REDIR_IN)
		return (open(node->filename->word, O_RDONLY));
	else if (node->kind == ND_REDIR_APPEND)
		return (open(node->filename->word,
				O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (node->kind == ND_REDIR_HEREDOC)
		return (read_heredoc(node->delimiter->word, node->is_delim_unquoted));
	else
		assert_error("open_redir_file");
}

int	open_redir_file(t_node *node)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPELINE)
	{
		if (open_redir_file(node->command) < 0)
			return (-1);
		if (open_redir_file(node->next) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects));
	node->filefd = openfd(node);
	if (node->filefd < 0)
	{
		if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND
			|| node->kind == ND_REDIR_IN)
			xperror2(node->filename->word, NULL);
		return (-1);
	}
	node->filefd = stashfd(node->filefd);
	return (open_redir_file(node->next));
}
