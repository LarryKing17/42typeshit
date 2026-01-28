/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:45:16 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/28 15:36:57 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	init_player_from_scene(t_data *d)
{
	d->px = d->scene.px * TILE_SIZE;
	d->py = d->scene.py * TILE_SIZE;
	d->dx = d->scene.dx;
	d->dy = d->scene.dy;
	if (d->dx == 0 && d->dy == -1)
	{
		d->plane_x = 0.66;
		d->plane_y = 0;
	}
	if (d->dx == 0 && d->dy == 1)
	{
		d->plane_x = -0.66;
		d->plane_y = 0;
	}
	if (d->dx == 1 && d->dy == 0)
	{
		d->plane_x = 0;
		d->plane_y = 0.66;
	}
	if (d->dx == -1 && d->dy == 0)
	{
		d->plane_x = 0;
		d->plane_y = -0.66;
	}
}

int	main(int ac, char **av)
{
	t_data	d;

	ft_bzero(&d, sizeof(d));
	if (ac != 2)
		exit_error(NULL, NULL, "Usage: ./cub3D <map.cub>");
	if (!parse_cub(av[1], &d.scene))
		exit_error(&d.scene, NULL, "Invalid map");
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "cub3D");
	d.img = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.sl, &d.endian);
	if (!load_all_textures(&d))
		exit_error(&d.scene, NULL, "Failed to load textures");
	init_player_from_scene(&d);
	draw(&d);
	mlx_hook(d.win, 2, 1L << 0, key_press, &d);
	mlx_hook(d.win, 17, 0, close_window, &d);
	mlx_loop(d.mlx);
	free_scene(&d.scene);
	return (0);
}
