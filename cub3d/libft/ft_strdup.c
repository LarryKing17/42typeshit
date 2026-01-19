/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:01:58 by idridi            #+#    #+#             */
/*   Updated: 2024/10/29 12:06:02 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (s[i])
		i++;
	copy = (char *) malloc (sizeof (char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	while (s[j])
	{
		copy[j] = s[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
