/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:49:13 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/10 20:56:29 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static void	ft_strlcpy_no_ret(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && *(src + i))
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize != 0)
		*(dst + i) = '\0';
}

char	*ft_strjoin_with_free(char *s1, char *s2, int to_free)
{
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = (char *)malloc(s1_len + s2_len + 1);
	if (joined != NULL)
	{
		ft_strlcpy_no_ret(joined, s1, s1_len + 1);
		ft_strlcpy_no_ret(joined + s1_len, s2, s2_len + 1);
	}
	if (to_free == 1)
		ft_safe_free(&s1);
	if (to_free == 2)
		ft_safe_free(&s2);
	return (joined);
}
