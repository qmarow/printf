#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

t_mod	get_width(const char *format, t_mod inf_mod, int *i, va_list argptr)
{
	if (ft_isdigit(format[*i]))
	{
		inf_mod.w = ft_atoi((char*)format + *i);
		while (ft_isdigit(format[*i]))
			++(*i);
	}
	else
	{
		inf_mod.w = va_arg(argptr, int);
		++(*i);
	}
	inf_mod.f_f_w = 0;
	return (inf_mod);
}

t_mod	get_accuracy(const char *format, t_mod inf_mod, int *i, va_list argptr)
{
	if (ft_isdigit(format[*i]))
	{
		inf_mod.ac = ft_atoi((char*)format + *i);
		while (ft_isdigit(format[*i]))
			++(*i);
		inf_mod.f_f_ac = 0;
	}
	else if (format[*i] == '*')
	{
		++(*i);
		inf_mod.ac = va_arg(argptr, int);
		inf_mod.f_f_ac = 0;
	}
	else
	{
		inf_mod.f_f_ac = 2;
		inf_mod.ac = 0;
	}
	return (inf_mod);
}

int		check_specifier(char *format, t_mod inf_mod, int *i, va_list argptr)
{
	inf_mod.sp = format[(*i)++];
	if (inf_mod.f_f_ac == 0 && (inf_mod.sp == 'd'
	|| inf_mod.sp == 'i')
	&& inf_mod.ac == 0 && inf_mod.flag == '0')
		inf_mod.flag = '.';
	inf_mod.minus = '_';
	return (ft_handler(inf_mod, argptr));
}

int		process_zero(int *i, const char *format, t_mod inf_mod)
{
	int		count;
	char	*str;
	char	*tmp;

	count = 0;
	inf_mod.sp = 's';
	if (inf_mod.f_f_ac == 2)
		inf_mod.f_f_ac = 1;
	if (inf_mod.f_f_ac == 0 && inf_mod.ac == 0)
		inf_mod.f_f_ac = 1;
	if (inf_mod.f_f_w == 0)
		inf_mod.f_f_w = 1;
	str = ft_substr(format, *i, 1);
	tmp = str;
	str = ft_obrabotchik_for_s(inf_mod, str, 1);
	free(tmp);
	count = ft_strlen(str);
	free(str);
	++(*i);
	return (count);
}

int		parce(const char *format, va_list argptr, int *i)
{
	t_mod	inf_mod;
	int		count;

	count = 0;
	inf_mod.flag = '.';
	if (!format[++(*i)])
		return (0);
	while ((format[(*i)] == '-' || format[*i] == '0'))
	{
		count = (format[*i] == '-') ? 1 : count;
		inf_mod.flag = (format[(*i)++]);
	}
	if (count)
		inf_mod.flag = '-';
	if ((inf_mod.f_f_w = 1) && (format[*i] == '*' || ft_isdigit(format[*i])))
		inf_mod = get_width(format, inf_mod, i, argptr);
	if ((inf_mod.f_f_ac = 1) && format[*i] == '.' && ++(*i))
		inf_mod = get_accuracy(format, inf_mod, i, argptr);
	if (ft_strchr("diupxXocs", format[*i]) && format[*i])
		count = check_specifier((char*)format, inf_mod, i, argptr);
	else if (ft_strchr("%%", format[*i]) && format[*i])
		count = process_zero(i, format, inf_mod);
	return (count);
}
