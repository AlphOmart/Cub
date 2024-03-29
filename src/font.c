/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:59:03 by edboutil          #+#    #+#             */
/*   Updated: 2024/03/29 12:57:18 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static unsigned int	rgb_conv(int rgb[3])
{
	unsigned int	result;
	int				i;

	i = 0;
	result = 0xFF;
	while (i < 3)
	{
		result = (result << 8) | (unsigned int)rgb[i];
		i++;
	}
	return (result);
}

void	color_pixels(t_mlx *mlx)
{
	unsigned int	floor;
	unsigned int	celling;
	int				count_height;
	int				count_width;
	char			*dst;

	floor = rgb_conv(mlx->data->f);
	celling = rgb_conv(mlx->data->c);
	count_height = 0;
	while (count_height < WIN_HEIGHT)
	{
		count_width = 0;
		while (count_width < WIN_WIDTH)
		{
			dst = mlx->game_addr + (count_height * mlx->line_length + \
					count_width * (mlx->bits_per_pixel / 8));
			if (count_height > WIN_HEIGHT / 2)
				*(unsigned int *)dst = floor;
			else
				*(unsigned int *)dst = celling;
			count_width++;
		}
		count_height++;
	}
}
