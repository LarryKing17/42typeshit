/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:07:44 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 18:20:08 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_texture_path(char *path)
{
	int	len;

	if (!path || !*path)
		return (0);
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

static char	**get_texture_target(char *line, t_scene *s)
{
	if (!ft_strncmp(line, "NO", 2))
		return (&s->tex.no);
	if (!ft_strncmp(line, "SO", 2))
		return (&s->tex.so);
	if (!ft_strncmp(line, "WE", 2))
		return (&s->tex.we);
	if (!ft_strncmp(line, "EA", 2))
		return (&s->tex.ea);
	return (NULL);
}

static void	trim_line_end(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (i > 0 && ft_strchr(" \t\n\r", line[i - 1]))
		line[--i] = '\0';
}

int	parse_texture(char *line, t_scene *s)
{
	char	**target;
	char	*path;

	line = skip_spaces(line);
	target = get_texture_target(line, s);
	if (!target)
		return (0);
	if (*target != NULL)
		return (0);
	line += 2;
	line = skip_spaces(line);
	trim_line_end(line);
	if (*line == '\0' || !is_valid_texture_path(line))
		return (0);
	path = ft_strdup(line);
	if (!path)
		return (0);
	*target = path;
	return (1);
}
