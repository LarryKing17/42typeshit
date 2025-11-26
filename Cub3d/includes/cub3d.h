/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:50:47 by zvalenti          #+#    #+#             */
/*   Updated: 2025/11/26 16:43:19 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "libft/h"

typedef struct s_rgb
{
	int red;
	int green;
	int blue;
	int value;
}	t_rgb;

typedef struct s_textures
{
	char *north;
	char *south;
	char *east;
	char *west;
}	t_textures;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
}	t_map;

typedef struct s_config
{
	t_textures tex;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;

	int			player_x;
	int			player_y;
	char		player_dir;
}	t_config;

int parse_file(char *path, t_config *cfg);

int parse_line(char *line, t_config *cfg, int *map_started);

int parse_texture(char *line, char **texture_path);

#endif