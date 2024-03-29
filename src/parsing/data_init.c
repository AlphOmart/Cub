/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:56:38 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 11:55:16 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	element_init(void *element[6], t_data *data);
static void	mlx_data_init(t_mlx *mlx);

/**
 * @brief The function stores the number of lines
 * 		read plus 1 at the address `file_size` and then terminates.
 * @param *data address of parameter whose elements need to be initialized
 * @return The program exits after the elements of the structure
 * 			located at the address passed as a parameter have been initialized.
 */
void	data_init(t_data *data, t_mlx *mlx)
{
	int	i;

	i = -1;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	while (++i < 3)
	{
		data->f[i] = -1;
		data->c[i] = -1;
	}
	data->map = NULL;
	element_init(data->element, data);
	mlx_data_init(mlx);
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

static void	mlx_data_init(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win = NULL;
	mlx->game_ptr = NULL;
	mlx->no.img = NULL;
	mlx->no.width = 0;
	mlx->no.height = 0;
	mlx->so.img = NULL;
	mlx->so.width = 0;
	mlx->so.height = 0;
	mlx->we.img = NULL;
	mlx->we.width = 0;
	mlx->we.height = 0;
	mlx->ea.img = NULL;
	mlx->ea.width = 0;
	mlx->ea.height = 0;
}
