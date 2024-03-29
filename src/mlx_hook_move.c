/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:33:06 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 16:33:39 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	press_w(double tmp_x, double tmp_y, t_mlx *mlx)
{
	tmp_x = (int)(mlx->player.pos_x + (mlx->player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->player.pos_y + (mlx->player.pdy * 2)) >> 6;
	if (mlx->player.map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->player.pos_x += mlx->player.pdx * 2;
	mlx->player.pos_y += mlx->player.pdy * 2;
}

void	press_s(double tmp_x, double tmp_y, t_mlx *mlx)
{
	tmp_x = (int)(mlx->player.pos_x - (mlx->player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->player.pos_y - (mlx->player.pdy * 2)) >> 6;
	if (mlx->player.map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->player.pos_x -= mlx->player.pdx * 2;
	mlx->player.pos_y -= mlx->player.pdy * 2;
}

void	press_d(double tmp_x, double tmp_y, t_mlx *mlx)
{
	mlx->player.pdx = cosf(mlx->player.pa + (M_PI / 2)) * 5;
	mlx->player.pdy = sinf(mlx->player.pa +(M_PI / 2)) * 5;
	tmp_x = (int)(mlx->player.pos_x + (mlx->player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->player.pos_y + (mlx->player.pdy * 2)) >> 6;
	if (mlx->player.map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->player.pos_x += mlx->player.pdx * 2;
	mlx->player.pos_y += mlx->player.pdy * 2;
	mlx->player.pdx = cosf(mlx->player.pa) * 5;
	mlx->player.pdy = sinf(mlx->player.pa) * 5;
}

void	press_a(double tmp_x, double tmp_y, t_mlx *mlx)
{
	mlx->player.pdx = cosf(mlx->player.pa + (M_PI / 2)) * 5;
	mlx->player.pdy = sinf(mlx->player.pa +(M_PI / 2)) * 5;
	tmp_x = (int)(mlx->player.pos_x - (mlx->player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->player.pos_y - (mlx->player.pdy * 2)) >> 6;
	if (mlx->player.map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->player.pos_x -= mlx->player.pdx * 2;
	mlx->player.pos_y -= mlx->player.pdy * 2;
	mlx->player.pdx = cosf(mlx->player.pa) * 5;
	mlx->player.pdy = sinf(mlx->player.pa) * 5;
}
