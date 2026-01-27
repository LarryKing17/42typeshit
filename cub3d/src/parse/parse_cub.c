/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:09:52 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 17:51:11 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_line(char *line)
{
	if ((!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || line[2] == '\t'))
		|| (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || line[2] == '\t')))
		return (1);
	return (0);
}

static int	handle_header_line(char *line, t_scene *s, char **lines)
{
	if (is_texture_line(line))
	{
		if (!parse_texture(line, s))
			exit_error(s, lines, "Invalid texture line or duplicate texture");
		return (1);
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		if (!parse_color(line, &s->floor))
			exit_error(s, lines, "Invalid floor color");
		return (1);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (!parse_color(line, &s->ceil))
			exit_error(s, lines, "Invalid ceiling color");
		return (1);
	}
	return (0);
}

static int	parse_header(char **lines, t_scene *s, int *idx)
{
	int		i;
	char	*line;

	i = *idx;
	while (lines[i])
	{
		line = skip_spaces(lines[i]);
		if (!*line)
		{
			i++;
			continue ;
		}
		if (handle_header_line(line, s, lines))
			;
		else if (is_map_line(lines[i]))
			break ;
		else
			exit_error(s, lines, "Invalid line in file");
		i++;
	}
	*idx = i;
	return (1);
}

static void	process_map_tail(char **lines, int idx, t_scene *s)
{
	while (lines[idx])
	{
		if (!is_empty_line(lines[idx]))
			exit_error(s, lines, "Invalid content after map");
		idx++;
	}
}

int	parse_cub(char *path, t_scene *s)
{
	char	**lines;
	int		idx;

	s->floor.value = -1;
	s->ceil.value = -1;
	if (!check_file_extension(path))
		exit_error(s, NULL, "Invalid file extension");
	lines = read_file(path);
	if (!lines)
		exit_error(s, NULL, "Cannot open file");
	idx = 0;
	parse_header(lines, s, &idx);
	if (!s->tex.no || !s->tex.so || !s->tex.we || !s->tex.ea
		|| s->floor.value == -1 || s->ceil.value == -1)
		exit_error(s, lines, "Missing elements in .cub file");
	idx = parse_map(lines, idx, s);
	process_map_tail(lines, idx, s);
	find_player(s);
	if (!check_closed(s))
		exit_error(s, lines, "Map not closed");
	free_strtab(lines);
	return (1);
}
