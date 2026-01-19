/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:07:23 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/16 15:31:25 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_rgb_value(char *str)
{
    int i = 0;

    // 1. Sauter tous les espaces/tabs au début du segment splité
    while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
        i++;
    
    // 2. Vérifier qu'il y a bien un chiffre après les espaces
    if (!str[i] || !ft_isdigit(str[i]))
        return (0);
    
    // 3. Avancer tant que c'est un chiffre
    while (ft_isdigit(str[i]))
        i++;
    
    // 4. Sauter tous les espaces/tabs/newlines restants à la fin
    while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
        i++;
        
    // 5. Si on n'est pas arrivé au '\0', c'est qu'il y a un caractère interdit
    return (str[i] == '\0');
}

int parse_color(char *line, t_color *c)
{
    char    **rgb;
    int     i;

    line++; 
    rgb = ft_split(line, ',');
    if (!rgb)
        return (0);

    i = 0;
    while (rgb[i])
        i++;
    if (i != 3)
        return (free_strtab(rgb), 0);

    if (!is_valid_rgb_value(rgb[0]) || !is_valid_rgb_value(rgb[1]) 
        || !is_valid_rgb_value(rgb[2]))
        return (free_strtab(rgb), 0);

    c->r = ft_atoi(rgb[0]);
    c->g = ft_atoi(rgb[1]);
    c->b = ft_atoi(rgb[2]);
    free_strtab(rgb);

    // 1. Vérifier la validité des plages 0-255
    if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255 || c->b < 0 || c->b > 255)
        return (0);

    // 2. CALCULER LA VALEUR (C'est ce qui manque !)
    // On décale R de 16 bits, G de 8 bits et on ajoute B
    c->value = (c->r << 16) | (c->g << 8) | c->b;

    return (1);
}

