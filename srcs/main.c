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

# include "../includes/cub3d.h"

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

void	draw_wall(t_data *data, int pos, t_ray r, t_textures tex)
{
	int		i;
	double	src_pos;
	int		slice_height;
	int		src_x;

	src_x = ((int) r.rx % mapS) * tex.width / mapS;
	if (fmod(r.rx, mapS) == 0)
		src_x = ((int) r.ry % mapS) * tex.width / mapS;
	//if (src_x < 0)
	//	return ;
	slice_height = (int)(mapS / r.dist * (720));
	i = 720 / 2 - slice_height / 2;
	src_pos = 0;
	if (i < 0)
	{
		src_pos = -i * (double) tex.height / (double) slice_height;
		i = 0;
	}
	while (src_pos < tex.height && i < 720)
	{
		data->game_addr[i * 1280 + pos] = tex.addr[(int)src_pos * tex.width + src_x];
		src_pos += (double) tex.height / (double) slice_height;
		i++;
	}
}

int	print(t_mlx *mlx)
{
	t_ray	rays[1280];
	int	i;

	i = 0;
	color_pixels(mlx, 1280, 720);
	draw_map(mlx);
	draw_player(mlx->data);
	raycast(mlx->data, rays);
	while (i < 1280)
	{
		//printf("%f\n", mlx->data.player.pos_x - rays[i].rx);
		if (fmod(rays[i].ry, mapS) == 0 && mlx->data.player.pos_x - rays[i].rx > 0)
			draw_wall(&mlx->data, i, rays[i], mlx->data.textures[0]);//printf("Coucou1\n");
		else if (fmod(rays[i].rx, mapS) == 0 && mlx->data.player.pos_x - rays[i].rx < 0)
			draw_wall(&mlx->data, i, rays[i], mlx->data.textures[3]);//printf("2\n");
		else if (fmod(rays[i].ry, mapS) == 0 && mlx->data.player.pos_y - rays[i].ry < 0)
			draw_wall(&mlx->data, i, rays[i], mlx->data.textures[1]);//printf("3\n");
		else
		{
			draw_wall(&mlx->data, i, rays[i], mlx->data.textures[2]);
		}
		printf("%f\n", mlx->data.player.pos_y - rays[i].ry);
		i++;
	}
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
