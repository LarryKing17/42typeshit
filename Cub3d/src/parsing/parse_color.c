/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:47:36 by zvalenti          #+#    #+#             */
/*   Updated: 2025/11/26 16:48:24 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int parse_color(char *str, int *color)
{
    char    **split;
    int     r, g, b;

    // Supprime les espaces avant la couleur
    while (*str == ' ' || *str == '\t')
        str++;

    // On split sur les virgules : "220,100,0" → ["220","100","0"]
    split = ft_split(str, ',');
    if (!split)
        return (error_msg("Malloc error"));

    // On doit avoir exactement 3 valeurs sinon erreur
    if (!split[0] || !split[1] || !split[2] || split[3])
    {
        ft_free_tab(split);
        return (error_msg("Color must be R,G,B"));
    }

    // Convertir les 3 chaînes en entiers
    r = ft_atoi(split[0]);
    g = ft_atoi(split[1]);
    b = ft_atoi(split[2]);

    ft_free_tab(split);

    // Vérifier que chaque valeur est dans [0..255]
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (error_msg("RGB values must be 0-255"));

    // Convertir en un entier final : 0xRRGGBB
    *color = (r << 16) | (g << 8) | b;

    return (0);
}
