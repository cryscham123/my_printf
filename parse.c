/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunghki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:30:02 by hyunghki          #+#    #+#             */
/*   Updated: 2023/04/26 16:30:07 by hyunghki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchr(char c, t_info *i)
{
	if (c == '!' && i->cmd != 'c' && i->cmd != 's')
		return (0);
	if ((i->cmd == 'c' || i->cmd == '%') && !(i->flag & F_LEFT))
		if (ft_padding(i, 1) < 0)
			return (-1);
	i->cnt++;
	return (write(1, &c, 1));
}

int	ft_printstr(char *s, t_info *i)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (ft_printstr("(null)", i));
	while (s[len] && !((i->flag & F_PREC) && len >= i->field[1]))
		len++;
	if (!(i->flag & F_LEFT))
		if (ft_padding(i, len) < 0)
			return (-1);
	len = 0;
	while (s[len] && !((i->flag & F_PREC) && len >= i->field[1]))
	{
		if (ft_putchr(s[len], i) < 0)
			return (-1);
		len++;
	}
	return (0);
}

int	ft_putnum(long long num, t_info *i, int cur)
{
	int	is_sign;
	int	is_put;

	if (num < 0)
		i->flag |= (F_PLUS + F_SPACE);
	num *= 1 * (num >= 0) + -1 * (num < 0);
	is_sign = (i->flag & (F_PLUS + F_SPACE)) != 0;
	is_put = !(num == 0 && cur == 0 && i->field[1] == 0 && (i->flag & F_PREC));
	if (num < 10)
	{
		if ((i->flag & F_ZERO) && ft_putchr("! !!+-"[i->flag & 5], i) < 0)
			return (-1);
		if (!(i->flag & F_LEFT))
			if (ft_padding(i, ft_max(cur + is_put, i->field[1]) + is_sign) < 0)
				return (-1);
		if (!(i->flag & F_ZERO) && ft_putchr("! !!+-"[i->flag & 5], i) < 0)
			return (-1);
		if ((i->flag & F_PREC))
			return (ft_precision(i, num, cur, num % 10 + '0'));
		return (ft_putchr(num % 10 + '0', i));
	}
	if (ft_putnum(num / 10, i, cur + 1) < 0 || ft_putchr(num % 10 + '0', i) < 0)
		return (-1);
	return (0);
}

int	ft_puthex(unsigned long long num, t_info *i, int cur)
{
	char	s;
	int		is_sign;

	s = "0123456789ABCDEF"[num % 16] | 32 * (i->cmd == 'x' || i->cmd == 'p');
	is_sign = (i->cmd == 'p' || (!(cur == 0 && num == 0) && (i->flag & 2))) * 2;
	if (num < 16)
	{
		if ((i->flag & F_ZERO) && is_sign != 0)
			if (ft_putchr('0', i) < 0 || ft_putchr("xX"[i->cmd == 'X'], i) < 0)
				return (-1);
		if (!(i->flag & F_LEFT))
			if (ft_padding(i, ft_max(cur + 1, i->field[1]) + is_sign) < 0)
				return (-1);
		if (!(i->flag & F_ZERO) && is_sign != 0)
			if (ft_putchr('0', i) < 0 || ft_putchr("xX"[i->cmd == 'X'], i) < 0)
				return (-1);
		if ((i->flag & F_PREC))
			return (ft_precision(i, num, cur, s));
		return (ft_putchr(s, i));
	}
	if (ft_puthex(num / 16, i, cur + 1) < 0 || ft_putchr(s, i) < 0)
		return (-1);
	return (0);
}
