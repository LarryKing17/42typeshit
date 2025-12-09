/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:15:29 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/08 15:44:54 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_file(char *path, t_config *cfg)
{
	int	fd;
	char *line;
	int map_started = 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_exit("Cannot open .cub file", cfg), 1);

	while ((line = get_next_line(fd)))
	{
		char *trim = ft_strtrim(line, "\n");
		free(line);

		if (!trim)
			return (error_exit("Malloc failed", cfg), close(fd), 1);
		if (trim[0] == '\0' && map_started == 0)
		{
			free(trim);
			continue;
		}

		if (parse_line(trim, cfg, &map_started) != 0)
		{
			free(trim);
			return (close(fd), 1);
		}

		free(trim);
	}
	close(fd);
	if (validate_map(cfg) != 0)
		return (1);
	return (0);
}

