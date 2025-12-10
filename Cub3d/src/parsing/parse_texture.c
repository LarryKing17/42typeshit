/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:19:31 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/10 14:46:21 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_texture(char *line, char **texture_path)
{
    char **split;
    char *trimmed;

    if (*texture_path != NULL)
        return (printf("Error\nTexture already defined\n"), 1);

    split = ft_split(line, ' ');
    if (!split)
        return (printf("Error\nMalloc failed\n"), 1);

    if (!split[0] || !split[1] || split[2] != NULL)
    {
        printf("Error\nInvalid texture line: %s\n", line);
        ft_free_tab(split);
        return (1);
    }

    trimmed = ft_strtrim(split[1], " \t");
    if (!trimmed)
    {
        ft_free_tab(split);
        return (printf("Error\nMalloc failed\n"), 1);
    }

    *texture_path = trimmed;  // déjà dupliqué via ft_strtrim

    ft_free_tab(split);
    return (0);
}