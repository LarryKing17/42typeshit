/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:49:31 by idridi            #+#    #+#             */
/*   Updated: 2026/01/28 16:56:14 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	draw(t_data *d)
{
	draw_3d_view(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

int	key_press(int keycode, t_data *d)
{
	if (keycode == 65307)
	{
		free_scene(&d->scene);
		exit(0);
	}
	if (keycode == 119)
		key_handler(d, 1, 1);
	else if (keycode == 115)
		key_handler(d, -1, -1);
	else if (keycode == 100)
		right_strafe(d, 6.0);
	else if (keycode == 97)
		left_strafe(d, 6.0);
	else if (keycode == 65363 || keycode == 65361)
		rot_press(keycode, d);
	draw(d);
	return (0);
}

int	close_window(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (d)
		free_scene(&d->scene);
	exit(0);
}

int	init_data(t_data *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "MLX Player");
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->sl, &d->endian);
	draw(d);
	mlx_hook(d->win, 2, 1L << 0, key_press, d);
	mlx_hook(d->win, 17, 0, close_window, NULL);
	mlx_loop(d->mlx);
	return (0);
}

void	key_handler(t_data *d, int col, int row)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = d->px + (d->dx * col) * 6.0;
	new_y = d->py + (d->dy * row) * 6.0;
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
