/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:09:12 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 18:03:10 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_player_char(t_scene *s, int y, int x, int *found)
{
	char	c;

	c = s->map.grid[y][x];
	if (!ft_strchr("NSEW", c))
		return (0);
	if (*found)
		exit_error(s, NULL, "Multiple players");
	*found = 1;
	s->px = x + 0.5;
	s->py = y + 0.5;
	s->dx = (c == 'E') - (c == 'W');
	s->dy = (c == 'S') - (c == 'N');
	s->map.grid[y][x] = '0';
	return (1);
}

void	find_player(t_scene *s)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = -1;
	while (++y < s->map.height)
	{
		x = -1;
		while (s->map.grid[y][++x])
			if (ft_strchr("NSEW", s->map.grid[y][x]))
				if (process_player_char(s, y, x, &found))
					;
	}
	if (!found)
		exit_error(s, NULL, "No player");
}

static int	is_void(t_scene *s, int x, int y)
{
	if (y < 0 || y >= s->map.height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(s->map.grid[y]))
		return (1);
	return (0);
}

static int	is_player_or_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_closed(t_scene *s)
{
	int	x;
	int	y;

	y = 0;
	while (y < s->map.height)
	{
		x = 0;
		while (s->map.grid[y][x])
		{
			if (is_player_or_floor(s->map.grid[y][x]))
			{
				if (is_void(s, x + 1, y) || is_void(s, x - 1, y) || is_void(s,
						x, y + 1) || is_void(s, x, y - 1))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
