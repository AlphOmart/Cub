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
void	ft_free_data(t_data *data, int i)
{
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	if (i != 0)
		free_map(data->map);
}

static t_ray	select_ray(t_ray inter_horiz, t_ray inter_vert)
{
	if (inter_horiz.hit && !inter_vert.hit)
		return (inter_horiz);
	if (inter_vert.hit && !inter_horiz.hit)
		return (inter_vert);
	if (inter_horiz.dist < inter_vert.dist)
		return (inter_horiz);
	return (inter_vert);
}

int	ray_collide_horiz(double vector[2], t_ray *ray, t_mlx *mlx)
{
	int	to_check[2];

	to_check[1] = (int)ray->inter[1] / CELL_SIZE - (vector[1] <= 0);
	to_check[0] = (int)ray->inter[0] / CELL_SIZE;
	if (to_check[0] < 0 || to_check[0] >= mlx->data->width_map || \
		to_check[1] < 0 || to_check[1] >= mlx->data->high_map)
		return (ray->hit = 0, 0);
	if (mlx->data->map[to_check[1]][to_check[0]] == '1')
		return (ray->hit = 1, 1);
	return (0);
}
int	ray_collide_vert(double vector[2], t_ray *ray, t_mlx* mlx)
{
	int	to_check[2];

	to_check[0] = (int) ray->inter[0] / CELL_SIZE - (vector[0] <= 0);
	to_check[1] = (int) ray->inter[1] / CELL_SIZE;
	if (to_check[0] < 0 || to_check[0] >= mlx->data->width_map || \
		to_check[1] < 0 || to_check[1] >= mlx->data->high_map)
		return (ray->hit = 0, 0);
	if (mlx->data->map[to_check[1]][to_check[0]] == '1')
		return (ray->hit = 1, 1);
	return (0);
}
t_ray	check_collide(t_ray inter, double vec[2], t_mlx *mlx, int i)
{
	int		nb_iter;
	int		hit;
	double	vec_magnitude;

	inter.hit = 0;
	nb_iter = 0;
	inter.dist = fabs(inter.dist);
	vec_magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
	if (i == 1)
		hit = ray_collide_horiz(vec, &inter, mlx);
	else
		hit = ray_collide_vert(vec, &inter, mlx);
	while (!hit && nb_iter < 512)
	{
		inter.inter[0] += vec[0];
		inter.inter[1] += vec[1];
		inter.dist += vec_magnitude;
		if (i == 1)
			hit = ray_collide_horiz(vec, &inter, mlx);
		else
			hit = ray_collide_vert(vec, &inter, mlx);
		nb_iter++;
	}
	return (inter);
}

	void	check_horizontal(double x, double y, double angle, t_ray *ray, t_mlx *mlx)
	{
	t_ray	inter;
	double	rad;
	double vec[2];

	rad = angle * (M_PI / 180);
	if (angle == 0 || angle == 180)
	{
		ray->inter[0] = INFINITY;
		ray->inter[1] = y;
		ray->dist = INFINITY;
		ray->hit = 0;
		return;
	}
	inter.inter[1] = (double) CELL_SIZE * (((int)y / CELL_SIZE) + \
			(angle < 180) + \
			(fabs(fmod(y, CELL_SIZE) - CELL_SIZE) <= 0.0001 && \
							angle < 180) - \
			(fmod(y, CELL_SIZE) <= 0.0001 && \
							angle > 180));
	inter.dist = (inter.inter[1] - y) / sin(rad);
	inter.inter[0] = (inter.dist * cos(rad));
	inter.inter[0] += x;
	vec[1] = CELL_SIZE - 2 * CELL_SIZE * (angle > 180);
	vec[0] = fabs((CELL_SIZE / (y - inter.inter[1])) * (inter.inter[0] - x));
	if (angle > 90 && angle < 270)
  		vec[0] *= -1;
	*ray = check_collide(inter, vec, mlx, 1);
	return;
}

void	check_vertical(double x, double y, double angle, t_ray *ray, t_mlx *mlx)
{
	t_ray	inter;
	double	rad;
	double vec[2];

	rad = angle * (M_PI / 180);
	if (angle == 90 || angle == 270)
	{
		ray->inter[0] = INFINITY;
		ray->inter[1] = y;
		ray->dist = INFINITY;
		ray->hit = 0;
		return;
	}
	inter.inter[0] = ((double) CELL_SIZE) * (((int)x / CELL_SIZE) + \
			(angle < 90 || angle > 270) - \
			(fabs(fmod(x, CELL_SIZE)) <= 0.0001 && \
						(angle > 90 && angle < 270)) + \
			(fabs(fmod(x, CELL_SIZE) - CELL_SIZE) <= 0.0001 && \
						(angle <= 90 || angle >= 270)));
	inter.dist = (inter.inter[0] - x) / cos(rad);
	inter.inter[1] = (inter.dist * sin(rad));
	inter.inter[1] += y;
	vec[0] = CELL_SIZE - 2 * CELL_SIZE * (angle > 90 && angle < 270);
	vec[1] = (CELL_SIZE / (x - inter.inter[0])) * \
								(inter.inter[1] - y);
	if (angle < 90 || angle > 270)
		vec[1] *= -1;
	*ray = check_collide(inter, vec, mlx,2);
	return;
}

int	raycast(t_mlx *mlx)
{
	double	cur_angle;
	size_t	i;
	t_ray	horiz;
	t_ray	vert;

	cur_angle = mlx->player.angle - (mlx->player.fov * 0.5);
	cur_angle = fmod((fmod(cur_angle, 360) + 360), 360);
	i = 0;
	while (i < 1920)
	{
		check_horizontal(mlx->player.pos[0], mlx->player.pos[1], cur_angle, &horiz, mlx);
		check_vertical(mlx->player.pos[0], mlx->player.pos[1], cur_angle, &vert, mlx);
		mlx->player.rays[i] = select_ray(horiz, vert);
		printf("dist ray[%li] : %f\n hit : %i\n curr angle : %f\n", i, mlx->player.rays[i].dist, mlx->player.rays[i].hit, cur_angle);

		cur_angle += mlx->player.fov / 1920;
		i++;
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
	mlx->player.fov = 60;
}

int handle_key_press(int keycode, t_mlx *mlx)
{
	double angle;

	angle = mlx->player.angle;
	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_w)
	{
		mlx->player.pos[0] += mlx->player.pdx;
		mlx->player.pos[1] += mlx->player.pdy;
	}
	else if (keycode == XK_s)
	{
		mlx->player.pos[0] -= mlx->player.pdx;
		mlx->player.pos[1] -= mlx->player.pdy;
	}
	else if (keycode == XK_q)
	{
		mlx->player.angle += 0.5;
		mlx->player.pdx = cos(angle) * 5;
		mlx->player.pdy = sin (angle) * 5;
	}
	else if (keycode == XK_e)
	{
		mlx->player.angle -= 0.5;
		mlx->player.pdx = cos(angle) * 5;
		mlx->player.pdy = sin (angle) * 5;
	}
	return (0);
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