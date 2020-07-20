/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmarowak <qmarowak@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 10:06:30 by qmarowak          #+#    #+#             */
/*   Updated: 2020/05/19 15:40:09 by qmarowak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char	*str;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (*(s1 + ++i) != '\0')
		*(str + i) = *(s1 + i);
	while (*s2 != '\0')
		*(str + i++) = *(s2++);
	*(str + i) = '\0';
	if (flag)
		free(s1);
	return (str);
}
