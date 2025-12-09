/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:52:18 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/09 15:05:24 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*
**  Ajoute une ligne brute de map dans cfg->map.grid
**  - on realloc une ligne de plus
**  - on duplique la ligne
*/
static int add_map_line(t_config *cfg, char *line)
{
    char **new_grid;
    int i;

    new_grid = malloc(sizeof(char *) * (cfg->map.height + 2));
    if (!new_grid)
        return (error_exit("Malloc failed in map realloc", cfg), 1);

    i = 0;
    while (i < cfg->map.height)
    {
        new_grid[i] = cfg->map.grid[i];
        i++;
    }

    new_grid[i] = ft_strdup(line);
    if (!new_grid[i])
        return (free(new_grid), error_exit("Malloc failed", cfg), 1);

    new_grid[i + 1] = NULL;

    free(cfg->map.grid);
    cfg->map.grid = new_grid;
    cfg->map.height++;

    return (0);
}

/*
**  parse_map():
**  → chaque ligne passée ici est forcément une ligne de map
**  → les lignes vides après le début sont interdites
*/
int parse_map(char *line, t_config *cfg)
{
    if (line[0] == '\0')
        return (error_exit("Empty line inside map", cfg), 1);

    if (add_map_line(cfg, line) != 0)
        return (1);

    return (0);
}
