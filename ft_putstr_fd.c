/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmarowak <qmarowak@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:06:09 by qmarowak          #+#    #+#             */
/*   Updated: 2020/05/19 15:38:36 by qmarowak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = -1;
	if (!s)
		return ;
	while (*(s + ++i) != '\0')
		ft_putchar_fd(*(s + i), fd);
}
