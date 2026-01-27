/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:07:23 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 17:38:45 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	return (str[i] == '\0');
}

static int	parse_rgb_array(char *line, int *r, int *g, int *b)
{
	char	**rgb;

	line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (0);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_strtab(rgb);
		return (0);
	}
	if (!is_valid_rgb_value(rgb[0]) || !is_valid_rgb_value(rgb[1])
		|| !is_valid_rgb_value(rgb[2]))
	{
		free_strtab(rgb);
		return (0);
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	free_strtab(rgb);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(char *line, t_color *c)
{
	int	r;
	int	g;
	int	b;

	if (!parse_rgb_array(line, &r, &g, &b))
		return (0);
	c->r = r;
	c->g = g;
	c->b = b;
	c->value = (r << 16) | (g << 8) | b;
	return (1);
}
