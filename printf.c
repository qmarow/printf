#include <stdio.h>
#include <stdarg.h>
#include "./printf.h"

double	sum_series(int, ...);
char	*perevorot(char *str);
int		ft_printf(const char*, ...);


int main(void)
{
	 int             a = -4;
		int             b = 0;
		char    c = 'a';
		int             d = 2147483647;
		int             e = -2147483648;
		int             f = 42;
		int             g = 25;
		int             h = 4200;
		int             i = 8;
		int             j = -12;
		int             k = 123456789;
		int             l = 0;
		int             m = -12345678;
		char    *n = "abcdefghijklmnop";
		char    *o = "-a";
		char    *p = "-12";
		char    *q = "0";
		char    *r = "%%";
		char    *s = "-2147483648";
		char    *t = "0x12345678";
		char    *u = "-0";
//	   printf("%1i, %1d, %1d, %1d, %1d, %1d, %1d, %1d\n\n", i, j, k, l, m, c, e, d);
//	ft_printf("%*i, %*d, %*d, %*d, %*d, %*d, %*d, %*d\n", i, j, k, l, m, c, e, d);
	printf("%*i, %*d, %*d, %*d, %*d, %*d, %*d, %*d\n", i, j, k, l, m, c, e, d);
	return 0;
}

char	*ft_perevod(va_list argptr, char specifier, int sistem_ch)
{
	long long unsigned int	number;
	char					*tmp;
	char					*str;
	char					*sixteen;
	int						i;

	number = va_arg(argptr, long long unsigned int);
	str = ft_strdup("");
	i = 8;
	sixteen = (specifier == 'X') ? ft_strdup("0123456789ABCDEF")
	: ft_strdup("0123456789abcdef");
	//printf("number %llu\n", number);
	tmp = ft_strdup("");
	while (number && i--)
	{
		//printf("((%d))\n", number % sistem_ch);
		str = ft_strjoin(str, ft_memset(tmp, sixteen[number % sistem_ch], 1), 1);
		number /= sistem_ch;
	}
	free(sixteen);
	//str = (specifier == 'p') ? ft_strjoin(str, "x0", 1) : str;
	free(tmp);
	return (str);
}

char	*int_diu(va_list argptr, char specifier)
{
	long	number;
	char		*str;
	char		*tmp;
	int			flag;
	long		value;
	
	value = (specifier == 'u') ? va_arg(argptr, unsigned int) : va_arg(argptr, int);
	if (specifier != 'u')
		value = (int)value;
	if (value == 0)
		return (ft_strdup("0"));
	tmp = ft_strdup(" ");
	str = ft_strdup("");
	//printf("val - %u\n");
	number = value;
//	printf("\nnumber %d\n", number);
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

char	*new_str(char specifier, va_list argptr)
{
	char	*str;
	char	sim;

	if (specifier == 'd' || specifier == 'i' || specifier == 'u')
	{
		str = int_diu(argptr, specifier);
	//	printf("\n>>> %s\n", str);
	}
	else if (specifier == 'x' || specifier =='X' || specifier == 'p')
	{
		str = (ft_perevod(argptr, specifier, 16));
	}
	else if (specifier == 'o')
		str = ft_perevod(argptr, specifier, 8);
	else if (specifier == 'c')
	{
		str = ft_strdup(" ");
		sim = va_arg(argptr, int);
		str = ft_memset(str, sim, 1);
	}
	return (str);

}

char	*ft_width(char flag, int width, char *str)
{
	int		i;
	char	sim;
	char	*tmp;
	char	*free_str;

	i = -1;
	//printf("%d\n", width);
	sim = (flag == '.') ? ' ' : flag;
	tmp = ft_strdup(" ");
	width = (width < 0) ? width * -1 : width;
//	printf("witt -- %s", str);
	while (str[++i] != '\0' && width-- >= 0)
	{
	//	printf(">>>");
		if (width == -1)
		{
			//printf("\n|=====================\n");
			return (str);
		}
	}
	if (sim != '-')
	{
		while (width--)
			str = ft_strjoin(str, ft_memset(tmp, sim, 1), 1);
	}
	else
		while (width-- && (free_str = str))
		{
			str = ft_strjoin(ft_memset(tmp, ' ', 1), str, 0);
			free(free_str);
		}
	free(tmp);
	return (str);
}

char	*ft_accuracy(t_mod inf_mod, char *str, char *dup_str)
{
	int		i;
	int		accuracy;
	char	flag;

	accuracy = inf_mod.accuracy;
	flag = inf_mod.flag;
	i = ft_strlen(str);
	free(str);
	if (flag != '-')
	{
		//printf("<><><>");
		dup_str = ft_width('0', accuracy, dup_str);
		dup_str = (inf_mod.specifier == 'p') ? ft_strjoin(dup_str, "x0", 1) : dup_str;
		dup_str = ft_width('.', i, dup_str);
		return (dup_str);
	}
	else
	{
		dup_str = ft_width('0', accuracy, dup_str);
		dup_str = (inf_mod.specifier == 'p') ? ft_strjoin(dup_str, "x0", 1) : dup_str;
		dup_str = ft_width('-', i, dup_str);
		return (dup_str);
	}
}

char	*ft_accu_for_s(t_mod inf_mod, char *dup_str)
{
	int		i;
	int		a;
	char	*str_str;
	int		accuracy;

	accuracy = inf_mod.accuracy;
	i = ft_strlen(dup_str);
	a = -1;
	if (inf_mod.flag_for_accu != 1)
		str_str = (char*)malloc(sizeof(char) * (accuracy + 1));
	else
		str_str = perevorot(ft_strdup(dup_str));
	if (inf_mod.flag_for_accu != 1)
	{
		while (accuracy-- && i > 0)
			str_str[++a] = dup_str[--i];
		str_str[++a] = '\0';
	}
	if (inf_mod.flag_for_width == 0)
	{
	//	printf(">>>>>");
		if (inf_mod.flag != '-')
			str_str = ft_width('-', inf_mod.width, str_str);
		else
			str_str = ft_width('.', inf_mod.width, str_str);
	}
	return (str_str);
}

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

char	*ft_obrabotchik_for_s(t_mod inf_mod, va_list argptr)
{
	char	*str;

	str = ft_strdup(va_arg(argptr, char*));
	str = perevorot(str);
//	printf("str - %s\n", str);
	inf_mod.flag = (inf_mod.flag == '0') ? '.' : inf_mod.flag;
	str = ft_accu_for_s(inf_mod, str);
	return (str);
}

int		ft_obrabotchik(t_mod inf_mod, va_list argptr)
{
	char	*str;
	char	*dup_str;
	char	*tmp;
	int		number;

	number = 1;
	if (inf_mod.specifier != 's')
	{
		str = new_str(inf_mod.specifier, argptr);
		if (inf_mod.accuracy == 0 && *str == '0')
		{
		//	printf("----------");
			tmp = str;
		 	str = ft_strdup("");
			free(tmp);
		}
		
		dup_str = ft_strdup(str);
		if (inf_mod.flag_for_width == 0 && inf_mod.specifier != 'c')
		{
			if (inf_mod.specifier == 'p' && inf_mod.flag_for_accu == 1)
			{
				inf_mod.width -= 2;
				str = ft_width(inf_mod.flag, inf_mod.width, str);
				str = (inf_mod.specifier == 'p') ? ft_strjoin(str, "x0", 1) : str;
			}
			else 
				str = ft_width(inf_mod.flag, inf_mod.width, str);
		}
		else if (inf_mod.flag_for_width == 0)
			str = ft_width('.', inf_mod.width, str);
		if (inf_mod.flag_for_accu != 1 && inf_mod.specifier != 'c')
		{
			str = ft_accuracy(inf_mod, str, dup_str);
			//printf("\nstr -- %s\n", str);
		}
		str = perevorot(str);
	//	printf("value - |%s|\n", str);
	}
	else
		str = ft_obrabotchik_for_s(inf_mod, argptr);
//	printf("|_%s_|\n", str);
	
	ft_putstr_fd(str, 1);
	number = ft_strlen(str);
//	free(str);
	return (number);
}

int		zapolnenie_srtuct(const char *format, va_list argptr, int *i)
{
	t_mod	inf_mod;
	int		count;
	int		a;

	a = -1;
	inf_mod.flag = '.';
	++(*i);
	while (++a < 2 && (format[(*i)] == '-' || format[*i] == '0'))
	{
		inf_mod.flag = (format[(*i)++]);
	}
//	printf("format - |%c|", format[*i]);
	if ((inf_mod.flag_for_width = 1) && (format[*i] == '*' || ft_isdigit(format[*i])))
	{
		if (ft_isdigit(format[*i]))
		{
			inf_mod.width = ft_atoi((char*)format + *i);
		}
		else
		{		
			inf_mod.width = va_arg(argptr, int);
		}
		inf_mod.flag_for_width = 0;
		++(*i);
	}
	if ((inf_mod.flag_for_accu = 1) && format[*i] == '.' && ++(*i))
	{
		printf(">>>>");
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
	}
	inf_mod.specifier = format[*i];
	++(*i);
//	printf("w - |%d|, flag - |%c|, for_w - |%d|, for_a - |%d|, sp - |%c|\n", inf_mod.width, inf_mod.flag, inf_mod.flag_for_width, inf_mod.flag_for_accu, inf_mod.specifier);
	count = ft_obrabotchik(inf_mod, argptr);
//	printf("\nCOUNT - %d", count);
	return (count);
}

int		print_str(const char *format, int	*i)
{
	int		count;

	count  = 0;
	while (format[*i] != '\0' && format[*i] != '%')
	{
		ft_putchar_fd(format[*i], 1);
		//printf("\ncount - %d  |%c|\n", *i, format[*i]);
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
			count = count + zapolnenie_srtuct(format, argptr, &i);
	}
	va_end(argptr);
//	printf("\n_____count - %d\n", count);
	return (count);
}