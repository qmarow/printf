#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

char	*perevorot(char *str)
{
	char	*dup_str;
	int		size;
	int		i;

	i = -1;
	size = ft_strlen(str) + 1;
	dup_str = (char*)malloc(sizeof(char) * size);
	--size;
	while (--size >= 0)
		dup_str[++i] = str[size];
	dup_str[++i] = '\0';
	free(str);
	return (dup_str);
}

char	*ft_perevod(va_list argptr, t_mod inf_mod, int sis_ch)
{
	long unsigned			number;
	char					*tmp;
	char					*str;
	char					*sixteen;

	number = (inf_mod.sp == 'p') ? va_arg(argptr, long unsigned)
	: va_arg(argptr, unsigned);
	if (inf_mod.sp != 'p')
		number = (unsigned)number;
	if (inf_mod.sp != 'p' && number == 0)
		return (ft_strdup("0"));
	if (inf_mod.sp == 'p' && inf_mod.f_f_ac != 2 && number == 0)
		return (ft_strdup("0"));
	str = ft_strdup("");
	sixteen = (inf_mod.sp == 'X') ? ft_strdup("0123456789ABCDEF")
	: ft_strdup("0123456789abcdef");
	tmp = ft_strdup(" ");
	while (number > 0)
	{
		str = ft_strjoin(str, ft_memset(tmp, sixteen[number % sis_ch], 1), 1);
		number /= sis_ch;
	}
	free(sixteen);
	free(tmp);
	return (str);
}

char	*int_diu(va_list argptr, char sp)
{
	long		number;
	char		*str;
	char		*tmp;
	int			flag;
	long		value;

	value = (sp == 'u') ? va_arg(argptr, unsigned int) : va_arg(argptr, int);
	if (sp != 'u')
		value = (int)value;
	if (value == 0)
		return (ft_strdup("0"));
	tmp = ft_strdup(" ");
	str = ft_strdup("");
	number = value;
	flag = (number < 0) ? 1 : 0;
	number *= (number < 0) ? -1 : 1;
	while (number)
	{
		str = ft_strjoin(str, ft_memset(tmp, (number % 10) + '0', 1), 1);
		number /= 10;
	}
	str = (flag) ? ft_strjoin(str, ft_memset(tmp, '-', 1), 1) : str;
	free(tmp);
	return (str);
}

char	*handler_for_i_d2(t_mod *inf_mod, char *str, int *number)
{
	char	*tmp;

	tmp = NULL;
	if (inf_mod->f_f_w == 0)
	{
		inf_mod->w *= -1;
		if ((inf_mod->flag == '0' && inf_mod->f_f_w == 0)
		|| (inf_mod->ac < (int)ft_strlen(str) && inf_mod->f_f_w == 0)
		|| (inf_mod->f_f_ac == 0 && inf_mod->f_f_w == 0
		&& inf_mod->ac > (int)(ft_strlen(str) - 1) && inf_mod->w > inf_mod->ac))
			inf_mod->w = (inf_mod->w < 0) ? inf_mod->w + 1 : inf_mod->w - 1;
		inf_mod->w *= -1;
	}
	tmp = str;
	str = ft_substr((const char*)str, 0, (ft_strlen(str) - 1));
	free(tmp);
	inf_mod->minus = ' ';
	*number = '-';
	return (str);
}
