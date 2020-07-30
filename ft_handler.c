/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:34:08 by qmarowak          #+#    #+#             */
/*   Updated: 2020/07/30 10:18:32 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

char	*handler_for_p(t_mod *inf_mod, char *str)
{
	if (inf_mod->sp == 'p' && inf_mod->f_f_ac == 1 && inf_mod->f_f_w == 1 &&
	ft_strlen(str))
		str = ft_strjoin(str, "x0", 1);
	if (inf_mod->sp == 'p' && inf_mod->f_f_w == 0 && inf_mod->f_f_ac == 1 &&
	(ft_strlen(str)))
	{
		inf_mod->sp = 'x';
		str = ft_strjoin(str, "x0", 1);
	}
	return (str);
}

char	*handler_for_i_d(t_mod *inf_mod, char *str, int *number)
{
	if (inf_mod->f_f_ac == 0 && (inf_mod->sp == 'd' || inf_mod->sp == 'i') &&
	inf_mod->ac > 0 && inf_mod->flag == '0'
	&& ft_strchr(str, '-') && ft_strlen(str) - 1)
		inf_mod->flag = '.';
	if (ft_strchr(str, '-') && ((inf_mod->f_f_ac == 0 && inf_mod->ac > 0 &&
	inf_mod->ac > ((int)ft_strlen(str) - 1)) || (inf_mod->flag == '0'
	&& inf_mod->f_f_w == 0)) && (inf_mod->sp == 'd' || inf_mod->sp == 'i'))
	{
		str = handler_for_i_d2(inf_mod, str, number);
	}
	return (str);
}

char	*pre_chek_w_a(t_mod *inf_mod, char *str)
{
	char	*dup_str;

	dup_str = ft_strdup(str);
	if (inf_mod->f_f_w == 0)
	{
		if (inf_mod->w < 0)
			inf_mod->flag = '-';
		if (inf_mod->sp == 'p' && inf_mod->f_f_ac == 1)
		{
			inf_mod->w -= 2;
			str = ft_width(inf_mod->flag, inf_mod->w, str);
			str = (inf_mod->sp == 'p') ? ft_strjoin(str, "x0", 1) : str;
		}
		else
		{
			str = ft_width(inf_mod->flag, inf_mod->w, str);
		}
	}
	if (inf_mod->f_f_ac != 1 && inf_mod->sp != 'c')
		str = ft_accuracy(*inf_mod, str, dup_str, &inf_mod->minus);
	else
		free(dup_str);
	return (str);
}

char	*pre_chek(char *str, t_mod inf_mod, int number)
{
	char	*tmp;

	if (inf_mod.sp == 'p')
		str = handler_for_p(&inf_mod, str);
	if (inf_mod.sp == 'c' && inf_mod.f_f_w == 0 && !(ft_strlen(str))
	&& inf_mod.w != 0)
		inf_mod.w = (inf_mod.w < 0) ? inf_mod.w + 1 : inf_mod.w - 1;
	if (inf_mod.sp == 'i' || inf_mod.sp == 'd')
		str = handler_for_i_d(&inf_mod, str, &number);
	if (inf_mod.f_f_ac != 1 && inf_mod.ac == 0 &&
	ft_strlen(str) == 1 && *str == '0')
	{
		tmp = str;
		str = ft_strdup("");
		free(tmp);
	}
	if (inf_mod.f_f_w == 0 || inf_mod.f_f_ac != 1)
		str = pre_chek_w_a(&inf_mod, str);
	if (inf_mod.minus == ' ')
		str = (number == '-') ? ft_strjoin(str, "-", 1) : str;
	str = perevorot(str);
	return (str);
}

int		ft_handler(t_mod inf_mod, va_list argptr)
{
	char	*str;
	int		number;
	int		flag;
	int		f;

	number = 1;
	flag = 100;
	f = 0;
	if (inf_mod.sp != 's')
		str = pre_chek(new_str(inf_mod, argptr, &flag), inf_mod, number);
	else
	{
		str = va_arg(argptr, char*);
		str = ft_obrabotchik_for_s(inf_mod, str, 0);
	}
	if (inf_mod.flag != '-' && (f = 1))
		ft_putstr_fd(str, 1);
	number = ft_strlen(str);
	if ((flag < 32 || flag > 127) && (number += 1))
		ft_putchar_fd(flag, 1);
	if (!f)
		ft_putstr_fd(str, 1);
	free(str);
	return (number);
}
