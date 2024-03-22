/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:33:36 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 17:15:50 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub3d.h"

int mapX = 10, mapY= 10, mapS = 64;

void	draw_line(t_data data, double xo, double yo, double angle)
{
	double i;
	double j;
	double k;
	size_t z;

	i = xo - data.player.pos_x;
	j = yo - data.player.pos_y;
	k = sqrt((i * i) + (j * j));
	i = cos(angle);
	j = sin(angle);
	z = 0;
	while (z <= k && z < 550)
	{
		data.addr[((int)data.player.pos_y + 3 + (int)(j * z)) * mapX * mapS + \
				((int)data.player.pos_x + 3 + (int)(i * z))] = 0xFF015000;
		++z;
	}
}

char map[10][10] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

//void	color_pixels(t_mlx *mlx, int width, int height);
void	draw_player(t_data data);

int	print(t_mlx *mlx)
{
	color_pixels(mlx, 1280, 720);
	draw_map(mlx);
	 raycast(mlx->data);
	draw_player(mlx->data);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->data.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->data.game_ptr, 641, 0);
	return 0;
}


//Todo in parsing get player coord
int	main(void)
{
	t_mlx		*mlx;

	mlx = malloc(sizeof(t_mlx) * 1);
	if (!mlx)
	return (-1);
	init_window(mlx);
	print(mlx);
	mlx_do_key_autorepeaton(mlx->mlx_ptr);
	mlx_hook(mlx->win, KeyRelease, KeyRelease, handle_key_press, mlx);
	mlx_hook(mlx->win, 17, 0, &close_window, mlx);
	mlx_loop_hook(mlx->mlx_ptr, print, mlx);
	mlx_loop(mlx->mlx_ptr);
//	close_window(mlx);
	return (0);
}
