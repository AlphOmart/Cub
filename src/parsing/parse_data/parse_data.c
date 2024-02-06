/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:59:43 by mwubneh           #+#    #+#             */
/*   Updated: 2024/02/06 13:58:22 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_info(char *str, t_data *data, char ***file, int n);
void		check_map(t_data *data);

/**
 * @briefChecks	This function is used to send the elements from file
 *			that need to be parsed into get_info, while removing any
 *			leading whitespace. Then, it checks the validity of these
 *			elements and finally retrieves the map from file.
 * @param ***file Corresponds to the data in the file provided by the user,
 *			from which the elements need to be parsed into data.
 * @param *data The address of the structure where the elements from
 *			`file` need to be parsed.
 * @return I"The program exits gracefully if an error is found; otherwise,
 *			the function ends, and the program continues."
 */
void	parse_data(char ***file, t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*file)[i] != NULL && errno != 4)
	{
		j = 0;
		while ((*file)[i][j] != '\0')
		{
			while (ft_isspace((*file)[i][j]))
				j++;
			if ((*file)[i][j])
			{
				get_info(&(*file)[i][j], data, file, i);
				break ;
			}
		}
		i++;
	}
	check_map(data);
	check_data(file, data);
}

/**
 * @brief "This function stores the information directly in the structure
 *			data's variables, using their addresses as references."
 * @param *str "The string that needs to be parsed into data."
 * @param *data "Structures that accommodate the parsed elements."
 * @return "The function stops once the given element has been parsed
 *		or when no corresponding match has been found, and the program continues."
 */
void	get_info(char *str, t_data *data, char ***file, int n)
{
	const char	*info[7] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
	size_t		i;

	i = 0;
	while (info[i] != NULL && errno != 4)
	{
		if (i < 4 && !ft_strncmp(str, info[i], 2))
			return (parse_textures(data->element[i], &str[2]),
				is_valid_path(data->element[i]),
				data->map = &(*file)[n], (void) NULL);
		else if (4 <= i && !ft_strncmp(str, info[i], 2))
			return (get_colors(data->element[i], &str[2]),
				data->map = &(*file)[n], (void) NULL);
		i++;
	}
}

void	get_pos(char **cpy, int start[2])
{
	size_t	x;
	size_t	y;

	y = 0;
	while (cpy[y])
	{
		x = 0;
		while (cpy[y][x])
		{
			if (cpy[y][x] == 'N' || cpy[y][x] == 'S'
					|| cpy[y][x] == 'W' || cpy[y][x] == 'E')
			{
				start[0] = y;
				start[1] = x;
				return ;
			}
			++x;
		}
		++y;
	}
	errno = 4;
}
