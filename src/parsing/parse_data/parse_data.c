/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:59:43 by mwubneh           #+#    #+#             */
/*   Updated: 2024/01/30 20:35:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_data(char ***file, t_data *data);
static void	get_info(char *str, t_data *data, char ***file, int n);
void	check_map(t_data* data);

char	*line_copy(char *str, size_t n)
{
	char	*tmp;
	size_t	i;
	size_t len = ft_strlen(str);

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

void	map_cpy(char **map, char ***cpy)
{
	size_t	i;
	size_t	j;
	size_t hi_size;
	size_t	temp;

	i = 0;
	j = 0;
	hi_size = 0;
	while (map[j] && !ft_strncmp(map[j], "\n", 2))
		j++;
	while (map[i + j])
	{
		temp =  ft_strlen(map[i + j]);
		if (temp > hi_size)
			hi_size = temp;
		i++;
	}
	*cpy = malloc(sizeof(char *) * (i + 1));
	if (!(*cpy))
		return (errno = 4, (void)NULL);
	i = 0;
	while (map[i + j])
	{
		(*cpy)[i] = line_copy(map[i + j], hi_size);
		i++;
	}
	(*cpy)[i] = NULL;
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
			if (cpy[y][x] == 'N' || cpy[y][x] == 'S' || cpy[y][x] == 'W' || cpy[y][x] == 'E')
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
//TODO : /N in map
void expension(char **map, int x, int y)
{
	if (map[y] && map[y][x] && (map[y][x] == '1' || map[y][x] == 'X'))
		return ;
	else if (map[y][x] == 32 || map[y][x] == '\n')
	{
		errno = 4;
		return ;
	}
	map[y][x] = 'X';
	if (map[y] && map[y][x + 1])
		expension(map, x + 1, y);
	if (map[y + 1])
		expension(map, x, y + 1);
	if (map[y] && x - 1>= 0 && map[y][x - 1])
		expension(map, x - 1, y);
	if (y - 1 >= 0 && map[y - 1])
		expension(map, x, y - 1);
}

bool	close_up(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'X')
			return false;
		i++;
	}
	return (true);
}
bool	close_down(char **cpy) {
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cpy[i])
		i++;
	i -= 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] == 'X')
			return (false);
		j++;
	}
	return true;
}

bool	close_left(char **cpy)
{
	size_t	j;

	j = 0;
	while (cpy[j])
	{
		if (cpy[j][0] == 'X')
			return (false);
		j++;
	}
	return (true);
}

bool	close_right(char **cpy)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cpy[i])
	{
		j = ft_strlen(cpy[i]);
		while (j >= 0 && cpy[i] && cpy[i][j] && cpy[i][j] != 1)
		{
			if (cpy[i][j] == 'X')
				return (false);
			j--;
		}
		i++;
	}
	return (true);
}

void	expension_1(char **map, int x, int y)
{
	if (map[y] && map[y][x] && (map[y][x] == 'Z' || map[y][x] == 32 || map[y][x] == '\n'))
		return ;
	map[y][x] = 'Z';
	if (map[y] && map[y][x + 1])
		expension_1(map, x + 1, y);
	if (map[y + 1])
		expension_1(map, x, y + 1);
	if (map[y] && x - 1>= 0 && map[y][x - 1])
		expension_1(map, x - 1, y);
	if (y - 1 >= 0 && map[y - 1])
		expension_1(map, x, y - 1);
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
bool	is_close(char **cpy)
{
	int		start[2];

	start[0] = -1;
	start[1] = -1;
	get_pos(cpy, start);
	if (start[0] == -1 || start[1] == -1)
		return (errno = 4, false);
	cpy[start[0]][start[1]] = 'x';
	expension(cpy, start[1], start[0]);
	int	i = -1;
	while(cpy[++i])
		printf("%s", cpy[i]);
	if (!close_up(cpy[0]) || !close_down(cpy) || !close_left(cpy) || !close_right(cpy))
		return (errno = 4, false);
	expension_1(cpy, start[1], start[0]);
	if(!is_block(cpy))
		return (errno = 4, false);
	return (true);
}

bool	is_valid(char *cpy)
{
	static	int pos_nbr = 0;
	size_t	j;

	j = 0;
	while (cpy[j] && j < ft_strlen(cpy) - 1)
	{
		if (ft_isspace(cpy[j]) && cpy[j] != '\n')
			;
		else if (cpy[j] != '0' && cpy[j] != '1')
		{
			if ((cpy[j] == 'N' || cpy[j] == 'S' || cpy[j] == 'W' || cpy[j] == 'E') && pos_nbr == 0)
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

void	check_elements(char **cpy)
{
	size_t	i;

	i = 0;
	while (cpy[i])
	{
		is_valid(cpy[i]);
		i++;
	}
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
	check_map(data);
	check_data(file, data);
}

void free_cpy(char **cpy)
{
	size_t	i;

	i = 0;
	while (cpy[i])
		free(cpy[i++]);
	free(cpy);
}

void	check_map(t_data* data)
{
	char	**cpy;

	cpy = NULL;
	if (!data->map || !data->map[1])
		return (data->map = NULL, errno = 4, (void)NULL);
	map_cpy(&data->map[1], &cpy);
	check_elements(cpy);
	map_cpy(cpy, &(data->map));
	if (!is_close(cpy))
		return (free_cpy(cpy));
	int i = -1;
	while (cpy[++i])
		printf("%s", cpy[i]);
	printf("\n");
	free_cpy(cpy);
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
		i = 0;
		while ((*file)[i] != NULL)
		{
			if (i < 4 && data->element[i] != NULL)
				free(*(char **) data->element[i]);
			free((*file)[i]);
			i++;
		}
		free(*file);
		i = 0;
		while (data->map && data->map[i])
			free(data->map[i++]);
		free(data->map);
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
	const char	*info[7] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
	size_t		i;

	i = 0;
	while (info[i] != NULL && errno != 4)
	{
		if (i < 4 && !ft_strncmp(str, info[i], 2))
			return (parse_textures(data->element[i], &str[2]),
				is_valid_path(data->element[i]), data->map = &(*file)[n], (void)NULL);
		else if (4 <= i && !ft_strncmp(str, info[i], 2))
			return (get_colors(data->element[i], trim_end(&str[2])), data->map = &(*file)[n], (void)NULL);
		i++;
	}
}
