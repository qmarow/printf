#include <stdio.h>
#include "printf.h"
#include <unistd.h>

int     parce(const char *format, va_list argptr, int *i)
{
    t_mod	inf_mod;
	int		count;
    int     a;

    a = -1;
	while (++a < 2 && (inf_mod.flag = '.') && (format[++(*i)] == '-' || format[*i] == '0'))
    {
        if (format[*i] == '-')
        {
            inf_mod.flag = (format[(*i)++]);
            break;
        }
        inf_mod.flag = (format[(*i)++]);
    }
	if ((inf_mod.flag_for_width = 1) && (format[*i] == '*' || ft_isdigit(format[*i])))
	{
		//printf("____format - %c___", format[*i]);
		if (ft_isdigit(format[*i]))
		{
			inf_mod.width = ft_atoi((char*)format + *i);
		}
		else
		{		
			inf_mod.width = va_arg(argptr, int);
		}
		inf_mod.flag_for_width = 0;
		//printf("width - %d\n", inf_mod.width);
		++(*i);
	}
	if ((inf_mod.flag_for_accu = 1) && format[*i] == '.' && ++(*i))
	{
		if (ft_isdigit(format[*i]))
		{
			inf_mod.accuracy = ft_atoi((char*)format + *i);
			while (ft_isdigit(format[*i]))
				++(*i);
		}
		else
		{
			++(*i);
			inf_mod.accuracy = va_arg(argptr, int);
		}
		inf_mod.flag_for_accu = 0;
	}
	inf_mod.specifier = format[*i];
	++(*i);
	count = ft_obrabotchik(inf_mod, argptr);
//	printf("\nCOUNT - %d", count);
	return (count);
}