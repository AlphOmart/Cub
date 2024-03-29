/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:06:33 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 12:41:27 by edboutil         ###   ########lyon.fr   */
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

char	*reverse_textures(t_textures *tex)
{
	int		y;
	int		x;
	int		c;
	char	*img_data;
	char	temp;

	y = 0;
	img_data = (char *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel, \
		&tex->width, &tex->endian);
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width / 2 * 4)
		{
			c = 0;
			while (c < 4)
			{
				temp = img_data[y * tex->width + x + c];
				img_data[y * tex->width + x + c] = \
					img_data[y * tex->width + (tex->width - x / 4 - 1) * 4 + c];
				img_data[y * tex->width + \
					(tex->width - x / 4 - 1) * 4 + c] = temp;
				c++;
			}
			x += 4;
		}
		++y;
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
