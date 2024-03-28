/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:35:29 by mwubneh           #+#    #+#             */
/*   Updated: 2024/02/26 14:01:50 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/cub3d.h"

/**
 * @brief This function is used to display an error message and
 * 			exit the program gracefully by assigning "errno" to "err" and
 * 			printing "str" to the standard error output.
 * @param str string of characters to be displayed on the error output
 * @param err Parameter that will be used to assign
 * 				the program's exit value to errno.
 * @return program exit with exit
 */
void	ft_error(char *str, int err)
{
	errno = err;
	perror(str);
	exit(err);
}
void	ft_free_data(t_data *data, int i)
{
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	if (i != 0)
		free_map(data->map);
}
void	draw_line(t_mlx *mlx, double xo, double yo, double angle)
{
	double i;
	double j;
	double k;
	size_t z;

	i = xo - mlx->player.pos_x;
	j = yo - mlx->player.pos_y;
	k = sqrt((i * i) + (j * j));
	i = cos(angle);
	j = sin(angle);
	z = 0;
	while (z <= k && z < 550)
	{
		mlx->map_addr[((int)mlx->player.pos_y + 3 + (int)(j * z)) * mlx->player.width_map * CELL_SIZE + \
				((int)mlx->player.pos_x + 3 + (int)(i * z))] = 0xFF015000;
		++z;
	}
}

void	draw_player(t_mlx *mlx)
{
	double	i;
	double	j;
	int		z;

	z = 0;
	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			mlx->map_addr[((int)(mlx->player.pos_y + j)) * mlx->player.width_map * CELL_SIZE + \
				((int)(mlx->player.pos_x + i))] = 0xFFD50000;
			++j;
		}
		++i;
	}
	i = cos(mlx->player.pa);
	j = sin(mlx->player.pa);
	while (z <= 20)
	{
		mlx->map_addr[((int)mlx->player.pos_y + 3 + (int)(j * z)) * mlx->player.width_map * CELL_SIZE + \
				((int)mlx->player.pos_x + 3 + (int)(i * z))] = 0xFFD50000;
		++z;
	}
}

void	mlx_fill_square(t_mlx *mlx, int y, int x, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < CELL_SIZE - 1)
	{
		j = 0;
		while (j < CELL_SIZE - 1)
		{
			mlx->map_addr[(y + i) * (mlx->player.width_map * CELL_SIZE) + (x + j)] = color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < mlx->player.high_map)
	{
		x = 0;
		while (x < mlx->player.width_map)
		{
			if (mlx->player.map[y][x] == '1')
				color = 0x808080;
			else
				color = 0xFFFFFF;
			mlx_fill_square(mlx, y * CELL_SIZE + 3, x * CELL_SIZE + 3, color);
			x++;
		}
		y++;
	}
}

int	get_src_x(t_ray r, t_player player, t_textures tex)
{
	int src_x;
	src_x = -1;

	if ((int)fmod(r.rx, CELL_SIZE) + 1 == CELL_SIZE && player.pos_x - r.rx > 0)
		src_x = ((int)(tex.width - r.ry + (2048 / tex.width *CELL_SIZE)) % CELL_SIZE) * tex.width / CELL_SIZE;
	else if (fmod(r.rx, CELL_SIZE) == 0 && (player.pos_x - r.rx) < 0)//
		src_x = ((int)(r.ry) % CELL_SIZE) * tex.width / CELL_SIZE;//
	else if (fmod(r.ry, CELL_SIZE) == 0 && player.pos_y - r.ry < 0)
		src_x = ((int)(tex.width - r.rx + (2048 / tex.width *CELL_SIZE)) % CELL_SIZE) * tex.width / CELL_SIZE;
	else
		src_x = ((int)(r.rx) % CELL_SIZE) * tex.width / CELL_SIZE;

	return (src_x);
}

void	draw_wall(t_mlx *mlx, int pos, t_ray r, t_textures tex)
{
	int		i;
	double	src_pos;
	int		slice_height;
	int		src_x;

	src_x = get_src_x(r, mlx->player, tex);
	if (src_x < 0)
		return ;
	slice_height = (int)(CELL_SIZE / r.dist * (WIN_HEIGHT));
	i = WIN_HEIGHT / 2 - slice_height / 2;
	src_pos = 0;
	if (i < 0)
	{
		src_pos = -i * (double) tex.height / (double) slice_height;
		i = 0;
	}
	while (src_pos < tex.height && i < WIN_HEIGHT)
	{
		char *dst = tex.addr + (int)src_pos * tex.width + src_x;
		int color = *(unsigned int *)dst;
		dst = mlx->game_addr + (int)i * mlx->line_length + pos * (mlx->bits_per_pixel / 8);
		*(unsigned int*)dst = color;
		src_pos += (double) tex.height / (double) slice_height;
		i++;
	}
}

int	print_image(t_mlx *mlx)
{
	t_ray	rays[WIN_WIDTH];
	int		i;

	i = 0;
	color_pixels(mlx);
	draw_map(mlx);
	draw_player(mlx);
	raycast(mlx, mlx->player, rays);
	while(i < WIN_WIDTH)
	{
		if ((int)fmod(rays[i].rx, CELL_SIZE) + 1 == CELL_SIZE && mlx->player.pos_x - rays[i].rx > 0)
			draw_wall(mlx, i, rays[i], mlx->no);
		else if (fmod(rays[i].rx, CELL_SIZE) == 0 && (mlx->player.pos_x - rays[i].rx) < 0)
			draw_wall(mlx, i, rays[i], mlx->no);
		else if (fmod(rays[i].ry, CELL_SIZE) == 0 && mlx->player.pos_y - rays[i].ry < 0)
			draw_wall(mlx, i, rays[i], mlx->no);
		else
			draw_wall(mlx, i, rays[i], mlx->no);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->map_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->game_ptr, 0, 400);
	return 0;
}

double	get_start_angle(char c)
{
	if ( c == 'N')
		return (270);
	else if (c == 'W')
		return (180);
	else if (c == 'S')
		return (90);
	else if (c == 'E')
		return (0);
	return (0);
}

void	init_player(t_mlx *mlx, t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	get_pos(data->map, fd);
	mlx->player.pos_x = (fd[1] * CELL_SIZE) + 0.5 * CELL_SIZE;
	mlx->player.pos_y = ((fd[0]+ 0.5 ) * CELL_SIZE);
	mlx->player.pa = (get_start_angle(data->map[fd[0]][fd[1]]) * M_PI) / 180;
	mlx->player.pdx = cos(mlx->player.pa);
	mlx->player.pdy = sin(mlx->player.pa);
	mlx->player.fov = 60;
	mlx->player.high_map = data->high_map;
	mlx->player.width_map = data->width_map;
	mlx->player.map = data->map;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_mlx	mlx;
	char	**file;

	if (argc != 2 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 5))
		ft_error(RED ERROR YELLOW USAGE NC, 2);
	get_file(argv[1], &file);
	data_init(&data, &mlx);
	parse_data(&file, &data);
	free_map(file);
	init_player(&mlx, &data);
	init_mlx(&mlx, &data);
	mlx_hook(mlx.win, 17, 0, close_window, &mlx);


	//fonctionne jusque la !
	mlx_hook(mlx.win, KeyRelease, KeyRelease, handle_key_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, print_image, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}