/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:47:36 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/08 14:42:25 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int convert_rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static int is_valid_rgb(int r, int g, int b)
{
    if (r < 0 || r > 255)
        return 0;
    if (g < 0 || g > 255)
        return (0);
    if (b < 0 || b > 255)
        return (0);
    return (1);
}

int parse_color(char *line, t_rgb *color)
{
    char **split;
    int     r;
    int     g;
    int     b;

    split = ft_split(line, ',');
    if(!split)
        return (1);
    if (!split[0] || !split[1] || !split[2] || !split[3])
    {
        ft_free_tab(split);
        return (1);
    }
    r = ft_atoi(split[0]);
    g = ft_atoi(split[1]);
    b = ft_atoi(split[2]);

    if (!is_valid_rgb(r, g, b))
        return (1);
    color->red = r;
    color->green = g;
    color->blue = b;
    color->value = convert_rgb_to_int(r, g, b);
    return (0);
}
