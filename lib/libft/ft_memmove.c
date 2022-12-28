/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:20:28 by myoshika          #+#    #+#             */
/*   Updated: 2022/09/22 22:39:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*uc_dst;
	const unsigned char	*uc_src = src;
	int					i;

	if (dst == src || len == 0)
		return (dst);
	uc_dst = dst;
	i = 1;
	if (dst > src)
	{
		uc_dst += len - 1;
		uc_src += len - 1;
		i = -1;
	}
	while (len--)
	{
		*uc_dst = *uc_src;
		uc_dst += i;
		uc_src += i;
	}
	return (dst);
}
