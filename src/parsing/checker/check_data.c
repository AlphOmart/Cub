/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:24:20 by mwubneh           #+#    #+#             */
/*   Updated: 2024/02/06 13:24:20 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	bad_element(t_data *data);
static bool	bad_colors(int const f[3], int const c[3]);

/**
 * @brief check_data" checks all the elements of the structure passed as
 *			an argument. If an error is found, if the user-provided file
 *			is finished, or if an argument is missing, the program exits
 *			gracefully. Otherwise, the function ends, and the program continues.
 * @param ***file If the data from the original file, from which the information
 *			is being retrieved, is null and the map has not yet been retrieved,
 *			the program exits gracefully.
 * @param *data Structures in which the validity of all elements is checked.
 * @return The program terminates if the function finds an error; otherwise,
 *			the function ends, and the program continues.
 */
void	check_data(char ***file, t_data *data)
{
	size_t	i;

	i = 0;
	if (errno == 4 || !bad_element(data) || (*file)[i] == NULL)
	{
		i = 0;
		while ((*file)[i] != NULL)
		{
			if (i < 4 && data->element[i] != NULL)
				free(*(char **) data->element[i]);
			free((*file)[i]);
			i++;
		}
		free(*file);
		free_map(data->map);
		ft_error(RED ERROR YELLOW INV_ELEMENT NC, errno);
	}
}

/**
 * @briefChecks	the validity of the given RGB elements.
 * @param f An array of integers where each element represents an RGB
 *			code number.
 * @param c An array of integers where each element represents an RGB
 *			code number.
 * @return If an error is found, the program returns false; otherwise,
 *			it returns true.
 */
static bool	bad_colors(int const f[3], int const c[3])
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if (f[i] < 0 || c[i] < 0 || 255 < f[i] || 255 < c[i])
			return (false);
		++i;
	}
	return (true);
}

/**
 * @brief	Verify that all the elements of data have been parsed correctly.
 * @param data Structure whose elements need to be parsed.
 * @return If an error is found, the program returns false; otherwise,
 *			it returns true.
 */
static bool	bad_element(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (*(char **) data->element[i] == NULL)
			return (false);
	}
	if (!bad_colors(data->element[4], data->element[5]))
		return (false);
	return (true);
}

void	free_map(char **cpy)
{
	size_t	i;

	i = 0;
	while (cpy[i])
		free(cpy[i++]);
	free(cpy);
}
