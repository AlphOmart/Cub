/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:50:20 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 17:02:35 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


void mlx_fill_square(t_mlx *mlx, int x, int y, int size, int color)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx->data.addr[(x + i) * WIN_WIDTH + (y + j)] = color;
			j++;
		}
		i++;
	}
}

void draw_map(t_mlx* mlx, int cell_size)
{

	int window_height;
	int y;
	int x;
	int color;

	x = 0;
	y = 0;
	window_height = 10 * cell_size;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			color = (map[x][y] == 1) ? 0x808080 : 0xFFFFFF;
			mlx_fill_square(mlx, x * (cell_size + 2), y * (cell_size + 2), cell_size, color);
			x++;
		}
		y++;
	}
}
