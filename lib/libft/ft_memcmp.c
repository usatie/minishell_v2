/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:20:23 by myoshika          #+#    #+#             */
/*   Updated: 2022/09/22 22:40:02 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*uc_s1 = (const unsigned char*)s1;
	const unsigned char	*uc_s2 = (const unsigned char*)s2;

	i = 0;
	while (i < n)
	{
		if (*(uc_s1 + i) != *(uc_s2 + i))
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return (*(uc_s1 + i) - *(uc_s2 + i));
}
