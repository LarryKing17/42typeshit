/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:08:39 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 18:07:39 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_height(char **lines, int i)
{
	int	h;

	h = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		h++;
		i++;
	}
	return (h);
}

static void	free_grid_partial(char **grid, int filled)
{
	int	k;

	k = 0;
	while (k < filled)
		free(grid[k++]);
	free(grid);
}

static void	copy_map_lines(char **lines, int start, int h, t_scene *s)
{
	int	j;

	j = 0;
	while (j < h)
	{
		s->map.grid[j] = ft_strdup(lines[start + j]);
		if (!s->map.grid[j])
		{
			free_grid_partial(s->map.grid, j);
			s->map.grid = NULL;
			exit_error(s, NULL, "Malloc failed during map copy");
		}
		j++;
	}
	s->map.grid[j] = NULL;
	s->map.height = j;
}

int	parse_map(char **lines, int i, t_scene *s)
{
	int	start;
	int	h;

	start = i;
	h = get_map_height(lines, i);
	if (h == 0)
		exit_error(s, lines, "No map found");
	s->map.grid = malloc(sizeof(char *) * (h + 1));
	if (!s->map.grid)
		exit_error(s, lines, "Malloc failed");
	copy_map_lines(lines, start, h, s);
	return (start + h);
}
