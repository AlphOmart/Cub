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

void	draw_player(t_data data)
{
	int	i;
	int j;
	int z;

	i = 0;
	z = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			data.addr[((int)data.player.pos_x + i) * WIN_WIDTH + ((int)data.player.pos_y + j)] = 0xFFD50000; // Rouge
			++j;
		}
		++i;
	}
	while (z <= 10)
	{
		data.addr[((int)data.player.pos_x + i / 2 + (int)data.player.pdx * z) * WIN_WIDTH + ((int)data.player.pos_y + j / 2 + (int)data.player.pdy * z)] = 0xFFD50000; // Rouge
		++z;
	}
}

int handle_key_press(int keycode, t_mlx *mlx)
{

	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
	{
		mlx->data.player.pos_x += mlx->data.player.pdx;
		mlx->data.player.pos_y += mlx->data.player.pdy;
	}
	else if (keycode == XK_s)
	{
		mlx->data.player.pos_x -= mlx->data.player.pdx;
		mlx->data.player.pos_y -= mlx->data.player.pdy;
	}
	else if (keycode == XK_a)
	{
		mlx->data.player.pa += 0.1;
		if (mlx->data.player.pa < 0)
			mlx->data.player.pa += 2 * PI;
		mlx->data.player.pdx = cos(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sin (mlx->data.player.pa) * 5;
	}
	else if (keycode == XK_d)
	{
		mlx->data.player.pa -= 0.1;
		if (mlx->data.player.pa > 2 * PI)
			mlx->data.player.pa -= 2 * PI;
		mlx->data.player.pdx = cos(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sin (mlx->data.player.pa) * 5;
	}
	print(mlx);
	return (0);
}
