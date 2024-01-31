/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:08:51 by mwubneh           #+#    #+#             */
/*   Updated: 2024/01/30 20:04:27 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function retrieves the content of to_get (a string) and inserts
 *		it into to_put (the address of a string), while removing any trailing
 *		unwanted whitespace if present.
 * @param **to_put The address where the trimmed variable should be stored
 * 			for reuse.
 * @param *to_get The variable that needs to be trimmed and stored in to_put.
 * @return Once the variable is stored in to_put, the function stops, and to_put
 *			will be reused later in the program.
 */
void	parse_textures(char **to_put, char *to_get)
{
	size_t	i;

	i = 0;
	while (to_get[i] && ft_isspace(to_get[i]))
		i++;
	if (*to_put != NULL)
		errno = 4;
	*to_put = ft_strjoin(*to_put, trim_end(&to_get[i]));
}

/**
 * @brief The purpose of this function is to check if the path provided
 *			as a parameter is valid for the proper functioning of the program.
 * @param **path The address of the variable whose validity needs to be verified.
 * @return The function assigns 4 to the errno variable if the parameter provided
 *			is not valid. Otherwise, it leaves errno at its current value,
 *			and the program continues.
 */
void	is_valid_path(char **path)
{
	size_t	i;

	i = 0;
	while ((*path) && (*path)[i] && ft_isspace((*path)[i]))
		i++;
	//(*path) = trim_end(*path);
	 if ((*path) && !ft_strncmp(path[i], "./", 2))
	 	i += 2;
	while ((*path) && (*path)[i])
	{
		if (ft_isspace((*path)[i]) &&
			((*path)[i - 1] != '\\' || ft_isspace((*path)[i - 1])))
			errno = 4;
		i++;
	}
}

/**
 * @brief Removes all the whitespace from the string passed as a parameter.
 * @param **string String from which trailing whitespace needs to be removed.
 * @return Returns the trimmed string.
 */
char	*trim_end(char *string)
{
	size_t	i;

	i = ft_strlen(string);
	i--;
	if (string[i] && ft_isspace(string[i]))
	{
		while (i > 0 && ft_isspace(string[i]))
			i--;
		string[i + 1] = '\0';
	}
	return (string);
}