/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:28:23 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/16 20:24:54 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	digit_count(long n)
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

static void	put_in_digits(char *arr, long n)
{
	int	div;

	div = 1;
	if (n < 0)
	{
		*arr = '-';
		n *= -1;
		arr++;
	}
	while (n / 10 >= div)
		div *= 10;
	while (div != 0)
	{
		*arr = (n / div) + '0';
		n %= div;
		div /= 10;
		arr++;
	}
	*(arr) = '\0';
}

char	*ft_ltoa(long n)
{
	char	*arr;
	int		digits;	

	digits = digit_count(n);
	arr = (char *)malloc(digits + 1);
	if (arr != NULL)
		put_in_digits(arr, n);
	return (arr);
}
