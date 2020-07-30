/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_w_ac.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmarowak <qmarowak@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:34:23 by qmarowak          #+#    #+#             */
/*   Updated: 2020/07/30 09:34:25 by qmarowak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "printf.h"

char	*ft_width(char flag, int width, char *str)
{
	int		i;
	char	sim;
	char	*tmp;
	char	*free_str;

	i = -1;
	sim = (flag == '.') ? ' ' : flag;
	free_str = NULL;
	sim = (width < 0) ? '-' : sim;
	width = (width < 0) ? width * -1 : width;
	while (str[++i] != '\0' && width-- >= 0)
		if (width == -1)
			return (str);
	tmp = ft_strdup(" ");
	if (sim != '-')
		while (width--)
			str = ft_strjoin(str, ft_memset(tmp, sim, 1), 1);
	else
		while (width-- && (free_str = str))
		{
			str = ft_strjoin(ft_memset(tmp, ' ', 1), str, 0);
			free(free_str);
		}
	free(tmp);
	return (str);
}

char	*ft_accuracy(t_mod inf_mod, char *str, char *dup_str, int *minus)
{
	int		i;
	int		accuracy;
	char	flag;

	accuracy = (inf_mod.ac < 0) ? 0 : inf_mod.ac;
	flag = inf_mod.flag;
	if (inf_mod.ac < 0)
	{
		free(dup_str);
		return (str);
	}
	else
		i = ft_strlen(str);
	free(str);
	if (*minus == ' ' && inf_mod.f_f_ac == 0 && inf_mod.f_f_w == 0
	&& inf_mod.ac < inf_mod.w && inf_mod.ac > (int)ft_strlen(dup_str))
		*minus = '-';
	dup_str = ft_width('0', accuracy, dup_str);
	if (inf_mod.sp == 'd' || inf_mod.sp == 'i')
		dup_str = (*minus == '-') ? ft_strjoin(dup_str, "-", 1) : dup_str;
	dup_str = (inf_mod.sp == 'p') ? ft_strjoin(dup_str, "x0", 1) : dup_str;
	dup_str = (flag != '-') ? ft_width('.', i, dup_str)
	: ft_width('-', i, dup_str);
	return (dup_str);
}
