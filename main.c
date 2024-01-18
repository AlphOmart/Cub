/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/17 17:59:01 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "includes/cub3d.h"

int close_window(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(0);
	return (0);
}

int handle_key_press(int keycode, void *param)
{
	if (keycode == ESQ)
		close_window(param);
	return (0);
}

/*
**@brief Each int of data.data represents a pixels of the map
** with each index represents a complete color of a pixel.
*/
void color_pixels(int *addr, int width, int height)
{
	int count_height;
	int count_width;

	count_height = 0;
	while (count_height < height)
	{
		count_width = 0;
		while (count_width < width)
		{
			if (count_height >= height / 2)
				addr[count_height * width + count_width] = 0x00FF0000; // Couleur rouge (format ARGB)
			else
				addr[count_height * width + count_width] = 0x00000000; // Couleur transparente
			count_width++;
		}
		count_height++;
	}
}

void	init_window()
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx.data.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.data.addr = (int *)mlx_get_data_addr(mlx.data.img_ptr, &mlx.data.bits_per_pixel, &mlx.data.line_length,
		&mlx.data.endian);
	color_pixels(mlx.data.addr, WIN_WIDTH, WIN_HEIGHT);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.data.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 1L << 0, handle_key_press, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

int	main(void)
{
	init_window();
	return (0);
}
