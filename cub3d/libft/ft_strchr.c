/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:13:26 by idridi            #+#    #+#             */
/*   Updated: 2024/10/28 19:11:05 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	i = 0;
	if (!c)
		return ((char *)(s + ft_strlen((char *)s)));
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			a = (char *)(s + i);
			return (a);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		a = (char *)(s + i);
		return (a);
	}
	return (NULL);
}
