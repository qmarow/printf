#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

t_mod	get_width(const char *format, t_mod inf_mod, int *i, va_list argptr)
{
	if (ft_isdigit(format[*i]))
	{
		inf_mod.width = ft_atoi((char*)format + *i);
		while (ft_isdigit(format[*i]))
			++(*i);
	}
	else
	{
		inf_mod.width = va_arg(argptr, int);
		++(*i);
	}
	inf_mod.flag_for_width = 0;
	return (inf_mod);
}

t_mod	get_accuracy(const char *format, t_mod inf_mod, int *i, va_list argptr)
{
	if (ft_isdigit(format[*i]))
	{
		inf_mod.accuracy = ft_atoi((char*)format + *i);
		while (ft_isdigit(format[*i]))
			++(*i);
		inf_mod.flag_for_accu = 0;
	}
	else if (format[*i] == '*')
	{
		++(*i);
		inf_mod.accuracy = va_arg(argptr, int);
		inf_mod.flag_for_accu = 0;
	}
	else
	{
		inf_mod.flag_for_accu = 2;
		inf_mod.accuracy = 0;
	}
	return (inf_mod);
}

int		check_specifier(char *format, t_mod inf_mod, int *i, va_list argptr)
{
	inf_mod.specifier = format[(*i)++];
	if (inf_mod.flag_for_accu == 0 && (inf_mod.specifier == 'd'
	|| inf_mod.specifier == 'i')
	&& inf_mod.accuracy == 0 && inf_mod.flag == '0')
		inf_mod.flag = '.';
	inf_mod.minus = '_';
	return (ft_obrabotchik(inf_mod, argptr));
}

void	processing_zero(int start, int *i, const char *format)
{
	*i = ++start;
	while ((format[*i] != '\0' || format[*i] == '%'))
	{
		while (format[*i] != '\0')
		{
			if (format[*i] == '%')
			{
				ft_putchar_fd(format[*i], 1);
				break ;
			}
			if (format[*i] == '\n')
				ft_putchar_fd('\n', 1);
			++(*i);
		}
		if (format[(*i)] == '\n')
			ft_putchar_fd('\n', 1);
		++(*i);
	}
}

int		parce(const char *format, va_list argptr, int *i)
{
	t_mod	inf_mod;
	int		count;
	int		start;

	start = *i;
	inf_mod.flag = '.';
	++(*i);
	if (format[*i] == '%' && ++(*i))
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	while ((format[(*i)] == '-' || format[*i] == '0'))
		inf_mod.flag = (format[(*i)++]);
	if ((inf_mod.flag_for_width = 1) &&
	(format[*i] == '*' || ft_isdigit(format[*i])))
		inf_mod = get_width(format, inf_mod, i, argptr);
	if ((inf_mod.flag_for_accu = 1) && format[*i] == '.' && ++(*i))
		inf_mod = get_accuracy(format, inf_mod, i, argptr);
	if (ft_strchr("diupxXocs", format[*i]))
		count = check_specifier((char*)format, inf_mod, i, argptr);
	else
		processing_zero(start, i, format);
	return (count);
}
