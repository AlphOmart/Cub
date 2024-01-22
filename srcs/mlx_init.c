/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:35:40 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 13:57:38 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->data.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx);
	exit(0);
}

/*
**@brief Each int of data.data represents a pixels of the map
** with each index represents a complete color of a pixel.
*/
void color_pixels(t_mlx *mlx, int width, int height)
{
	int count_height;
	int count_width;

	count_height = 0;
	//printf("%f\n", mlx.data.player.pos_x);
	while (count_height < height)
	{
		count_width = 0;
		while (count_width < width)
			{
			mlx->data.addr[count_height * width + count_width] = 0xFFB3E5FC; // Couleur transparente
			count_width++;
		}
		count_height++;
	}
}

void	init_window(t_mlx	*mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx->data.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->data.addr = (int *)mlx_get_data_addr(mlx->data.img_ptr, &mlx->data.bits_per_pixel, &mlx->data.line_length,
		&mlx->data.endian);
	mlx->data.player.pos_x = 300;
	mlx->data.player.pos_y = 300;

}
