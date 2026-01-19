/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:44:20 by idridi            #+#    #+#             */
/*   Updated: 2024/10/28 18:18:48 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*sr;
	unsigned char	*des;

	i = 0;
	sr = (unsigned char *)src;
	des = (unsigned char *)dest;
	if (src == dest || n == 0)
		return (dest);
	if (des > sr)
	{
		while (n-- > 0)
		{
			des[n] = sr[n];
		}
	}
	else
	{
		while (i < n)
		{
			des[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
/*
int main(void)
{
	char dest[] = "iehvvmkub";
	const char src[] = "salut les amis";
	ft_memmove(dest, src, 8);
	printf("%s \n", dest);
}*/