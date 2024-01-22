/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:15:48 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 14:50:08 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_player(t_data data)
{
	int	i;
	int j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			data.addr[((int)data.player.pos_x + i) * WIN_WIDTH + ((int)data.player.pos_y + j)] = 0xFFD50000; // Rouge
			++j;
		}
		++i;
	}
}

int handle_key_press(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
		mlx->data.player.pos_x -= 10;
	else if (keycode == XK_s)
		mlx->data.player.pos_x += 10;
	else if (keycode == XK_a)
		mlx->data.player.pos_y -= 10;
	else if (keycode == XK_d)
		mlx->data.player.pos_y += 10;
	print(mlx);
	return (0);
}
