/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:47:36 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/10 14:48:54 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int convert_rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static int is_valid_rgb(int r, int g, int b)
{
    return !(r < 0 || r > 255 ||
             g < 0 || g > 255 ||
             b < 0 || b > 255);
}

int parse_color(char *line, t_rgb *color)
{
    char **split;
    char *r_str;
    char *g_str;
    char *b_str;
    int   r, g, b;

    split = ft_split(line, ',');
    if (!split)
        return (printf("Error\nMalloc failed\n"), 1);

    // ❌ split[3] ne doit PAS exister, sinon il y a trop de valeurs
    if (!split[0] || !split[1] || !split[2] || split[3] != NULL)
    {
        ft_free_tab(split);
        return (printf("Error\nInvalid RGB format: %s\n", line), 1);
    }

    // Trim pour éviter les espaces ex: "220, 100, 20"
    r_str = ft_strtrim(split[0], " \t");
    g_str = ft_strtrim(split[1], " \t");
    b_str = ft_strtrim(split[2], " \t");

    // Trim malloc failed ?
    if (!r_str || !g_str || !b_str)
    {
        free(r_str);
        free(g_str);
        free(b_str);
        ft_free_tab(split);
        return (printf("Error\nMalloc failed\n"), 1);
    }

    // Convertir
    r = ft_atoi(r_str);
    g = ft_atoi(g_str);
    b = ft_atoi(b_str);

    free(r_str);
    free(g_str);
    free(b_str);
    ft_free_tab(split);

    if (!is_valid_rgb(r, g, b))
        return (printf("Error\nRGB must be between 0 and 255\n"), 1);

    color->red = r;
    color->green = g;
    color->blue = b;
    color->value = convert_rgb_to_int(r, g, b);

    return (0);
}
