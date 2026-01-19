/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:17:49 by idridi            #+#    #+#             */
/*   Updated: 2025/01/11 18:46:48 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	i;
	int	signe;

	i = 0;
	res = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9'
		&& nptr[i])
	{
		res *= 10;
		res += (nptr[i] - 48);
		i++;
	}
	res *= signe;
	return (res);
}
/*int main(void)
{
	char b[] = "+-+ 98u4";
	printf("%d",ft_atoi(b));
}*/