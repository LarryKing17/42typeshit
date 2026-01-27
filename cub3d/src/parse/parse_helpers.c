/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:10:00 by autopatch         #+#    #+#             */
/*   Updated: 2026/01/26 17:44:41 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strtab_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_strtab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	is_empty_line(char *l)
{
	if (!l)
		return (1);
	while (*l)
	{
		if (*l != ' ' && *l != '\t' && *l != '\n')
			return (0);
		l++;
	}
	return (1);
}

int	is_map_line(char *l)
{
	int	has_content;
	int	len;
	int	i;

	if (!l)
		return (0);
	len = 0;
	while (l[len] && l[len] != '\n')
		len++;
	if (len == 1 && (l[0] == '1' || l[0] == '0'))
		return (0);
	has_content = 0;
	i = 0;
	while (l[i] && l[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW\t", l[i]))
			return (0);
		if (l[i] == '0' || ft_strchr(" 1NSEW", l[i]))
			has_content = 1;
		i++;
	}
	return (has_content);
}

char	*skip_spaces(char *s)
{
	while (s && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	return (s);
}
