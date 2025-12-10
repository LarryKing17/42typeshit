/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:22 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/10 15:36:53 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *s)
{
    int	i;

    if (!s)
        return (1);
    i = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;
    return (s[i] == '\0');
}

void	free_split(char **tab)
{
    int	i;

    if (!tab)
        return ;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void	free_config(t_config *cfg)
{
    int	i;

    if (!cfg)
        return ;
    free(cfg->tex.north);
    free(cfg->tex.south);
    free(cfg->tex.east);
    free(cfg->tex.west);
    if (cfg->map.grid)
    {
        i = 0;
        while (cfg->map.grid[i])
        {
            free(cfg->map.grid[i]);
            i++;
        }
        free(cfg->map.grid);
    }
}
