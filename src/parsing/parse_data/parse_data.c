/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:59:43 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/21 14:10:28 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_data(char ***file, t_data *data);
static void	get_info(char *str, t_data *data, char ***file, int n);

void	map_cpy(char **map, char ***cpy)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i] != NULL)
		++i;
	*cpy = malloc(sizeof(char *) * (i + 1));
	if (!(*cpy))
		exit(-1);
	j = -1;
	while (++j < i)
		(*cpy)[j] = ft_strdup(map[j]);
	(*cpy)[i] = NULL;
}

bool	is_close(char **cpy)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cpy[i] && ft_strlen(cpy[i]) == 1 && ft_isspace(cpy[i][0]))
		i++;
	while (cpy[i])
	{
		j = 0;
		while (cpy[i][j])
		{
			if (ft_strlen(cpy[i]) == 1 && ft_isspace(cpy[i][0]))
				break ;
			cpy[i][j] = x
			j++;
		}
		printf("%s\n", cpy[i]);
		i++;
	}
	return (true);
}

void	check_map(char **map)
{
	size_t	i;
	char	**cpy;

	map_cpy(map, &cpy);
	if (!is_close(cpy))
		exit(-15);
	i = 0;
	while (cpy[i])
		free(cpy[i++]);
	free(cpy);
}

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
	check_data(file, data);
	check_map(data->map);
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
bool	bad_colors(int const f[3], int const c[3])
{
	size_t	i;

	i = -1;
	while (++i < 3)
	{
		if (f[i] < 0 || c[i] < 0 || 255 < f[i] || 255 < c[i])
			return (false);
	}
	return (true);
}
/**
 * @brief	Verify that all the elements of data have been parsed correctly.
 * @param data Structure whose elements need to be parsed.
 * @return If an error is found, the program returns false; otherwise,
 *			it returns true.
 */
bool	bad_element(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (*(char **) data->element[i] == NULL)
			return (false);
	}
	if (!bad_colors(data->element[4], data->element[5]))
		return (false);
	return (true);
}
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
static void	check_data(char ***file, t_data *data)
{
	size_t	i;

	i = 0;

	if (errno == 4 || !bad_element(data) || (*file)[i] == NULL)
	{
		i = -1;
		while ((*file)[++i] != NULL)
		{
			if (i < 4 && data->element[i] != NULL)
				free(*(char **) data->element[i]);
			free((*file)[i]);
		}
		free(*file);
		ft_error(RED ERROR YELLOW INV_ELEMENT NC, errno);
	}
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
	const char	*info[7] = {"NO ", "SO ", "WE ", "EA ", "F", "C", NULL};
	size_t		i;

	i = -1;
	while (info[++i] != NULL && errno != 4)
	{
		if (i < 4 && !ft_strncmp(str, info[i], 2))
			return (parse_textures(data->element[i], &str[2]),
				is_valid_path(data->element[i]), data->map = &(*file)[n], (void)NULL);
		else if (4 <= i && !ft_strncmp(str, info[i], 1))
			return (get_colors(data->element[i], trim_end(&str[1])), data->map = &(*file)[n], (void)NULL);
	}
}
