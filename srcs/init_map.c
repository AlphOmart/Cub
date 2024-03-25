/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:50:20 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 17:18:34 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_data data, t_ray ray, size_t i)
{
	int		j;
	int		line_0;
	double	line_h;

	line_h = (720 * (mapS)) / ray.dist;
	if (line_h > 720)
		line_h = 720;
	line_0 = (720 / 2) - (line_h / 2);
	j = 0;
	while (j < line_h)
	{
		data.game_addr[(j + line_0) * 1280 + i] = 0x808080;
		j++;
	}
}

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

void	mlx_fill_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < mapS - 1)
	{
		j = 0;
		while (j < mapS - 1)
		{
			mlx->data.addr[(x + i) * mapX * mapS + (y + j)] = color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx)
{
	int	y;
	int	x;
	int	color;

	x = 0;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y][x] == '1')
				color = 0x808080;
			else
				color = 0xFFFFFF;
			mlx_fill_square(mlx, y * mapS + 3, x * mapS + 3, color);
			x++;
		}
		y++;
	}
}
