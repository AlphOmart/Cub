/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:13:57 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 16:29:42 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static void	draw_wall(t_mlx *mlx, int pos, t_ray r, t_textures tex);
static int	mlx_get_color(double src_pos, int src_x, t_textures tex);
static void	mlx_put_pixel(t_mlx*mlx, int i, int pos, int color);
static void	get_i(int *i, int slice_height, double *src_pos, t_textures tex);

int	print_image(t_mlx *mlx)
{
	t_ray	rays[WIN_WIDTH];
	int		i;

	i = 0;
	color_pixels(mlx);
	raycast(mlx->player, rays);
	while (i < WIN_WIDTH)
	{
		if (fmod(rays[i].ry, CELL_SIZE) + 0.01 == CELL_SIZE && \
								mlx->player.pos_y - rays[i].ry > 0)
			draw_wall(mlx, i, rays[i], mlx->no);
		else if (fmod(rays[i].rx, CELL_SIZE) == 0 && \
								mlx->player.pos_x - rays[i].rx < 0)
			draw_wall(mlx, i, rays[i], mlx->ea);
		else if (fmod(rays[i].ry, CELL_SIZE) == 0 && \
								mlx->player.pos_y - rays[i].ry < 0)
			draw_wall(mlx, i, rays[i], mlx->so);
		else
			draw_wall(mlx, i, rays[i], mlx->we);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->game_ptr, 0, 0);
	return (0);
}

static void	draw_wall(t_mlx *mlx, int pos, t_ray r, t_textures tex)
{
	int		i;
	double	src_pos;
	int		slice_height;
	int		src_x;

	src_x = ((int) r.rx % CELL_SIZE) * tex.width / CELL_SIZE;
printf("rx :%f\n", fmod(r.rx, CELL_SIZE));
printf("ry :%f\n", fmod(r.ry, CELL_SIZE));
	if (fmod(r.rx, CELL_SIZE) == 0 || \
					(int)fmod(r.rx, CELL_SIZE) == CELL_SIZE - 1)
		src_x = ((int) r.ry % CELL_SIZE) * tex.width / CELL_SIZE;
	if (src_x < 0 || !r.hit)
		return ;
	slice_height = (int)(CELL_SIZE / r.dist * (WIN_HEIGHT));
	src_pos = 0;
	get_i(&i, slice_height, &src_pos, tex);
	while (src_pos <= tex.height && i < WIN_HEIGHT)
	{
		mlx_put_pixel(mlx, i, pos, mlx_get_color(src_pos, src_x, tex));
		src_pos += (double) tex.height / (double) slice_height;
		i++;
	}
}

static void	get_i(int *i, int slice_height, double *src_pos, t_textures tex)
{
	*i = WIN_HEIGHT / 2 - slice_height / 2;
	if (*i < 0)
	{
		*src_pos = -(*i) * (double) tex.height / (double) slice_height;
		*i = 0;
	}
}

static int	mlx_get_color(double src_pos, int src_x, t_textures tex)
{
	char	*dst;
	int		color;

	dst = tex.addr + (int)src_pos * tex.width + src_x;
	color = *(unsigned int *)dst;
	return (color);
}

static void	mlx_put_pixel(t_mlx*mlx, int i, int pos, int color)
{
	char	*dst;

	dst = mlx->game_addr + (int)i * mlx->line_length + pos * \
									(mlx->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}
