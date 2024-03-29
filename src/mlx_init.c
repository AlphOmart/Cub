/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:06:33 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 12:56:54 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	open_textures(t_mlx *mlx, t_data *data);

void	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->data = data;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "cub3d");
	mlx->game_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->game_addr = mlx_get_data_addr(mlx->game_ptr, \
		&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	open_textures(mlx, data);
}

void	reverse(char *img_data, t_textures *tex, int c, int x_y[2])
{
	char	temp;

	temp = img_data[x_y[1] * tex->width + x_y[0] + c];
	img_data[x_y[1] * tex->width + x_y[0] + c] = \
					img_data[x_y[1] * tex->width + \
					(tex->width - x_y[0] / 4 - 1) * 4 + c];
	img_data[x_y[1] * tex->width + \
					(tex->width - x_y[0] / 4 - 1) * 4 + c] = temp;
}

char	*reverse_textures(t_textures *tex)
{
	int		x_y[2];
	int		c;
	char	*img_data;

	x_y[1] = 0;
	img_data = (char *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel, \
		&tex->width, &tex->endian);
	while (x_y[1] < tex->height)
	{
		x_y[0] = 0;
		while (x_y[0] < tex->width / 2 * 4)
		{
			c = 0;
			while (c < 4)
			{
				reverse(img_data, tex, c, x_y);
				c++;
			}
			x_y[0] += 4;
		}
		x_y[1]++;
	}
	return (img_data);
}

void	open_reversed_textures(t_mlx *mlx, t_data *data)
{
	mlx->so.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->so, &(mlx->so.width), &(mlx->so.height));
	if (!mlx->so.img)
		ft_exit(data, mlx, 1, 0);
	mlx->so.addr = mlx_get_data_addr \
					(mlx->so.img, \
					&mlx->so.bits_per_pixel, \
					&mlx->so.width, &mlx->so.endian);
	reverse_textures(&mlx->so);
	mlx->we.img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->we,
			&(mlx->we.width), &(mlx->we.height));
	if (!mlx->we.img)
		ft_exit(data, mlx, 2, 0);
	mlx->we.addr = mlx_get_data_addr \
					(mlx->we.img, \
					&mlx->we.bits_per_pixel, \
					&mlx->we.width, &mlx->we.endian);
	reverse_textures(&mlx->we);
}

void	open_textures(t_mlx *mlx, t_data *data)
{
	mlx->no.img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->no,
			&(mlx->no.width), &(mlx->no.height));
	if (!mlx->no.img)
		ft_exit(data, mlx, 0, 0);
	mlx->no.addr = mlx_get_data_addr \
				(mlx->no.img, \
				&mlx->no.bits_per_pixel, \
				&mlx->no.width, &mlx->no.endian);
	mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->ea, &(mlx->ea.width), &(mlx->ea.height));
	if (!mlx->ea.img)
		ft_exit(data, mlx, 3, 0);
	mlx->ea.addr = mlx_get_data_addr \
					(mlx->ea.img, \
					&mlx->ea.bits_per_pixel, \
					&mlx->ea.width, &mlx->ea.endian);
	open_reversed_textures(mlx, data);
	ft_free_data(data, 0);
}
