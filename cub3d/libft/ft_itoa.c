/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:28:04 by idridi            #+#    #+#             */
/*   Updated: 2024/10/30 18:26:46 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		i;
	long	j;

	j = n;
	i = len(n);
	a = malloc(i + 1 * sizeof(char));
	if (n == 0)
		a[0] = '0';
	if (!a)
		return (NULL);
	if (j < 0)
	{
		j *= -1;
		a[0] = '-';
	}
	while (j > 0)
	{
		a[--i] = j % 10 + '0';
		j /= 10;
	}
	a[len(n)] = '\0';
	return (a);
}
