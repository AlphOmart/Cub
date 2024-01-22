/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 16:30:04 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
# include <X11/keysym.h>

voidcolor_pixels(t_mlx *mlx, int width, int height);
void	draw_player(t_data data);

void	print(t_mlx *mlx)
{
	color_pixels(mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_map(mlx->mlx_ptr, 30);
	draw_player(mlx->data);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->data.img_ptr, 0, 0);
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
	mlx_loop(mlx->mlx_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->data.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx);
	return (0);
}
