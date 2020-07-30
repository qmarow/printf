/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmarowak <qmarowak@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 09:35:11 by qmarowak          #+#    #+#             */
/*   Updated: 2020/07/30 09:35:14 by qmarowak         ###   ########.fr       */
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
