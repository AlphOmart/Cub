/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/18 14:59:55 by mwubneh          ###   ########.fr       */
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

void	color_img(t_data data, char c, int x, int y)
{
	int	color;
	int count_height;
	int count_width;
	if (c == 1)
		color = 0x00FF0000;
	else
		color = 0x00000000;
	(void)x;
	(void)y;
	count_height = 0;
	while (count_height < 10)
	{
		count_width = 0;
		while (count_width < 10)
		{
			data.addr[count_height * 10 + count_width] = color; // Couleur transparente
			count_width++;
		}
		count_height++;
	}
}
void	img_gen(t_mlx mlx, char map[10][10], int width, int height)
{
	size_t	x;
	size_t	y;

	x = 0;
	(void)width;
	(void)height;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			color_img(mlx.data, map[x][y], x, y);
			y++;
		}
		x++;
	}
}

t_mlx	init_window()
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx.data.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.data.addr = (int *)mlx_get_data_addr(mlx.data.img_ptr, &mlx.data.bits_per_pixel, &mlx.data.line_length,
		&mlx.data.endian);
	return (mlx);
}
/*
@brief this fonction print a background with a blue zone for a minimap
*/
void	zone_minimap(t_data data, int count_height, int count_width, int width)
{
	if (count_height >= 890 && count_height <= 900  && count_width >= 1630)
		data.addr[count_height * width + count_width] = 0x000000FF; // Couleur rouge (format ARGB)
	else if (count_height >= 1070 && count_width >= 1630)
		data.addr[count_height * width + count_width] = 0x000000FF; // Couleur rouge (format ARGB)
	else if (count_width >= 1630 && count_width <= 1640 && count_height >=890)
		data.addr[count_height * width + count_width] = 0x000000FF; // Couleur rouge (format ARGB)
	else if (count_width >= width || (count_width >=1910 && count_height >= 890))
		data.addr[count_height * width + count_width] = 0x000000FF; // Couleur rouge (format ARGB)
}

void	minimap_window(t_mlx mlx, int width, int height)
{
	int count_height;
	int count_width;

	count_height = 0;
	while (count_height < height)
	{
		count_width = 0;
		while (count_width < width)
		{
			zone_minimap(mlx.data, count_height, count_width, width);
			count_width++;
		}
		count_height++;
	}
}

int	main(void)
{
	t_mlx	mlx;
	char	map[10][10] = {"1111111111",
						   "1000010001",
						   "1000000001",
						   "1000000001",
						   "1000000001",
						   "1000000001",
						   "1000000001",
						   "1000000001",
						   "1000000001",
						   "1111111111"};
	(void)map;
	mlx = init_window();
	color_pixels(mlx.data.addr, WIN_WIDTH, WIN_HEIGHT);
	minimap_window(mlx, WIN_WIDTH, WIN_HEIGHT);

	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.data.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 1L << 0, handle_key_press, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
