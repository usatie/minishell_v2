/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:28:23 by myoshika          #+#    #+#             */
/*   Updated: 2022/10/22 22:10:06 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	digit_count(int n)
{
	int	digits;

	digits = 0;
	if (n < 0 || n == 0)
		digits++;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static void	put_in_digits(char *arr, long buf)
{
	int	div;

	div = 1;
	if (buf < 0)
	{
		*arr = '-';
		buf *= -1;
		arr++;
	}
	while (buf / 10 >= div)
		div *= 10;
	while (div != 0)
	{
		*arr = (buf / div) + '0';
		buf %= div;
		div /= 10;
		arr++;
	}
	*(arr) = '\0';
}

char	*ft_itoa(int n)
{
	char	*arr;
	long	buf;
	int		digits;	

	digits = digit_count(n);
	arr = (char *)malloc(digits + 1);
	buf = (long)n;
	if (arr != NULL)
		put_in_digits(arr, buf);
	return (arr);
}
