/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:27:28 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 12:59:06 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_mlx(t_mlx *mlx, int n, int c);
int		close_window(t_mlx *mlx);

void	ft_exit(t_data *data, t_mlx *mlx, int n, int c)
{
	ft_free_data(data, 1);
	free_mlx(mlx, n, c);
	ft_error(RED ERROR YELLOW "invalid sprites path !\n" NC, 4);
}

int	close_window(t_mlx *mlx)
{
	free_mlx(mlx, 4, 1);
	exit(0);
}

void	free_mlx(t_mlx *mlx, int n, int c)
{
	if (n)
		mlx_destroy_image(mlx->mlx_ptr, mlx->no.img);
	if (n >= 2)
		mlx_destroy_image(mlx->mlx_ptr, mlx->so.img);
	if (n >= 3)
		mlx_destroy_image(mlx->mlx_ptr, mlx->we.img);
	if (n >= 4)
		mlx_destroy_image(mlx->mlx_ptr, mlx->ea.img);
	mlx_destroy_image(mlx->mlx_ptr, mlx->game_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	if (c != 0)
		free_map(mlx->data->map);
}
