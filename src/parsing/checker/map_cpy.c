/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:24:20 by mwubneh           #+#    #+#             */
/*   Updated: 2024/02/06 13:24:20 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cub3d.h"

static void	get_hi_size(size_t *hi_size, size_t *i, size_t j, char **map);
static char	*line_copy(char *str, size_t n);

void	map_cpy(char **map, char ***cpy)
{
	size_t	i;
	size_t	j;
	size_t	hi_size;

	i = 0;
	j = 0;
	hi_size = 0;
	while (map[j] && !ft_strncmp(map[j], "\n", 2))
		j++;
	get_hi_size(&hi_size, &i, j, map);
	*cpy = malloc(sizeof(char *) * (i + 1));
	if (!(*cpy))
		return (errno = 4, (void) NULL);
	i = 0;
	while (map[i + j])
	{
		(*cpy)[i] = line_copy(map[i + j], hi_size);
		i++;
	}
	(*cpy)[i] = NULL;
}

static char	*line_copy(char *str, size_t n)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	tmp = calloc (sizeof(char), (n + 1));
	if (!tmp)
	{
		errno = 4;
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		if (i < len && str[i] != '\0' && str[i] != '\n')
			tmp[i] = str[i];
		else
			tmp[i] = ' ';
		i++;
	}
	tmp[i - 1] = '\n';
	return (tmp);
}

static void	get_hi_size(size_t *hi_size, size_t *i, size_t j, char **map)
{
	size_t	temp;

	temp = 0;
	while (map[*i + j])
	{
		(temp) = ft_strlen(map[*i + j]);
		if (temp > *hi_size)
			*hi_size = temp;
		(*i)++;
	}
}
