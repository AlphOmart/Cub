/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:35:29 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 13:08:48 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
	mlx_hook(mlx.win, KeyRelease, KeyRelease, handle_key_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, print_image, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
