/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:08:39 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/15 16:56:38 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_map(char **lines, int i, t_scene *s)
{
    int start = i;
    int h = 0;

    // Copier uniquement les lignes consécutives de map
    while (lines[i])
    {
        if (!is_map_line(lines[i]))
            break; // FIN de la map détectée
        h++;
        i++;
    }

    if (h == 0)
        exit_error("No map found");

    s->map.grid = malloc(sizeof(char *) * (h + 1));
    if (!s->map.grid)
        exit_error("Malloc failed");

    int j = 0;
    int k = start;
    while (j < h)
        s->map.grid[j++] = ft_strdup(lines[k++]);

    s->map.grid[j] = NULL;
    s->map.height = j;

    return i; // retourne l'index de la première ligne après la map
}







