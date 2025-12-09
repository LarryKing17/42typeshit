/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:15:50 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/09 14:10:12 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_line(char *line, t_config *cfg, int *map_started)
{
    // Si la map n'a PAS encore commencé → on attend les textures/couleurs
    if (*map_started == 0)
    {
        if (ft_strncmp(line, "NO ", 3) == 0)
            return (parse_texture(line, &cfg->tex.north));
        if (ft_strncmp(line, "SO ", 3) == 0)
            return (parse_texture(line, &cfg->tex.south));
        if (ft_strncmp(line, "WE ", 3) == 0)
            return (parse_texture(line, &cfg->tex.west));
        if (ft_strncmp(line, "EA ", 3) == 0)
            return (parse_texture(line, &cfg->tex.east));

        if (ft_strncmp(line, "F ", 2) == 0)
            return (parse_color(line + 2, &cfg->floor));
        if (ft_strncmp(line, "C ", 2) == 0)
            return (parse_color(line + 2, &cfg->ceiling));

        // Ligne vide → OK mais avant la map seulement
        if (line[0] == '\0')
            return (0);

        // Sinon → ceci EST le début de la map
        *map_started = 1;
    }

    // Ici : map_started == 1 → cette ligne doit être de la map
    // On vérifie que la ligne contient uniquement des chars de map
    int i = 0;
    while (line[i])
    {
        char c = line[i];
        if (c != ' ' && c != '0' && c != '1' &&
            c != 'N' && c != 'S' && c != 'E' && c != 'W')
            return (1); // ERREUR si ligne invalide dans la map
        i++;
    }

    return (parse_map(line, cfg));
}