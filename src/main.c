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

#include <math.h>
#define CELL_SIZE 64
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
void	ft_free_data(t_data *data)
{
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free_map(data->map);
}

unsigned int	rgb_conv(int rgb[3])
{
	unsigned int	result;
	int	i;

	i = 0;
	result = 0xFF;
	while (i < 3)
	{
		result = (result << 8) | (unsigned int)rgb[i];
		i++;
	}
	return (result);
}

void color_pixels(t_mlx *mlx)
{
	unsigned int	floor;
	unsigned int	celling;
	int				count_height;
	int				count_width;

	floor = rgb_conv(mlx->data->f);
	celling = rgb_conv(mlx->data->c);


	count_height = 0;
	printf("celling = %X\n", celling);
	printf("floor = %X\n", floor);
	while (count_height < 1080)
	{
		count_width = 0;
		while (count_width < 1920)
		{
			if (count_height > 1080 / 2)
				mlx->addr[count_height * 1920 + count_width] = floor;
			else
				mlx->addr[count_height * 1920 + count_width] = celling;

			count_width++;
		}
		count_height++;
	}
}

void	check_horizontal(double pos[2], double angle, t_ray *ray)
{
	t_ray	inter;
	double	rad;
	double vec[2];

	rad = angle * M_PI_4 / 45;
	if (angle == 0 || angle == 180) {
		ray->inter[0] = INFINITY;
		ray->inter[1] = pos[1];
		ray->dist = INFINITY;
		ray->hit = 0;
		return;
	}
	inter.inter[1] = (double) CELL_SIZE * ((int)(pos[1] / CELL_SIZE) + (angle  < 180));
	inter.dist = (inter.inter[1] - pos[1]) / sin(rad);
	inter.inter[0] = (inter.dist * cos(rad));
	inter.inter[0] += pos[0];
	vec[1] = CELL_SIZE - 2 * CELL_SIZE * (angle > 180);
	vec[0] = fabs((CELL_SIZE / (pos[1] - inter.inter[1])) * (inter.inter[0] - pos[0]));
	if (angle > 90 || angle > 270)
		vec[0] *= -1;
	return;
}

int	raycast(t_mlx *mlx)
{
	double	cur_angle;
	size_t	i;
	t_ray	horiz;

	cur_angle = mlx->player.angle - (mlx->player.fov * 0.5);
	printf("%f", cur_angle);
	i = 0;
	while (i < 1920)
	{
		check_horizontal(mlx->player.pos, cur_angle, &horiz);
		//check_vertical(mlx->player.pos, cur_angle, &ray_verical);
	}
	return (0);
}

int	print_image(t_mlx *mlx)
{
	raycast(mlx);
	color_pixels(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_ptr, 0, 0);
	return 0;
}

double	get_start_angle(char c)
{
	if ( c == 'N')
		return (90);
	else if (c == 'W')
		return (180);
	else if (c == 'S')
		return (270);
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
	mlx->player.pos[0] = fd[0];
	mlx->player.pos[1] = fd[1];
	mlx->player.angle = get_start_angle(data->map[fd[0]][fd[1]]);
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
	//mlx_hook(mlx->win, KeyRelease, KeyRelease, handle_key_press, mlx);
	mlx_loop_hook(mlx.mlx_ptr, print_image, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}