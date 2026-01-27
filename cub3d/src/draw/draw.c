/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:27:54 by idridi            #+#    #+#             */
/*   Updated: 2026/01/22 13:50:22 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	free_textures(t_data *d)
{
	if (d->tex_no.img)
		mlx_destroy_image(d->mlx, d->tex_no.img);
	if (d->tex_so.img)
		mlx_destroy_image(d->mlx, d->tex_so.img);
	if (d->tex_we.img)
		mlx_destroy_image(d->mlx, d->tex_we.img);
	if (d->tex_ea.img)
		mlx_destroy_image(d->mlx, d->tex_ea.img);
}

void	put_pixel(t_data *d, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	if (!d || !d->addr)
		return ;
	*(int *)(d->addr + y * d->sl + x * (d->bpp / 8)) = color;
}

void	draw_textured_column(t_data *d, t_ray *ray, int x)
{
	t_texture	*tex;
	t_tp		tp;

	tex = select_texture(d, ray);
	tp.step = (double)tex->height / (double)ray->line_height;
	tp.start = ray->draw_start - HEIGHT / 2;
	tp.tex_pos = tp.step * (tp.start + ray->line_height / 2);
	tp.y = -1;
	while (tp.y++ < ray->draw_start)
		put_pixel(d, x, tp.y, d->scene.ceil.value);
	tp.y = ray->draw_start - 1;
	while (tp.y++ <= ray->draw_end)
	{
		tp.tex_y = (int)tp.tex_pos;
		if (tp.tex_y < 0)
			tp.tex_y = 0;
		if (tp.tex_y >= tex->height)
			tp.tex_y = tex->height - 1;
		tp.tex_pos += tp.step;
		tp.color = get_texture_color(tex, ray->tex_x, tp.tex_y);
		put_pixel(d, x, tp.y, tp.color);
	}
	tp.y += -1;
	while (tp.y++ < HEIGHT)
		put_pixel(d, x, tp.y, d->scene.floor.value);
}

void	calculate_texture_x(t_data *d, t_ray *ray)
{
	double		wall_x;
	t_texture	*tex;

	if (ray->side == 0)
		wall_x = d->py + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = d->px + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex = select_texture(d, ray);
	ray->tex_x = (int)(wall_x * (double)tex->width);
	if (ray->tex_x >= tex->width)
		ray->tex_x = tex->width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = tex->width - 1 - ray->tex_x;
}

t_texture	*select_texture(t_data *d, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&d->tex_ea);
		else
			return (&d->tex_we);
	}
	else
	{
		if (ray->step_y > 0)
			return (&d->tex_so);
		else
			return (&d->tex_no);
	}
}





