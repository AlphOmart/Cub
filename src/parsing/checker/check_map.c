/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:24:20 by mwubneh           #+#    #+#             */
/*   Updated: 2024/02/06 14:01:30 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_elements(char **cpy);

void	check_map(t_data *data)
{
	char	**cpy;

	cpy = NULL;
	if (!data->map || !data->map[1])
		return (data->map = NULL, errno = 4, (void) NULL);
	map_cpy(&data->map[1], &cpy);
	check_elements(cpy);
	map_cpy(cpy, &(data->map));
	if (!is_close(cpy))
		return (free_map(cpy));
	free_map(cpy);
}

bool	is_valid(char *cpy)
{
	static int	pos_nbr = 0;
	size_t		j;

	j = 0;
	while (cpy[j] && j < ft_strlen(cpy) - 1)
	{
		if (ft_isspace(cpy[j]) && cpy[j] != '\n')
			;
		else if (cpy[j] != '0' && cpy[j] != '1')
		{
			if ((cpy[j] == 'N' || cpy[j] == 'S'
					|| cpy[j] == 'W' || cpy[j] == 'E') && pos_nbr == 0)
				pos_nbr += 1;
			else
			{
				errno = 4;
				return (false);
			}
		}
		j++;
	}
	return (true);
}

static void	check_elements(char **cpy)
{
	size_t	i;

	i = 0;
	while (cpy[i])
	{
		is_valid(cpy[i]);
		i++;
	}
}

bool	is_block(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'Z' && !ft_isspace(map[i][j]))
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}
