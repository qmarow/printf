#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

char    *handler_for_p(t_mod *inf_mod, char *str)
{
    if ((*inf_mod).specifier == 'p' && (*inf_mod).flag_for_accu == 1 && (*inf_mod).flag_for_width == 1
    && ft_strlen((const char*)str))
		str = ft_strjoin(str, "x0", 1);
	else if ((*inf_mod).specifier == 'p' && (*inf_mod).flag_for_width == 0 && (*inf_mod).flag == '.' && (ft_strlen((const char*)str)))
	{
		(*inf_mod).specifier = 'x';
		str = ft_strjoin(str, "x0", 1);
	}
	if ((*inf_mod).specifier == 'p' && !(ft_strlen((const char*)str)))
	{
		(*inf_mod).specifier = 'x';
		str = ft_strdup(")lin(");
	}
    return (str);
}

int		ft_handler(t_mod inf_mod, va_list argptr)
{
	char	*str;
	char	*dup_str;
	char	*tmp;
	int		number;

	number = 1;
	if (inf_mod.specifier != 's')
	{
		str = new_str(inf_mod.specifier, argptr);
        str = (inf_mod.specifier == 'p') ? handler_for_p(&inf_mod, str) : str;
		if (inf_mod.specifier == 'c' && inf_mod.flag_for_width == 0 && !(ft_strlen((const char*)str))
		&& inf_mod.width != 0)
			inf_mod.width = (inf_mod.width < 0) ? inf_mod.width + 1 : inf_mod.width - 1;
		if (inf_mod.flag_for_accu == 0 && (inf_mod.specifier == 'd' || inf_mod.specifier == 'i')
		&& inf_mod.accuracy > 0 && inf_mod.flag == '0' && ft_strchr((const char*)str, '-') &&((int)ft_strlen((const char*)str) - 1))
			inf_mod.flag = '.';
		if (ft_strchr((const char*)str, '-') && ((inf_mod.flag_for_accu == 0 && inf_mod.accuracy > 0 && inf_mod.accuracy > ((int)ft_strlen((const char*)str) - 1))
		|| (inf_mod.flag == '0' && inf_mod.flag_for_width == 0)) &&
		(inf_mod.specifier == 'd' || inf_mod.specifier == 'i'))
		{
			if (inf_mod.flag_for_width == 0 && inf_mod.width < 0)
			{
				inf_mod.width *= -1;
				if ((inf_mod.flag == '0' && inf_mod.flag_for_width == 0) ||
				(inf_mod.accuracy < ((int)ft_strlen((const char*)str)) && inf_mod.flag_for_width == 0) ||
				(inf_mod.flag_for_accu == 0 && inf_mod.flag_for_width == 0 && inf_mod.accuracy > ((int)ft_strlen((const char*)str) - 1) &&
				inf_mod.width > inf_mod.accuracy))
					inf_mod.width = (inf_mod.width < 0) ? inf_mod.width + 1 : inf_mod.width - 1;
				inf_mod.width *= -1;
			}
			else
				if ((inf_mod.flag == '0' && inf_mod.flag_for_width == 0) ||
				(inf_mod.accuracy < ((int)ft_strlen((const char*)str)) && inf_mod.flag_for_width == 0) ||
				(inf_mod.flag_for_accu == 0 && inf_mod.flag_for_width == 0 && inf_mod.accuracy > ((int)ft_strlen((const char*)str) - 1) &&
				inf_mod.width <= (inf_mod.accuracy + 1) && inf_mod.width > inf_mod.accuracy))
					inf_mod.width = (inf_mod.width < 0) ? inf_mod.width + 1 : inf_mod.width - 1;
			str = ft_substr((const char*)str, 0, (ft_strlen(str) - 1));
			inf_mod.minus = ' ';
			number = '-';
		}
		if (inf_mod.flag_for_accu != 1 && inf_mod.accuracy == 0 && ft_strlen((const char*)str) == 1 && *str == '0')
		{
			tmp = str;
		 	str = ft_strdup("");
			free(tmp);
		}
		dup_str = ft_strdup(str);
		if (inf_mod.flag_for_width == 0)
		{
			if (inf_mod.width < 0)
				inf_mod.flag = '-';
			if (inf_mod.specifier == 'p' && inf_mod.flag_for_accu == 1)
			{
				inf_mod.width -= 2;
				str = ft_width(inf_mod.flag, inf_mod.width, str);
				str = (inf_mod.specifier == 'p') ? ft_strjoin(str, "x0", 1) : str;
			}
			else 
				str = ft_width(inf_mod.flag, inf_mod.width, str);
		}
		if (inf_mod.flag_for_accu != 1 && inf_mod.specifier != 'c')
		{
			str = ft_accuracy(inf_mod, str, dup_str, &inf_mod.minus);
		}
		if (inf_mod.minus == ' ')
			str = (number == '-') ? ft_strjoin(str, "-", 1) : str;
		str = perevorot(str);
	}
	else
		str = ft_obrabotchik_for_s(inf_mod, argptr);
	ft_putstr_fd(str, 1);
	number = ft_strlen(str);
	// if (inf_mod.flag_for_accu == 1 && inf_mod.flag_for_width == 1)
	// 	free(dup_str);
	free(str);
	return (number);
}