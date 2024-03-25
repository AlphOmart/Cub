/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:15:48 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 17:12:26 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	press_w(double tmp_x, double tmp_y, t_mlx *mlx)
{
	tmp_x = (int)(mlx->data.player.pos_x + (mlx->data.player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->data.player.pos_y + (mlx->data.player.pdy * 2)) >> 6;
	if (map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->data.player.pos_x += mlx->data.player.pdx * 2;
	mlx->data.player.pos_y += mlx->data.player.pdy * 2;
}

void	press_s(double tmp_x, double tmp_y, t_mlx *mlx)
{
	tmp_x = (int)(mlx->data.player.pos_x - (mlx->data.player.pdx * 2)) >> 6;
	tmp_y = (int)(mlx->data.player.pos_y - (mlx->data.player.pdy * 2)) >> 6;
	if (map[(int)tmp_y][(int)tmp_x] == '1')
		return ;
	mlx->data.player.pos_x -= mlx->data.player.pdx * 2;
	mlx->data.player.pos_y -= mlx->data.player.pdy * 2;
}

void	press_a(t_mlx *mlx)
{
	mlx->data.player.pa -= 0.1;
	if (mlx->data.player.pa < 0)
		mlx->data.player.pa += (2 * M_PI);
	mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
	mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
}

void	press_d(t_mlx *mlx)
{
	mlx->data.player.pa += 0.1;
	if (mlx->data.player.pa > 2 * M_PI)
		mlx->data.player.pa -= (2 * M_PI);
	mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
	mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
}

int	handle_key_press(int keycode, t_mlx *mlx)
{
	double		tmp_x;
	double		tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
		press_w(tmp_x, tmp_y, mlx);
	else if (keycode == XK_s)
		press_s(tmp_x, tmp_y, mlx);
	else if (keycode == XK_a)
		press_a(mlx);
	else if (keycode == XK_d)
		press_d(mlx);
	return (0);
}
