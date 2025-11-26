/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:43:33 by zvalenti          #+#    #+#             */
/*   Updated: 2024/11/21 19:23:14 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static char	*ft_read(int fd, char *buffer, char *result)
{
	int		lire;
	char	*temp;

	lire = 1;
	while (lire != '\0')
	{
		lire = read(fd, buffer, BUFFER_SIZE);
		if (lire == -1)
			return (NULL);
		else if (lire == 0)
			break ;
		buffer[lire] = '\0';
		if (!result)
		{
			result = ft_strdup("");
			return (NULL);
		}
		temp = result;
		result = ft_strjoin(temp, buffer);
		free(temp);
		if (!result)
			return (NULL);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (result);
}*/
static char	*ft_read_and_fill(char *result, char *buffer)
{
	char	*temp;

	buffer[BUFFER_SIZE] = '\0';
	if (!result)
		result = ft_strdup("");
	if (!result)
		return (NULL);
	temp = result;
	result = ft_strjoin(temp, buffer);
	free(temp);
	if (!result)
		return (NULL);
	return (result);
}

static char	*ft_read(int fd, char *buffer, char *result)
{
	int	lire;

	lire = read(fd, buffer, BUFFER_SIZE);
	while (lire > 0)
	{
		buffer[lire] = '\0';
		result = ft_read_and_fill(result, buffer);
		if (!result)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
		lire = read(fd, buffer, BUFFER_SIZE);
	}
	if (lire == -1)
		return (NULL);
	return (result);
}

static char	*ft_extraire(char *ligne)
{
	size_t	count;
	char	*result;

	count = 0;
	while (ligne[count] != '\n' && ligne[count] != '\0')
		count++;
	if (ligne[count] == '\0' || ligne[1] == '\0')
		return (NULL);
	result = ft_substr(ligne, count + 1, ft_strlen(ligne) - count);
	if (!result)
		return (NULL);
	if (*result == '\0')
	{
		free(result);
		result = NULL;
	}
	ligne[count + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	char		*ligne;
	char		*buffer;
	static char	*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ligne = ft_read(fd, buffer, result);
	free(buffer);
	if (!ligne)
	{
		free(result);
		result = NULL;
		return (NULL);
	}
	result = ft_extraire(ligne);
	return (ligne);
}
