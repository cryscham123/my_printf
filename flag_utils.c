/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunghki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:30:14 by hyunghki          #+#    #+#             */
/*   Updated: 2023/04/26 16:30:18 by hyunghki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_padding(t_info *i, int n)
{
	char	padding;

	padding = ' ';
	if (i->flag & F_ZERO)
		padding = '0';
	while ((i->flag & F_WDTH) && n < i->field[0])
	{
		if (write(1, &padding, 1) < 0)
			return (-1);
		i->cnt++;
		n++;
	}
	return (0);
}

int	ft_precision(t_info *i, int num, int n, int target)
{
	if (num == 0 && n == 0 && i->field[1] == 0)
		return (0);
	while ((i->flag & F_PREC) && n < i->field[1] - 1)
	{
		if (ft_putchr('0', i) < 0)
			return (-1);
		n++;
	}
	return (ft_putchr(target, i));
}
