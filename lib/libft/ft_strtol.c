/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:55:16 by myoshika          #+#    #+#             */
/*   Updated: 2022/12/26 18:14:31 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdbool.h>

typedef struct s_strtol
{
	int				sign;
	bool			found_num;
	bool			found_num_ii;
	long			num;
}	t_strtol;

static int	char_to_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

static void	make_num(const char **nptr, int base, t_strtol *s)
{
	int	c;

	while (**nptr)
	{
		c = char_to_numeric(**nptr);
		if (c == -1 || c >= base)
			break ;
		s->found_num_ii = true;
		if (s->sign == 1 && ((s->num > LONG_MAX / base)
				|| (s->num == LONG_MAX / base && c > LONG_MAX % base)))
		{
			errno = ERANGE;
			s->num = LONG_MAX;
		}
		else if (s->sign == -1 && ((s->num < LONG_MIN / base)
				|| (s->num == LONG_MIN / base && c > LONG_MIN % base * -1)))
		{
			errno = ERANGE;
			s->num = LONG_MIN;
		}
		if (s->num != LONG_MAX && s->num != LONG_MIN)
			s->num = (s->num * base) + (s->sign * c);
		(*nptr)++;
	}
}

static int	change_base(const char *nptr, char **endptr, int *base, t_strtol *s)
{
	if (nptr[0] == '0')
	{
		s->found_num = true;
		if (endptr)
			*endptr = (char *)&nptr[1];
	}
	if ((*base == 16 || *base == 0) && nptr[0] == '0')
	{
		*base = 16;
		if (nptr[1] == 'x' || nptr[1] == 'X')
			return (2);
	}
	if (*base == 0)
	{
		*base = 10;
		if (nptr[0] == '0')
			*base = 8;
	}
	return (0);
}

static size_t	skip_space_and_sign(const char *nptr, t_strtol *s)
{
	size_t	i;

	i = 0;
	while (nptr[i] == 32 || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s->sign = -1;
		i++;
	}
	return (i);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	t_strtol		s;
	const char		*original_nptr = nptr;

	if (base < 0 || base > 36 || base == 1)
	{
		errno = EINVAL;
		return (0);
	}
	ft_bzero(&s, sizeof(t_strtol));
	s.sign = 1;
	nptr += skip_space_and_sign(nptr, &s);
	nptr += change_base(nptr, endptr, &base, &s);
	make_num(&nptr, base, &s);
	if (endptr && s.found_num_ii)
		*endptr = (char *)nptr;
	if (endptr && !s.found_num && !s.found_num_ii)
		*endptr = (char *)original_nptr;
	return (s.num);
}
