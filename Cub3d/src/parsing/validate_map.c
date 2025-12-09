/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:58:35 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/09 15:07:50 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                          CHECK VALID CHARACTERS                            */
/* ************************************************************************** */

int check_map_chars(t_config *cfg)
{
    int y = 0;
    int x;

    while (y < cfg->map.height)
    {
        x = 0;
        while (cfg->map.grid[y][x])
        {
            char c = cfg->map.grid[y][x];

            if (c != '0' && c != '1' && c != ' ' &&
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
                return (error_exit("Invalid map character", cfg), 1);
            x++;
        }
        y++;
    }
    return (0);
}

/* ************************************************************************** */
/*                          PLAYER VALIDATION                                 */
/* ************************************************************************** */

int check_player(t_config *cfg)
{
    int found = 0;

    for (int y = 0; y < cfg->map.height; y++)
    {
        for (int x = 0; cfg->map.grid[y][x]; x++)
        {
            char c = cfg->map.grid[y][x];

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (found == 1)
                    return (error_exit("Multiple player positions", cfg), 1);

                cfg->player_x = x;
                cfg->player_y = y;
                cfg->player_dir = c;
                found = 1;

                cfg->map.grid[y][x] = '0'; // devient du sol
            }
        }
    }
    if (!found)
        return (error_exit("No player found in map", cfg), 1);

    return (0);
}

/* ************************************************************************** */
/*                          MAP CLOSED CHECK                                  */
/* ************************************************************************** */

static int is_outside(t_config *cfg, int y, int x)
{
    return (y < 0 || x < 0 || y >= cfg->map.height ||
            x >= (int)ft_strlen(cfg->map.grid[y]));
}

static int is_open_space(t_config *cfg, int y, int x)
{
    if (cfg->map.grid[y][x] == ' ')
        return (1);

    if (cfg->map.grid[y][x] == '0')
    {
        if (is_outside(cfg, y - 1, x)) return (1);
        if (is_outside(cfg, y + 1, x)) return (1);
        if (is_outside(cfg, y, x - 1)) return (1);
        if (is_outside(cfg, y, x + 1)) return (1);

        if (cfg->map.grid[y - 1][x] == ' ') return (1);
        if (cfg->map.grid[y + 1][x] == ' ') return (1);
        if (cfg->map.grid[y][x - 1] == ' ') return (1);
        if (cfg->map.grid[y][x + 1] == ' ') return (1);
    }
    return (0);
}

int check_map_closed(t_config *cfg)
{
    for (int y = 0; y < cfg->map.height; y++)
    {
        for (int x = 0; cfg->map.grid[y][x]; x++)
        {
            if (is_open_space(cfg, y, x))
                return (error_exit("Map is not closed", cfg), 1);
        }
    }
    return (0);
}

/* ************************************************************************** */
/*                    CHECK TOP + BOTTOM WALLS                                */
/* ************************************************************************** */

int check_top_bottom_walls(t_config *cfg)
{
    int last = cfg->map.height - 1;

    for (int x = 0; cfg->map.grid[0][x]; x++)
        if (cfg->map.grid[0][x] != '1' && cfg->map.grid[0][x] != ' ')
            return (error_exit("Top row is leaking", cfg), 1);

    for (int x = 0; cfg->map.grid[last][x]; x++)
        if (cfg->map.grid[last][x] != '1' && cfg->map.grid[last][x] != ' ')
            return (error_exit("Bottom row is leaking", cfg), 1);

    return (0);
}

/* ************************************************************************** */
/*                        FINAL VALIDATION FUNCTION                           */
/* ************************************************************************** */

int validate_map(t_config *cfg)
{
    if (cfg->map.height == 0)
        return (error_exit("Map is empty", cfg), 1);

    if (check_map_chars(cfg)) return (1);
    if (check_player(cfg)) return (1);
    if (check_top_bottom_walls(cfg)) return (1);
    if (check_map_closed(cfg)) return (1);

    return (0);
}
