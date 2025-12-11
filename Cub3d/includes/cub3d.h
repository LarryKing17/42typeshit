/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:50:47 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/10 15:03:20 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

# include "libft.h"
# include "get_next_line.h"

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

int	parse_color(char *line, t_rgb *color);

int	parse_map(char *line, t_config *cfg);

int		validate_map(t_config *cfg);
int		check_map_chars(t_config *cfg);
int		check_player(t_config *cfg);
int		check_map_closed(t_config *cfg);
int		check_top_bottom_walls(t_config *cfg);

// UTILS
void	free_config(t_config *cfg);
int		is_empty_line(char *s);
void	free_split(char **tab);

void ft_free_tab(char **tab);
void	error_exit(const char *msg, t_config *cfg);

#endif
