#include "../headers/cub3d.h"

void	color_pixels(t_mlx *mlx);
void	open_textures(t_mlx *mlx, t_data *data);
void	ft_free_data(t_data *data, int i);

void	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->data = data;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "cub3d");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->addr = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel, &mlx->line_length,
	&mlx->endian);
	// color_pixels(mlx);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_ptr, 0, 0);
	open_textures(mlx, data);
}

void	free_mlx(t_mlx *mlx, int n)
{
	if (n)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[0].img);
	if (n >= 2)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[1].img);
	if (n >= 3)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[2].img);
	if (n >= 4)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[3].img);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
}

void ft_exit(t_data *data, t_mlx *mlx, int n)
{
	ft_free_data(data, 1);
	free_mlx(mlx, n);
	ft_error(RED ERROR YELLOW "invalid sprites path !\n" NC, 4);
}

void	open_textures(t_mlx *mlx, t_data *data)
{
	mlx->textures[0].img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->no,
			&(mlx->textures[0].width), &(mlx->textures[0].height));
	if (!mlx->textures[0].img)
		ft_exit(data, mlx, 0);
	mlx->textures[1].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->so, &(mlx->textures[1].width), &(mlx->textures[1].height));
	if (!mlx->textures[1].img)
		ft_exit(data, mlx, 1);

	mlx->textures[2].img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->we,
			&(mlx->textures[2].width), &(mlx->textures[2].height));
	if (!mlx->textures[2].img)
		ft_exit(data, mlx, 2);
	mlx->textures[3].img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->ea, &(mlx->textures[3].width), &(mlx->textures[3].height));
	if (!mlx->textures[3].img)
		ft_exit(data, mlx, 3);
	ft_free_data(data, 0);
}

int close_window(t_mlx *mlx)
{
	free_mlx(mlx, 4);
	exit(0);
}