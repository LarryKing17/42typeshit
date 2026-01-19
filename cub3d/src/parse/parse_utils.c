/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:05:41 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/15 18:42:43 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

int	ft_strtab_len(char **tab)
{
	int	i = 0;

	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	free_strtab(char **tab)
{
	int	i = 0;

	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int is_empty_line(char *l)
{
    if (!l)
        return 1;
    while (*l)
    {
        if (*l != ' ' && *l != '\t' && *l != '\n')
            return 0;
        l++;
    }
    return 1;
}


int is_map_line(char *l)
{
    int has_content = 0;
    int len = 0;

    if (!l)
        return 0;

    while (l[len] && l[len] != '\n')
        len++;

    // Ligne trop courte et juste un '1' ou '0' → pas map
    if (len == 1 && (l[0] == '1' || l[0] == '0'))
        return 0;

    int i = 0;
    while (l[i] && l[i] != '\n')
    {
        
        if (!ft_strchr(" 01NSEW\t", l[i])) // enlever '\n' ici, on gère avant
            return 0; // caractère invalide
        if (l[i] == '0' || ft_strchr(" 1NSEW", l[i])) // vrai contenu
            has_content = 1;
        i++;
    }

    return has_content;
}

