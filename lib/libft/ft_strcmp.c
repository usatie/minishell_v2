/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:17:06 by myoshika          #+#    #+#             */
/*   Updated: 2022/10/03 18:53:28 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*uc_s1 = (const unsigned char*)s1;
	const unsigned char	*uc_s2 = (const unsigned char*)s2;

	i = 0;
	while (*(uc_s1 + i) && *(uc_s2 + i))
	{
		if (*(uc_s1 + i) != *(uc_s2 + i))
			break ;
		i++;
	}
	return (*(uc_s1 + i) - *(uc_s2 + i));
}
