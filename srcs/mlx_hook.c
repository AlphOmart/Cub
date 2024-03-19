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
	double	i;
	double	j;
	int		z;

	z = 0;
	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			data.addr[(int)(data.player.pos_x + i) * mapX*mapS + ((int)(data.player.pos_y + j))] = 0xFFD50000; // Rouge
			++j;
		}
		++i;
	}
	i = cos(data.player.pa);
	j = sin(data.player.pa);
	while (z <= 20)
	{
		data.addr[((int)data.player.pos_x + 3 + (int)(i * z)) * mapX*mapS + ((int)data.player.pos_y + 3 + (int)(j * z))] = 0xFFD50000; // Rouge
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
		mlx->data.player.pa += 0.01;
		if (mlx->data.player.pa > 2 * PI)
			mlx->data.player.pa -= 2 * PI;
		mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
	}
	else if (keycode == XK_d)
	{
		mlx->data.player.pa -= 0.01;
		if (mlx->data.player.pa < 0)
			mlx->data.player.pa += 2 * M_PI;
		mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
	}
	print(mlx);
	return (0);
}
