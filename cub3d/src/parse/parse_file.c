/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:06:55 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/26 17:53:11 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

int	check_file_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strncmp(path + len - 4, ".cub", 4));
}

char	**read_file(char *path)
{
	int		fd;
	char	*line;
	char	*all;
	char	*tmp;
	char	**res;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	all = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = all;
		all = ft_strjoin(all, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	res = ft_split(all, '\n');
	free(all);
	return (res);
}
