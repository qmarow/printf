/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:36:27 by qmarowak          #+#    #+#             */
/*   Updated: 2020/07/30 10:18:53 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

char	*new_str(t_mod inf_mod, va_list argptr, int *flag)
{
	char	*str;

	if (inf_mod.sp == 'd' || inf_mod.sp == 'i' || inf_mod.sp == 'u')
	{
		return (int_diu(argptr, inf_mod.sp));
	}
	if (inf_mod.sp == 'x' || inf_mod.sp == 'X' || inf_mod.sp == 'p')
	{
		return (ft_perevod(argptr, inf_mod, 16));
	}
	*flag = va_arg(argptr, int);
	str = (*flag < 32 || *flag > 127) ? ft_strdup("")
	: ft_memset(ft_strdup(" "), *flag, 1);
	return (str);
}

char	*ft_accu_for_s(t_mod inf_mod, char *str)
{
	char	*str_str;
	char	*tmp;
	int		accuracy;

	accuracy = inf_mod.ac;
	tmp = perevorot(str);
	if (inf_mod.f_f_ac != 1)
		str_str = ft_substr(tmp, 0, accuracy);
	else
		str_str = ft_strdup(tmp);
	free(tmp);
	str_str = perevorot(str_str);
	if (inf_mod.f_f_w == 0)
	{
		if (inf_mod.flag == '-')
			str_str = ft_width('-', inf_mod.w, str_str);
		else
			str_str = ft_width(inf_mod.flag, inf_mod.w, str_str);
	}
	str_str = perevorot(str_str);
	return (str_str);
}

char	*ft_obrabotchik_for_s(t_mod inf_mod,
char *str, int flag)
{
	if (inf_mod.f_f_ac == 0 && inf_mod.ac < 0)
		inf_mod.f_f_ac = 1;
	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	str = perevorot(str);
	if (inf_mod.f_f_w == 0 && inf_mod.w < 0)
	{
		inf_mod.flag = '-';
		inf_mod.w *= -1;
	}
	str = ft_accu_for_s(inf_mod, str);
	if (flag)
	{
		ft_putstr_fd(str, 1);
		return (str);
	}
	return (str);
}

int		print_str(const char *format, int *i)
{
	int		count;

	count = 0;
	while (format[*i] != '\0' && format[*i] != '%')
	{
		ft_putchar_fd(format[*i], 1);
		++(*i);
		++count;
	}
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list argptr;
	int		count;
	int		i;

	va_start(argptr, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		count = count + print_str(format, &i);
		if (format[i] == '%')
			count = count + parce(format, argptr, &i);
	}
	va_end(argptr);
	return (count);
}
