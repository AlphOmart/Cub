/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 14:52:08 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub3d.h"
# define PI 3.14159265359
void	color_pixels(t_mlx *mlx, int width, int height);
void	draw_player(t_data data);

void	print(t_mlx *mlx)
{
	color_pixels(mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_player(mlx->data);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->data.img_ptr, 0, 0);
}

void	draw_player(t_data data)
{
	int	i;
	int j;
	int z;

	i = 0;
	z = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			data.addr[((int)data.player.pos_x + i) * WIN_WIDTH + ((int)data.player.pos_y + j)] = 0xFFD50000; // Rouge
			++j;
		}
		++i;
	}
	while (z <= 10)
	{
		data.addr[((int)data.player.pos_x + i / 2 + (int)data.player.pdx * z) * WIN_WIDTH + ((int)data.player.pos_y + j / 2 + (int)data.player.pdy * z)] = 0xFFD50000; // Rouge
		z++;
	}
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->data.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx);
	exit(0);
}

int handle_key_press(int keycode, t_mlx *mlx)
{

	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
	{
		mlx->data.player.pos_x += mlx->data.player.pdx;
		mlx->data.player.pos_y += mlx->data.player.pdy;
	}
	else if (keycode == XK_s)
	{
		mlx->data.player.pos_x -= mlx->data.player.pdx;
		mlx->data.player.pos_y -= mlx->data.player.pdy;
	}
	else if (keycode == XK_a)
	{
		mlx->data.player.pa += 0.1;
		if (mlx->data.player.pa < 0)
			mlx->data.player.pa += 2 * PI;
		mlx->data.player.pdx = cos(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sin (mlx->data.player.pa) * 5;
	}
	else if (keycode == XK_d)
	{
		mlx->data.player.pa -= 0.1;
		if (mlx->data.player.pa > 2 * PI)
			mlx->data.player.pa -= 2 * PI;
		mlx->data.player.pdx = cos(mlx->data.player.pa) * 5;
		mlx->data.player.pdy = sin (mlx->data.player.pa) * 5;
	}
	print(mlx);
	return (0);
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
	mlx->data.player.pa = 0;
	mlx->data.player.pdx = 0;
	mlx->data.player.pdy = 0;


}

int	main(void)
{
	t_mlx		*mlx;

	mlx = malloc(sizeof(t_mlx) * 1);
	if (!mlx)
	return (-1);
	init_window(mlx);
	printf("%f\n", mlx->data.player.pos_x);
	print(mlx);
	mlx_do_key_autorepeaton(mlx->mlx_ptr);
	mlx_hook(mlx->win, KeyRelease, KeyRelease, handle_key_press, mlx);
	mlx_hook(mlx->win, 17, 0, &close_window, mlx);
	mlx_loop(mlx->mlx_ptr);
//	close_window(mlx);
	return (0);
}
