#include "../headers/cub3d.h"

static unsigned int	rgb_conv(int rgb[3])
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

void color_pixels(t_mlx *mlx) {
	unsigned int	floor;
	unsigned int	celling;
	int				count_height;
	int				count_width;

	floor = rgb_conv(mlx->data->f);
	celling = rgb_conv(mlx->data->c);


	count_height = 0;
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
