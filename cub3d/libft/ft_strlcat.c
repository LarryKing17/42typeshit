/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:29:26 by idridi            #+#    #+#             */
/*   Updated: 2026/01/28 17:24:34 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	if (size > 0)
	{
		while (i + j < size - 1 && src[i])
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
		i = ft_strlen(src);
		i += j;
		return (i);
	}
	i = ft_strlen(src);
	return (i);
}
