/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:34:13 by edboutil          #+#    #+#             */
/*   Updated: 2024/01/17 17:56:11 by edboutil         ###   ########.fr       */
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

enum e_keycode
{
	ESQ = 65307,
};


typedef struct s_data
{
	void			*img_ptr;
	int				*addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
}					t_data;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_data			data;
}					t_mlx;

// void	ft_free(t_data *data, int n);
// void	ft_error(char *str, t_data *data, int n);

#endif
