/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:45:12 by idridi            #+#    #+#             */
/*   Updated: 2026/01/22 13:48:53 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	pddp(t_ray *ray, t_data *d)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - d->px
				/ TILE_SIZE + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - d->py
				/ TILE_SIZE + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	perform_dda(t_data *d, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_y >= d->scene.map.height
			|| ray->map_x >= (int)ft_strlen(d->scene.map.grid[ray->map_y]))
			ray->hit = 1;
		else if (d->scene.map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	pddp(ray, d);
}


void	cast_ray(t_data *d, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = d->dx + d->plane_x * ray->camera_x;
	ray->ray_dir_y = d->dy + d->plane_y * ray->camera_x;
	ray->map_x = (int)(d->px / TILE_SIZE);
	ray->map_y = (int)(d->py / TILE_SIZE);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((d->px / TILE_SIZE) - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - (d->px / TILE_SIZE)) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((d->py / TILE_SIZE) - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - (d->py / TILE_SIZE)) * ray->delta_dist_y;
	}
}

void	draw_3d_view(t_data *d)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(d, &ray, x);
		perform_dda(d, &ray);
		calculate_wall_height(&ray);
		calculate_texture_x(d, &ray);
		draw_textured_column(d, &ray, x);
		x++;
	}
}
