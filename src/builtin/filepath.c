/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:11:53 by susami            #+#    #+#             */
/*   Updated: 2023/01/06 09:51:42 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"

bool	consume_path(char **rest, char *path, char *elm)
{
	size_t	elm_len;

	elm_len = ft_strlen(elm);
	if (ft_strncmp(path, elm, elm_len) == 0)
	{
		if (path[elm_len] == '\0' || path[elm_len] == '/')
		{
			*rest = path + elm_len;
			return (true);
		}
	}
	return (false);
}

void	delete_last_path_elm(char *path)
{
	char	*start;
	char	*last_slash_ptr;

	start = path;
	last_slash_ptr = NULL;
	while (*path)
	{
		if (*path == '/')
			last_slash_ptr = path;
		path++;
	}
	if (last_slash_ptr != start)
		*last_slash_ptr = '\0';
}

size_t	strlncpy(char *dst, char *src, size_t n, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && n > 0 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
		n--;
	}
	dst[i] = '\0';
	while (n > 0 && *src)
	{
		i++;
		n--;
		src++;
	}
	return (i);
}

// dst: "/Users/shunusami" src:"Desktop/workspace/minishell")
// ->
// dst : "/Users/shunusami/Desktop", rest: "/workspace/minishell"
//
// using strlcpy like strncpy
void	append_path_elm(char *dst, size_t dstsize, char **rest, char *src)
{
	char	buf[PATH_MAX];
	size_t	elm_len;

	elm_len = 0;
	while (src[elm_len] && src[elm_len] != '/')
		elm_len++;
	if (strlncpy(buf, src, elm_len, PATH_MAX) >= PATH_MAX)
		assert_error("This will not happen");
	if (dst[ft_strlen(dst) - 1] != '/')
		if (ft_strlcat(dst, "/", dstsize) >= dstsize)
			assert_error("This will not happen");
	if (ft_strlcat(dst, buf, dstsize) >= dstsize)
		assert_error("This will not happen");
	*rest = src + elm_len;
}
