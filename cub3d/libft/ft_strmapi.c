/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:36:51 by idridi            #+#    #+#             */
/*   Updated: 2024/10/30 18:55:14 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*a;

	i = 0;
	a = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!a)
		return (NULL);
	a[ft_strlen(s)] = '\0';
	while (s[i])
	{
		a[i] = f(i, s[i]);
		i++;
	}
	return (a);
}
