/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idridi <idridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:14:24 by idridi            #+#    #+#             */
/*   Updated: 2026/01/22 13:42:58 by idridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int	get_texture_color(t_texture *tex, int x, int y)
{
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	return (*(int *)(tex->data + y * tex->size_line + x * (tex->bpp / 8)));
}

int	load_texture(t_data *d, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->size_line, &tex->endian);
	return (1);
}

int	load_all_textures(t_data *d)
{
	if (!load_texture(d, &d->tex_no, d->scene.tex.no))
		return (0);
	if (!load_texture(d, &d->tex_so, d->scene.tex.so))
		return (0);
	if (!load_texture(d, &d->tex_we, d->scene.tex.we))
		return (0);
	if (!load_texture(d, &d->tex_ea, d->scene.tex.ea))
		return (0);
	return (1);
}

int	rotate(double *dx, double *dy, double angle)
{
	double	old_dx;

	old_dx = *dx;
	*dx = old_dx * cos(angle) - (*dy) * sin(angle);
	*dy = old_dx * sin(angle) + (*dy) * cos(angle);
	return (0);
}

void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}