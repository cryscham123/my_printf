/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunghki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:29:53 by hyunghki          #+#    #+#             */
/*   Updated: 2023/04/26 16:29:56 by hyunghki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define F_WDTH 64
# define F_PREC 32
# define F_ZERO 16
# define F_LEFT 8
# define F_PLUS 4
# define F_SHAP 2
# define F_SPACE 1

# include <stdarg.h>
# include <unistd.h>

typedef struct s_info
{
	unsigned int	flag;
	int				field[2];
	int				cnt;
	char			cmd;
}	t_info;

int	ft_printf(const char *s, ...);
int	ft_putchr(char c, t_info *i);
int	ft_printstr(char *s, t_info *i);
int	ft_putnum(long long num, t_info *i, int cur);
int	ft_puthex(unsigned long long n, t_info *i, int cur);
int	ft_max(int a, int b);
int	ft_padding(t_info *i, int n);
int	ft_precision(t_info *i, int num, int n, int target);

#endif
