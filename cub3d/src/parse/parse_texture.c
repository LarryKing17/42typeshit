/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:07:44 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/16 16:07:44 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

static int	is_valid_texture_path(char *path)
{
    int len;

    if (!path || !*path)
        return (0);

    len = ft_strlen(path);
    // On vérifie juste si le chemin est assez long et finit par .xpm
    if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
        return (0);

    return (1);
}

int parse_texture(char *line, t_scene *s)
{
    char    **target;
    char    *path;
    int     i;

    // 1. Sauter les espaces au début
    while (*line == ' ' || *line == '\t')
        line++;

    // 2. Identifier quelle texture on remplit
    if (!ft_strncmp(line, "NO", 2)) target = &s->tex.no;
    else if (!ft_strncmp(line, "SO", 2)) target = &s->tex.so;
    else if (!ft_strncmp(line, "WE", 2)) target = &s->tex.we;
    else if (!ft_strncmp(line, "EA", 2)) target = &s->tex.ea;
    else return (0);

	if(*target != NULL)
		return (0);

    line += 2; // Passer l'identifiant (NO, SO, etc.)

    // 3. Sauter les espaces avant le chemin
    while (*line == ' ' || *line == '\t')
        line++;

    // 4. NETTOYAGE : Supprimer espaces, tabs et retours à la ligne à la fin
    i = ft_strlen(line);
    while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t' 
          || line[i - 1] == '\n' || line[i - 1] == '\r'))
    {
        line[i - 1] = '\0';
        i--;
    }

    // 5. VÉRIFICATIONS FINALES
    // - Le chemin ne doit pas être vide
    // - La texture ne doit pas avoir déjà été remplie (doublon)
    // - L'extension doit être .xpm
    if (*line == '\0' || *target != NULL || !is_valid_texture_path(line))
        return (0);

    // 6. ALLOCATION
    path = ft_strdup(line);
    if (!path)
        return (0);

    *target = path;
    return (1);
}