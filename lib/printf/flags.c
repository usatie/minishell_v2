/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 07:01:55 by myoshika          #+#    #+#             */
/*   Updated: 2022/11/25 10:44:12 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	basic_atoi(const char *str, size_t *i, int num)
{
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
	{
		if ((num > INT_MAX / 10)
			|| (num == INT_MAX / 10 && str[*i] - '0' > INT_MAX % 10))
			num = INT_MAX;
		else
			num = (num * 10) + (str[*i] - '0');
		(*i)++;
	}
	return (num);
}

static int	get_width_precision(const char *str, size_t i, t_printf *info)
{
	if (ft_isdigit(str[i]))
		info->width = basic_atoi(str + i, &i, 0);
	if (str[i] == '.')
	{
		i++;
		info->precision = basic_atoi(str, &i, 0);
	}
	return (i);
}

static size_t	get_flags(const char *after_pct, size_t i, t_printf *info)
{
	while (after_pct[i] && ft_strchr("- +#0", after_pct[i]))
	{
		if (after_pct[i] == '-')
			info->dash = true;
		else if (after_pct[i] == ' ' && info->sign != '+')
			info->sign = ' ';
		else if (after_pct[i] == '+')
			info->sign = '+';
		else if (after_pct[i] == '#')
			info->sharp = true;
		else if (after_pct[i] == '0')
			info->padding = '0';
		i++;
	}
	return (i);
}

size_t	get_info(const char *after_pct, t_printf *info)
{
	size_t	i;

	i = 0;
	i += get_flags(after_pct, i, info);
	i += get_width_precision(after_pct + i, 0, info);
	info->fmt = after_pct[i++];
	if (info->dash)
		info->padding = ' ';
	return (i);
}
