/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:33:41 by idridi            #+#    #+#             */
/*   Updated: 2024/10/30 12:55:05 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strcount(char const *s, char c)
{
	size_t	strnb;
	size_t	i;

	strnb = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] != '\0' && s[i] == c)
			i++;
		strnb++;
	}
	return (strnb);
}

static char	*stdu(const char *s, int start, int end)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!ret)
		return (NULL);
	while (start < end)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(char const *str, char const c)
{
	size_t	i;
	size_t	j;
	int		k;
	char	**strs;

	i = 0;
	j = 0;
	strs = malloc((strcount(str, c) + 1) * sizeof(char *));
	if (!str || !strs)
		return (0);
	k = -1;
	while (i <= ft_strlen(str))
	{
		if (str[i] != c && k < 0)
			k = i;
		else if ((str[i] == c || i == ft_strlen(str)) && k >= 0)
		{
			strs[j++] = stdu(str, k, i);
			k = -1;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}
