/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:06:35 by idridi            #+#    #+#             */
/*   Updated: 2024/10/28 18:19:53 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		if (size > ft_strlen((char *)src))
			size = ft_strlen((char *)src) + 1;
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		i = 0;
	}
	while (src[i])
		i++;
	return (i);
}
/* int main(void)
{
	char a[] = "";
	char c[] = "cafdbca";
	ft_strlcpy(c, a, 0);
	printf("%s \n", c);
	printf("%d \n", ft_strlcpy(c, a, 5));
}*/