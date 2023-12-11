/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:59:14 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/06 20:11:29 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_split_size(char **temp);

/**
 * @brief "This function splits `to_get`, checks that it returns a
 *		string array of size 3, then applies the `atoi` function
 *		to each of the elements and stores them in an integer array."
 * @param colors[3]"An integer array where the elements of `to_get`
 *			will be parsed."
 * @param *to_get "The string that will be split, on which `atoi`
 *			will be applied, and then stored in `colors`."
 */
void	get_colors(int colors[3], char *to_get)
{
	char	**temp;
	size_t	i;

	i = 0;
	while (to_get[i] && ft_isspace(to_get[i]))
		i++;
	temp = ft_split(&to_get[i], ',');
	if (get_split_size(temp) != 3)
	{
		errno = 4;
		return ;
	}
	i = 0;
	while (temp[i])
	{
		colors[i] = ft_atoi(temp[i]);
		i++;
	}
	i = 0;
	while (temp[i] != NULL)
		free(temp[i++]);
	free(temp);
}

/**
 * @brief Calculate the size of a char ** variable passed as a parameter.
 * @param **temp Array of strings whose size needs to be calculated.
 * @return Returns the size of the string
 */
static size_t	get_split_size(char **temp)
{
	size_t	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}