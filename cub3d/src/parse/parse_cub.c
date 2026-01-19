/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:09:52 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/16 16:13:36 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

char *skip_spaces(char *s)
{
    while (s && (*s == ' ' || (*s >= 9 && *s <= 13)))
        s++;
    return (s);
}

int parse_cub(char *path, t_scene *s)
{
    char **lines;
    int i;

    s->floor.value = -1;
    s->ceil.value = -1;
    if (!check_file_extension(path))
        exit_error("Invalid file extension");
    lines = read_file(path);
    if (!lines)
        exit_error("Cannot open file");

    i = 0;
    while (lines[i])
    {
        char *line = skip_spaces(lines[i]);
        if (!*line) // Ligne vide ou saut de ligne
        {
            i++;
            continue;
        }
        // Identification stricte des textures et couleurs
        if ((!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
            || (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
            || (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t'))
            || (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t')))
            {
                if (!parse_texture(line, s))
                    exit_error("Invalid texture line or duplicate texture"); 
            }
            
        else if (!ft_strncmp(line, "F ", 2))
        {
            if (!parse_color(line, &s->floor)) exit_error("Invalid floor color");
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            if (!parse_color(line, &s->ceil)) exit_error("Invalid ceiling color");
        }
        else if (is_map_line(lines[i])) // On passe lines[i] pour garder les espaces de début de map
        {
            // Sécurité : on ne commence pas la map si les textures manquent
            if (s->floor.value == -1 || s->ceil.value == -1 || !s->tex.no)
                exit_error("Missing textures/colors before map");
            
            i = parse_map(lines, i, s);
            // Après la map, tout doit être vide
            while (lines[i])
            {
                if (!is_empty_line(lines[i])) exit_error("Invalid content after map");
                i++;
            }
            break;
        }
        else
            exit_error("Invalid line in file");
        i++;
    }

    // Vérifications finales
    if (!s->tex.no || !s->tex.so || !s->tex.we || !s->tex.ea 
        || s->floor.value == -1 || s->ceil.value == -1)
        {
            printf("DEBUG: NO:%p SO:%p WE:%p EA:%p F:%d C:%d\n", 
            s->tex.no, s->tex.so, s->tex.we, s->tex.ea, s->floor.value, s->ceil.value);
           exit_error("Missing elements in .cub file");  
        }
       
    
    find_player(s); // Trouve le joueur ou exit_error si 0 ou multiple
    if (!check_closed(s)) // Floodfill pour les murs
        exit_error("Map not closed");

    free_strtab(lines);
    return (1);
}