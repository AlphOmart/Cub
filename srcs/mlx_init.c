/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                     (720 * (mapS)) / ray.dist                           +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:35:40 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 17:23:18 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->data.game_ptr);
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
void	color_pixels(t_mlx *mlx, int width, int height)
{
	int	count_h;
	int	count_w;

	count_h = 0;
	while (count_h < height)
	{
		count_w = 0;
		while (count_w < width)
		{
			if (count_h > height / 2)
				mlx->data.game_addr[count_h * width + count_w] = 0xFFB3E5FC;
			else
				mlx->data.game_addr[count_h * width + count_w] = 0xFFB005FC;
			count_w++;
		}
		count_h++;
	}
}

void	open_textures(t_mlx *mlx, t_data *data)
{
	data->no = "textures/1.xpm";
	data->so = "textures/2.xpm";
	data->ea = "textures/3.xpm";
	data->we = "textures/4.xpm";
	mlx->data.textures[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->no,
			&(mlx->data.textures[0].width), &(mlx->data.textures[0].height));
	if (!mlx->data.textures[0].img)
		exit(0);
	mlx->data.textures[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->so, &(mlx->data.textures[1].width), &(mlx->data.textures[1].height));
	if (!mlx->data.textures[1].img)
		exit(0);
	mlx->data.textures[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->we,
			&(mlx->data.textures[2].width), &(mlx->data.textures[2].height));
	if (!mlx->data.textures[2].img)
		exit(0);
	mlx->data.textures[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->ea, &(mlx->data.textures[3].width), &(mlx->data.textures[3].height));
	if (!mlx->data.textures[3].img)
		exit(0);
	mlx->data.textures[0].addr = mlx_get_data_addr \
				(mlx->data.textures[0].img, \
				&mlx->data.textures[0].bits_per_pixel, \
				&mlx->data.textures[0].width, &mlx->data.textures[0].endian);
	mlx->data.textures[1].addr = mlx_get_data_addr \
					(mlx->data.textures[1].img, \
					&mlx->data.textures[1].bits_per_pixel, \
					&mlx->data.textures[1].width, &mlx->data.textures[1].endian);
	mlx->data.textures[2].addr = mlx_get_data_addr \
						(mlx->data.textures[2].img, \
						&mlx->data.textures[2].bits_per_pixel, \
						&mlx->data.textures[2].width, &mlx->data.textures[2].endian);
	mlx->data.textures[3].addr = mlx_get_data_addr \
						(mlx->data.textures[3].img, \
						&mlx->data.textures[3].bits_per_pixel, \
						&mlx->data.textures[3].width, &mlx->data.textures[3].endian);
}

//Memo cos et sin prennent uniquement des radiants
void	init_window(t_mlx	*mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, 1925, 725, "cub3d");
	mlx->data.img_ptr = mlx_new_image(mlx->mlx_ptr, 10 * CELL_SIZE, \
			10 * CELL_SIZE);
	mlx->data.addr = (int *)mlx_get_data_addr \
			(mlx->data.img_ptr, \
			&mlx->data.bits_per_pixel, \
			&mlx->data.line_length, &mlx->data.endian);
	mlx->data.game_ptr = mlx_new_image(mlx->mlx_ptr, 1280, \
			720);
	mlx->data.game_addr = (int *)mlx_get_data_addr \
			(mlx->data.game_ptr, \
			&mlx->data.bits_per_pixel, \
			&mlx->data.line_length, &mlx->data.endian);
	mlx->data.player.pos_x = 1.10 * CELL_SIZE;
	mlx->data.player.pos_y = 1.10 * CELL_SIZE;
	mlx->data.player.pa = (90 * M_PI) / 180;
	mlx->data.player.fov = 60;
	mlx->data.player.pdx = cos(mlx->data.player.pa);
	mlx->data.player.pdy = sin(mlx->data.player.pa);
	open_textures(mlx, &mlx->data);
}
