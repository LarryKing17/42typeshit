/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:15:50 by zvalenti          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:03 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_line(char *line, t_config *cfg, int *map_started)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line, &cfg->tex.north));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line, &cfg->tex.south));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line, &cfg->tex.west));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line, &cfg->tex.east));

	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line + 2, &cfg->floor));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line + 2, &cfg->ceiling));
		
	*map_started = 1;
	return(parse_map(line, cfg));
}
