/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:34:13 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/22 16:18:10 by edboutil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
}					t_player;

typedef struct s_data
{
	void			*img_ptr;
	int				*addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
	t_player		player;
}					t_data;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_data			data;
}					t_mlx;

//window
void				close_window(t_mlx *mlx);
void				color_pixels(t_mlx *mlx, int width, int height);
void				init_mlx_data(t_mlx *mlx);
void				init_window(t_mlx	*mlx);

//player
void				draw_player(t_data data);
int					handle_key_press(int keycode, t_mlx *mlx);


void				print(t_mlx *mlx);
void				draw_map(t_mlx* mlx, int cell_size);
// void	ft_free(t_data *data, int n);
// void	ft_error(char *str, t_data *data, int n);

#endif
