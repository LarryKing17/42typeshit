/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bassem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:44:46 by idridi            #+#    #+#             */
/*   Updated: 2026/01/28 16:52:27 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	rot_press(int keycode, t_data *d)
{
	double	rot_speed;

	rot_speed = 0.05;
	if (keycode == 65363)
	{
		rotate(&d->dx, &d->dy, rot_speed);
		rotate(&d->plane_x, &d->plane_y, rot_speed);
	}
	if (keycode == 65361)
	{
		rotate(&d->dx, &d->dy, -rot_speed);
		rotate(&d->plane_x, &d->plane_y, -rot_speed);
	}
}

void	right_strafe(t_data *d, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = d->px - d->dy * move_speed;
	new_y = d->py + d->dx * move_speed;
	map_x = (int)(new_x / TILE_SIZE);
	map_y = (int)(new_y / TILE_SIZE);
	if (map_y >= 0 && map_y < d->scene.map.height
		&& map_x >= 0 && map_x < (int)ft_strlen(d->scene.map.grid[map_y])
		&& d->scene.map.grid[map_y][map_x] != '1')
	{
		d->px = new_x;
		d->py = new_y;
	}
}

void	left_strafe(t_data *d, double move_speed)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = d->px + d->dy * move_speed;
	new_y = d->py - d->dx * move_speed;
	map_x = (int)(new_x / TILE_SIZE);
	map_y = (int)(new_y / TILE_SIZE);
	if (map_y >= 0 && map_y < d->scene.map.height
		&& map_x >= 0 && map_x < (int)ft_strlen(d->scene.map.grid[map_y])
		&& d->scene.map.grid[map_y][map_x] != '1')
	{
		d->px = new_x;
		d->py = new_y;
	}
}
