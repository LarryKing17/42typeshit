/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:52:18 by zvalenti          #+#    #+#             */
/*   Updated: 2025/11/27 17:01:03 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_map(char *line, t_config *cfg)
{
    char **new_grid;
    int   i;

    // Si c'est la première ligne de la map → initialisation
    if (cfg->map.height == 0)
    {
        cfg->map.grid = malloc(sizeof(char *) * 2);
        if (!cfg->map.grid)
            return (1);

        cfg->map.grid[0] = ft_strdup(line);
        cfg->map.grid[1] = NULL;

        cfg->map.height = 1;
        cfg->map.width = ft_strlen(line);

        return (0);
    }

    // Si la map a déjà commencé → reallocer pour ajouter une ligne
    new_grid = malloc(sizeof(char *) * (cfg->map.height + 2));
    if (!new_grid)
        return (1);

    // Copier les anciennes lignes dans le nouveau tableau
    i = 0;
    while (i < cfg->map.height)
    {
        new_grid[i] = cfg->map.grid[i];
        i++;
    }

    // Ajouter la nouvelle ligne à la suite
    new_grid[i] = ft_strdup(line);
    new_grid[i + 1] = NULL;

    free(cfg->map.grid);
    cfg->map.grid = new_grid;

    // Mise à jour des dimensions
    cfg->map.height++;
    if (ft_strlen(line) > cfg->map.width)
        cfg->map.width = ft_strlen(line);

    return (0);
}
