/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utoomey <utoomey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:06:17 by qmarowak          #+#    #+#             */
/*   Updated: 2020/07/29 11:54:53 by utoomey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strchr(char *str, int ch)
{
	int i;

	i = -1;
	while (*((char*)str + ++i))
		if (*(str + i) == ch)
			return (((char*)str + i));
	if (ch == '\0')
		return (((char*)str + i));
	return (NULL);
}
