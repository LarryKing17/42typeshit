/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:05:41 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 18:20:48 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_scene_members(t_scene *s)
{
	if (!s)
		return ;
	if (s->tex.no)
		free(s->tex.no);
	if (s->tex.so)
		free(s->tex.so);
	if (s->tex.we)
		free(s->tex.we);
	if (s->tex.ea)
		free(s->tex.ea);
	if (s->map.grid)
		free_strtab(s->map.grid);
}

void	exit_error(t_scene *s, char **lines, char *msg)
{
	printf("Error\n%s\n", msg);
	if (lines)
		free_strtab(lines);
	free_scene_members(s);
	exit(1);
}

void	free_scene(t_scene *s)
{
	free_scene_members(s);
}
