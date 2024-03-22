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
			color = (map[y][x] == '1') ? 0x808080 : 0xFFFFFF;
			mlx_fill_square(mlx, y * mapS + 3, x * mapS + 3 , color);
			x++;
		}
		y++;
	}
}
