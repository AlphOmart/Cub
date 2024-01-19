/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/19 19:15:15 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "includes/cub3d.h"
# include <X11/keysym.h>

void color_pixels(t_mlx *mlx, int width, int height);
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

	i = 0;
	printf("coucou : %f\n", data.player.pos_x);
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

void close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(0);
}

int handle_key_press(int keycode, t_mlx *mlx)
{

	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
		mlx->data.player.pos_x -= 5;
	else if (keycode == XK_s)
		mlx->data.player.pos_x += 5;
	else if (keycode == XK_a)
		mlx->data.player.pos_y -= 5;
	else if (keycode == XK_d)
		mlx->data.player.pos_y += 5;
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

int	main(void)
{
	t_mlx		*mlx;

	mlx = malloc(sizeof(t_mlx) * 1);
	if (!mlx)
	return (-1);
	init_window(mlx);
	printf("%f\n", mlx->data.player.pos_x);
	print(mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, handle_key_press, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
