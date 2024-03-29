/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:15:48 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 16:42:27 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	press_right(t_mlx *mlx);
void	press_left(t_mlx *mlx);

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
	else if (keycode == XK_d)
		press_d(tmp_x, tmp_y, mlx);
	else if (keycode == XK_a)
		press_a(tmp_x, tmp_y, mlx);
	else if (keycode == XK_Left)
		press_left(mlx);
	else if (keycode == XK_Right)
		press_right(mlx);
	return (0);
}

void	press_left(t_mlx *mlx)
{
	mlx->player.pa -= 0.1;
	if (mlx->player.pa < 0)
		mlx->player.pa += (2 * M_PI);
	mlx->player.pdx = cosf(mlx->player.pa) * 5;
	mlx->player.pdy = sinf(mlx->player.pa) * 5;
}

void	press_right(t_mlx *mlx)
{
	mlx->player.pa += 0.1;
	if (mlx->player.pa > 2 * M_PI)
		mlx->player.pa -= (2 * M_PI);
	mlx->player.pdx = cosf(mlx->player.pa) * 5;
	mlx->player.pdy = sinf(mlx->player.pa) * 5;
}
