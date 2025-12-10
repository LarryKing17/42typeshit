/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:19:31 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/10 15:21:31 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_texture(char *line, char **texture_path)
{
    char **split;
    char *trimmed;
    int fd;

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

    trimmed = ft_strtrim(split[1], " \t\n");
    ft_free_tab(split);
    if (!trimmed)
        return (printf("Error\nMalloc failed\n"), 1);

    /* Check extension .xpm */
    int len = ft_strlen(trimmed);
    if (len < 4 || ft_strncmp(trimmed + len - 4, ".xpm", 4) != 0)
    {
        free(trimmed);
        return (printf("Error\nTexture is not a .xpm file: %s\n", trimmed), 1);
    }

    /* Check that the .xpm file exists and is readable */
    fd = open(trimmed, O_RDONLY);
    if (fd < 0)
    {
        free(trimmed);
        return (printf("Error\nCannot open texture file: %s\n", trimmed), 1);
    }
    close(fd);

    /* Finally assign the valid path */
    *texture_path = trimmed;
    return (0);
}