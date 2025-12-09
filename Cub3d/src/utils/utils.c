/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:22 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/09 15:09:52 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                            UTILS : is_empty_line                           */
/* ************************************************************************** */

/*
** Retourne 1 si la ligne ne contient que des espaces ou est vide.
*/
int	is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (s[i] == '\0');
}

/* ************************************************************************** */
/*                          UTILS : free_split                                */
/* ************************************************************************** */

/*
** Libère un tableau obtenu via ft_split.
*/
void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* ************************************************************************** */
/*                              UTILS : free_cub                              */
/* ************************************************************************** */

/*
** Libère proprement toutes les allocations du parsing.
**
** - textures (NO, SO, WE, EA)
** - map.grid (tableau 2D)
*/
void	free_cub(t_cub *cub)
{
	int	i;

	/* Textures */
	free(cub->textures.no);
	free(cub->textures.so);
	free(cub->textures.we);
	free(cub->textures.ea);

	/* Map */
	if (cub->map.grid)
	{
		i = 0;
		while (cub->map.grid[i])
		{
			free(cub->map.grid[i]);
			i++;
		}
		free(cub->map.grid);
	}
}
