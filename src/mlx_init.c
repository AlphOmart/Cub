#include "../headers/cub3d.h"

void	color_pixels(t_mlx *mlx);
void	open_textures(t_mlx *mlx, t_data *data);
void	ft_free_data(t_data *data, int i);

void	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->data = data;
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, 1920, 1920, "cub3d");
	mlx->game_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->map_ptr = mlx_new_image(mlx->mlx_ptr, (mlx->player.width_map * CELL_SIZE), (mlx->player.high_map * CELL_SIZE));
	mlx->map_addr = (int *)mlx_get_data_addr(mlx->map_ptr, &mlx->bits_per_pixel, &mlx->line_length,
	&mlx->endian);
	mlx->game_addr = mlx_get_data_addr(mlx->game_ptr, &mlx->bits_per_pixel, &mlx->line_length,
	&mlx->endian);
	open_textures(mlx, data);
}

void	free_mlx(t_mlx *mlx, int n, int c)
{
	if (n)
		mlx_destroy_image(mlx->mlx_ptr, mlx->no.img);
	if (n >= 2)
		mlx_destroy_image(mlx->mlx_ptr, mlx->so.img);
	if (n >= 3)
		mlx_destroy_image(mlx->mlx_ptr, mlx->we.img);
	if (n >= 4)
		mlx_destroy_image(mlx->mlx_ptr, mlx->ea.img);
	mlx_destroy_image(mlx->mlx_ptr, mlx->game_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	if (c != 0)
		free_map(mlx->data->map);
}

void ft_exit(t_data *data, t_mlx *mlx, int n, int c)
{
	ft_free_data(data, 1);
	free_mlx(mlx, n, c);
	ft_error(RED ERROR YELLOW "invalid sprites path !\n" NC, 4);
}

void	open_textures(t_mlx *mlx, t_data *data)
{
	mlx->no.img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->no,
			&(mlx->no.width), &(mlx->no.height));
	mlx->no.addr = mlx_get_data_addr \
				(mlx->no.img, \
				&mlx->no.bits_per_pixel, \
				&mlx->no.width, &mlx->no.endian);
	if (!mlx->no.img)
		ft_exit(data, mlx, 0, 0);
	mlx->so.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->so, &(mlx->so.width), &(mlx->so.height));
	if (!mlx->so.img)
		ft_exit(data, mlx, 1, 0);

	mlx->we.img = mlx_xpm_file_to_image(mlx->mlx_ptr, data->we,
			&(mlx->we.width), &(mlx->we.height));
	if (!mlx->we.img)
		ft_exit(data, mlx, 2, 0);
	mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			data->ea, &(mlx->ea.width), &(mlx->ea.height));
	if (!mlx->ea.img)
		ft_exit(data, mlx, 3, 0);
	ft_free_data(data, 0);
}

int close_window(t_mlx *mlx)
{
	free_mlx(mlx, 4, 1);
	exit(0);
}