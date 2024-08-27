/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunghki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:29:39 by hyunghki          #+#    #+#             */
/*   Updated: 2023/05/17 14:43:50 by hyunghki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_flag_validate(t_info *i)
{
	if ((i->flag & F_ZERO) && (i->flag & F_LEFT))
		i->flag &= ~F_ZERO;
	if ((i->flag & F_ZERO) && (i->flag & F_PREC))
		i->flag &= ~F_ZERO;
	if ((i->flag & F_SPACE) && (i->flag & F_PLUS))
		i->flag &= ~F_SPACE;
}

static int	ft_parse(va_list *ap, char c, t_info i)
{
	int	status;

	i.cmd = c;
	ft_flag_validate(&i);
	if (c == 'c')
		status = ft_putchr((char)(va_arg(*ap, size_t)), &i);
	else if (c == '%')
		status = ft_putchr('%', &i);
	else if (c == 's')
		status = ft_printstr(va_arg(*ap, char *), &i);
	else if (c == 'd' || c == 'i')
		status = ft_putnum(va_arg(*ap, int), &i, 0);
	else if (c == 'u')
		status = ft_putnum(va_arg(*ap, unsigned int), &i, 0);
	else if (c == 'p')
		status = ft_puthex((unsigned long long)va_arg(*ap, void *), &i, 0);
	else
		status = ft_puthex(va_arg(*ap, unsigned int), &i, 0);
	if (status < 0 || ft_padding(&i, i.cnt) < 0)
		return (-1);
	return (i.cnt);
}

static int	ft_convert(va_list *ap, const char **s)
{
	t_info	i;
	int		tmp;

	i.flag = 0;
	i.cnt = 0;
	i.field[0] = 0;
	i.field[1] = 0;
	while (**s == '#' || **s == ' ' || **s == '0' || **s == '-' || **s == '+')
	{
		tmp = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0!!1!!!!!!!2!3!!4"[(int)**s];
		i.flag |= (1 << (tmp - '0'));
		(*s)++;
	}
	while (**s == '.' || (**s >= '1' && **s <= '9'))
	{
		tmp = (**s == '.');
		(*s) += tmp;
		i.flag |= (F_WDTH >> tmp);
		while (**s >= '0' && **s <= '9')
		{
			i.field[tmp] = i.field[tmp] * 10 + (**s - '0');
			(*s)++;
		}
	}
	return (ft_parse(ap, **s, i));
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		cnt;
	int		tmp;

	va_start(ap, s);
	cnt = 0;
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			tmp = ft_convert(&ap, &s);
		}
		else
			tmp = write(1, s, 1);
		if (tmp < 0)
			return (-1);
		cnt += tmp;
		s++;
	}
	va_end(ap);
	return (cnt);
}
