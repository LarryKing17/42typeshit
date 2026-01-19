/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:01:20 by idridi            #+#    #+#             */
/*   Updated: 2024/10/28 14:51:58 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *)big);
	if (ft_strlen((char *)little) > ft_strlen((char *)big))
		return (NULL);
	while ((i + j) < len)
	{
		if (little[j] == big[i + j])
			j++;
		else
		{
			i++;
			j = 0;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
	}
	return (NULL);
}
/*int main(void)
{
	char b[] = "salut";
	char c[] = "salut";
	printf("%s",ft_strnstr(b,c,4));
}*/