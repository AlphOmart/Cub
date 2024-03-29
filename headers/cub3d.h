/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:36:49 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 12:46:57 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

////////////////////////////////////////////////////////////////////////////////
//////////                         INCLUDES                           //////////
////////////////////////////////////////////////////////////////////////////////
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "../libft/headers/libft.h"
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>

////////////////////////////////////////////////////////////////////////////////
//////////                         DEFINES                            //////////
////////////////////////////////////////////////////////////////////////////////
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define NC		"\033[0m"
////////////////////////////////////////////////////////////////////////////////
//////////                      ERROR_MESSAGES                        //////////
////////////////////////////////////////////////////////////////////////////////
# define ERROR    "Error\n"
# define USAGE    "Usage : ./cub3D <path/map_file.cub> "
# define NOT_FILE "Invalid file ! (directory)"
# define INV_PATH "Invalid path or file."
# define INV_ELEMENT "Invalid file (element in file)."
# define MALL_ERR "malloc failed, "
# define FILE_READ_ERR "Problem encountered during file reading"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define CELL_SIZE 64
////////////////////////////////////////////////////////////////////////////////
//////////                        STRUCTURES                          //////////
////////////////////////////////////////////////////////////////////////////////

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	int		f[3];
	int		c[3];

	char	**map;
	int		width_map;
	int		high_map;

	void	*element[6];
}		t_data;

typedef struct s_textures
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				height;
	int				width;
}					t_textures;

typedef struct s_ray
{
	bool	hit;
	double	angle;
	double	yo, xo;
	double	rx;
	double	ry;
	double	dist;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	pdx;
	double	pdy;
	double	pa;
	double	fov;
	char	**map;
	int		width_map;
	int		high_map;
}			t_player;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	void			*map_ptr;
	void			*game_ptr;
	int				*map_addr;
	char			*game_addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;

	t_player		player;
	t_textures		no;
	t_textures		so;
	t_textures		ea;
	t_textures		we;
	t_data			*data;
}					t_mlx;

////////////////////////////////////////////////////////////////////////////////
//////////                        PROTOTYPES                          //////////
////////////////////////////////////////////////////////////////////////////////

void	ft_error(char *str, int err);
//--------------------------------get_file.c----------------------------------//
void	get_file(char *path, char ***file);
//-------------------------------data-init.c----------------------------------//
void	data_init(t_data *data, t_mlx *mlx);
//-------------------------------parse_data.c---------------------------------//
void	parse_data(char ***file, t_data *data);
void	get_pos(char **cpy, int start[2]);
//-----------------------------parse_textures.c-------------------------------//
void	parse_textures(char **to_put, char *to_get);
void	is_valid_path(char **path);
char	*trim_end(char *string);
//-----------------------------parse_colors.c-------------------------------//
void	get_colors(int colors[3], char *to_get);
//-----------------------------check_close.c---------------------------------//
bool	is_close(char **cpy);
//-----------------------------expensions.c---------------------------------//
void	zero_expension(char **map, int x, int y);
void	one_expension(char **map, int x, int y);
//-----------------------------check_map.c-----------------------------------//
bool	is_block(char **map);
//-----------------------------check_data.c---------------------------------//
void	check_data(char ***file, t_data *data);
void	free_map(char **cpy);
//-----------------------------map_cpy.c-----------------------------------//
void	map_cpy(char **map, char ***cpy);
//-----------------------------mlx_init.c-----------------------------------//
void	init_mlx(t_mlx *mlx, t_data *data);
int		close_window(t_mlx *mlx);

//-----------------------------mlx_utils.c-----------------------------------//
void	ft_exit(t_data *data, t_mlx *mlx, int n, int c);
int		close_window(t_mlx *mlx);

void	color_pixels(t_mlx *mlx);
void	raycast(t_player player, t_ray *selected);
int		handle_key_press(int keycode, t_mlx *mlx);
void	ft_free_data(t_data *data, int i);
int	print_image(t_mlx *mlx);
#endif