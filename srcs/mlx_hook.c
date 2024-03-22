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
			data.addr[((int)(data.player.pos_y + j)) * mapX * mapS + \
				((int)(data.player.pos_x + i))] = 0xFFD50000;
			++j;
		}
		++i;
	}
	i = cos(data.player.pa);
	j = sin(data.player.pa);
	while (z <= 20)
	{
		data.addr[((int)data.player.pos_y + 3 + (int)(j * z)) * mapX * mapS + \
				((int)data.player.pos_x + 3 + (int)(i * z))] = 0xFFD50000;
		++z;
	}
}

int	handle_key_press(int keycode, t_mlx *mlx)
{

	double		temp1, temp2;


	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
	{
		temp1 = (int)(mlx->data.player.pos_y + mlx->data.player.pdy) >> 6;
		temp2 = (int)(mlx->data.player.pos_x + mlx->data.player.pdx) >> 6;
		printf("test1 = %f\n", temp1);
		printf("test1 = %i\n", (int)temp1);
		printf("test : %c\n",map[(int)temp1][(int)temp2]);
		if (map[(int)temp1][(int)temp2] == '1')
			return (0);
		mlx->data.player.pos_x += mlx->data.player.pdx;
		mlx->data.player.pos_y += mlx->data.player.pdy;
	}
	else if (keycode == XK_s)
	{
		temp1 = (int)(mlx->data.player.pos_y - mlx->data.player.pdy) >> 6;
		temp2 = (int)(mlx->data.player.pos_x - mlx->data.player.pdx) >> 6;
		printf("test1 = %f\n", temp1);
		printf("test1 = %i\n", (int)temp1);
		printf("test : %c\n",map[(int)temp1][(int)temp2]);
		if (map[(int)temp1][(int)temp2] == '1')
			return (0);
		mlx->data.player.pos_x -= mlx->data.player.pdx;
		mlx->data.player.pos_y -= mlx->data.player.pdy;
	}
	else if (keycode == XK_a)
	{
		mlx->data.player.pa -= 0.1;
		if (mlx->data.player.pa < 0)
			mlx->data.player.pa += (2 * M_PI);
		mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
	}
	else if (keycode == XK_d)
	{
		mlx->data.player.pa += 0.1;
		if (mlx->data.player.pa > 2 * M_PI)
			mlx->data.player.pa -= (2 * M_PI);
		mlx->data.player.pdx = cosf(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sinf(mlx->data.player.pa) * 5;
	}
	print(mlx);
	return (0);
}
