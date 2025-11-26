/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:19:31 by zvalenti          #+#    #+#             */
/*   Updated: 2025/11/26 16:42:16 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_texture(char *line, char **texture_path)
{
	char **split;

	if (*texture_path != NULL)
		return (printf("Error\nTexture already defined\n"), 1);

	split = ft_split(line, ' ');
	if (!split)
		return (printf("Error\nMalloc failed\n"), 1);
	if(!split[0] || !split[1] || split[2] != NULL)
	{
		printf("Error\nInvalid texture line: %s\n", line);
		ft_free_tab(split);
		return (1);
	}
	*texture_path = ft_strdup(split[1])
	if(!(*texture_path))
	{
		ft_free_tab(split);
		return (printf("Error\nMalloc failed\n"), 1);
	}

	ft_free_tab(split);
	return (0);
	
}