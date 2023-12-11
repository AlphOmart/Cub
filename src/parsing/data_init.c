/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:56:38 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/04 14:42:42 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	element_init(void *element[6], t_data *data);

/**
 * @brief The function stores the number of lines
 * 		read plus 1 at the address `file_size` and then terminates.
 * @param *data address of parameter whose elements need to be initialized
 * @return The program exits after the elements of the structure
 * 			located at the address passed as a parameter have been initialized.
 */
void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	while (i++ < 3)
	{
		data->f[i] = -1;
		data->c[i] = -1;
	}
	element_init(data->element, data);
}

/**
 * @brief Initialize an array of addresses (*element[6])
 *			to make the assignment of data elements more flexible.
 * @param *data structures whose elements need to be
 *				assigned to the array of addresses
 */
static void	element_init(void *element[6], t_data *data)
{
	(element)[0] = &data->no;
	(element)[1] = &data->so;
	(element)[2] = &data->we;
	(element)[3] = &data->ea;
	(element)[4] = &data->f;
	(element)[5] = &data->c;
}
