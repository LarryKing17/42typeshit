/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:06:55 by idridi            #+#    #+#             */
/*   Updated: 2024/10/29 11:59:10 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	tot;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	tot = nmemb * size;
	ret = malloc(tot);
	if (!ret)
		return (NULL);
	ft_bzero(ret, tot);
	return (ret);
}
