/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:05:02 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 13:09:05 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief This function is used to display an error message and
 * 			exit the program gracefully by assigning "errno" to "err" and
 * 			printing "str" to the standard error output.
 * @param str string of characters to be displayed on the error output
 * @param err Parameter that will be used to assign
 * 				the program's exit value to errno.
 * @return program exit with exit
 */
void	ft_error(char *str, int err)
{
	errno = err;
	perror(str);
	exit(err);
}

void	ft_free_data(t_data *data, int i)
{
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	if (i != 0)
		free_map(data->map);
}

double	get_start_angle(char c)
{
	if (c == 'N')
		return (270);
	else if (c == 'W')
		return (180);
	else if (c == 'S')
		return (90);
	else if (c == 'E')
		return (0);
	return (0);
}

void	init_player(t_mlx *mlx, t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	get_pos(data->map, fd);
	mlx->player.pos_x = (fd[1] * CELL_SIZE) + 0.5 * CELL_SIZE;
	mlx->player.pos_y = ((fd[0] + 0.5) * CELL_SIZE);
	mlx->player.pa = (get_start_angle(data->map[fd[0]][fd[1]]) * M_PI) / 180;
	mlx->player.pdx = cos(mlx->player.pa);
	mlx->player.pdy = sin(mlx->player.pa);
	mlx->player.fov = 60;
	mlx->player.high_map = data->high_map;
	mlx->player.width_map = data->width_map;
	mlx->player.map = data->map;
}
