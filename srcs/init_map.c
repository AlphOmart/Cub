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

void mlx_fill_square(t_mlx *mlx, int x, int y, int size, int color)
{
	int	i;
	int	j;

	j = 2;
	i = 2;
	while (i < size - 3)
	{
		j = 2;
		while (j < size - 3)
		{
			mlx->data.addr[(x + i) * mapX*mapS + (y + j)] = color;
			j++;
		}
		i++;
	}
}

void draw_map(t_mlx* mlx)
{

	int y;
	int x;
	int color;

	x = 0;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			color = (map[x*mapX+y] == 1) ? 0x808080 : 0xFFFFFF;
			mlx_fill_square(mlx, x * mapS, y * mapS, mapS, color);
			x++;
		}
		y++;
	}
}
