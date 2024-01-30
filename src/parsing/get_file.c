/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:34:07 by mwubneh           #+#    #+#             */
/*   Updated: 2024/01/30 14:47:58 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	valid_path(char *path, int *fd);
static void	get_file_size(size_t *file_size, char *path);

/**
 * @brief In the first step, "get_file" calculates the size of
 *		the ".cub" file (provided by the "path" parameter).
 *		Then, it allocates the necessary memory for the "files" parameter
 *		to store all the data within it.
 *		The calculation of the size and the storage of data are performed
 *		using "get_next_line()."
 * @param path representation of the path provided
 *				by the user to access the .cub file
 * @param files is the variable where all the data to be parsed
 				from the ".cub" file will be stored.
 *				Its memory is allocated within this function,
 *				and the data is stored in it.
 * @return This function uses ft_error in case a problem is detected during
 *			the memory allocation for files, or if the copying of the ".cub" file
 *			into files did not occur correctly. Otherwise, the data is stored at
 *			the address of files, and the function completes.
 */
void	get_file(char *path, char ***file)
{
	size_t	file_size;
	size_t	i;
	int		fd;

	get_file_size(&file_size, path);
	valid_path(path, &fd);
	*file = malloc(sizeof(char *) * file_size);
	if (!(*file))
		ft_error(RED ERROR YELLOW MALL_ERR"in get_file.c, line 44 "NC, 4);
	i = 0;
	while (42)
	{
		(*file)[i] = get_next_line(fd);
		if ((*file)[i] == NULL)
			break ;
		i++;
	}
	if (i != file_size - 1)
		ft_error(RED ERROR YELLOW FILE_READ_ERR NC, 4);
}

/**
 * @brief This function is used to verify if the path
 *		provided as a parameter is valid, ensuring that
 *		it corresponds to a file that is openable,
 *		readable, and not a directory.
 * @param path representation of the path provided
 *				by the user to access the .cub file
 * @param fd Address of the variable where the file descriptor
 *			from open(path) will be stored.
 * @return The function terminates the program's execution
 *			with ft_error if the path corresponds to a directory or
 *			if the file opening doesn't occur correctly. Otherwise, it completes,
 * 			and the file descriptor is stored at the address of fd.
 */
static void	valid_path(char *path, int *fd)
{
	*fd = open(path, O_DIRECTORY);
	if (*fd != -1)
		ft_error(RED ERROR YELLOW NOT_FILE NC, 2);
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		ft_error(RED ERROR YELLOW INV_PATH NC, 2);
}

/**
 * @brief TThis function is used to determine the size
 *		(number of lines in the file) to allocate
 *		the necessary memory for files. get_next_line is used to determine
 *		the number of lines in the file. Then, the file descriptor stored
 *		at the address of fd is closed.
 * @param file_size The number of lines read by `get_next_line` plus 1 is
 *				a variable that will be used for memory allocation in a
 *				subsequent step of the function.
 *	@param path path to the .cub file provided
 * @return The function stores the number of lines (+1) at the address file_size
 * 			and then terminates.
 */
static void	get_file_size(size_t *file_size, char *path)
{
	char	*line;
	int		fd;

	valid_path(path, &fd);
	*file_size = 0;
	while (42)
	{
		++(*file_size);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
}
