/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:20:39 by mwubneh           #+#    #+#             */
/*   Updated: 2024/04/02 14:03:10 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edboutil <edboutil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:00:54 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 16:30:47 by edboutil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	check_vertical(t_player player, t_ray *ray, double ray_angle);
void	check_horizontal(t_player player, t_ray *ray, double ray_angle);
t_ray	select_ray(t_player player, t_ray vert, t_ray horiz, double angle);

void	raycast(t_player player, t_ray *selected)
{
	t_ray	horiz;
	t_ray	vert;
	double	angle;
	int		i;

	angle = ((player.pa * 180) / M_PI) - (player.fov * 0.5);
	angle = fmod((fmod(angle, 360) + 360), 360);
	angle = angle * M_PI / 180;
	i = 0;
	while (i < WIN_WIDTH)
	{
		check_vertical(player, &vert, angle);
		check_horizontal(player, &horiz, angle);
		selected[i] = select_ray(player, vert, horiz, player.pa - angle);
		angle = (angle * 180 / M_PI) + (player.fov / WIN_WIDTH);
		angle = fmod((fmod(angle, 360) + 360), 360);
		angle = angle * M_PI / 180;
		i++;
	}
}

void	check_on_map(t_ray *ray, int *dof, t_player player, int mx_y[2])
{
	if (mx_y[0] >= 0 && mx_y[0] < player.width_map && \
						mx_y[1] < player.high_map && \
						mx_y[1] >= 0 && player.map[mx_y[1]][mx_y[0]] == '1')
	{
		ray->hit = true;
		*dof = 42;
	}
	else
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		*dof += 1;
	}
}

void	final_check(t_player player, t_ray *ray, int dof, int is_vert)
{
	int	mx_y[2];

	ray->hit = false;
	while (dof < 42)
	{
		mx_y[0] = ((int)(ray->rx) >> 6);
		if (is_vert == 1 && player.pos_x - ray->rx > 0)
			mx_y[0] = ((int)(ray->rx) >> 6) - 1;
		mx_y[1] = ((int)(ray->ry) >> 6);
		if (is_vert != 1 && player.pos_y - ray->ry > 0)
			mx_y[1] = ((int)(ray->ry) >> 6) - 1;
		check_on_map(ray, &dof, player, mx_y);
	}
	if (!ray->hit)
	{
		ray->rx = INFINITY;
		ray->ry = INFINITY;
	}
}

void	check_horizontal(t_player player, t_ray *ray, double ray_angle)
{
	double	a_tan;
	int		dof;

	a_tan = -1 / tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI)
	{
		ray->ry = (((int)player.pos_y >> 6) << 6);
		ray->rx = ((player.pos_y) - (ray->ry)) * a_tan + player.pos_x;
		ray->yo = -CELL_SIZE;
		ray->xo = -(ray->yo) * a_tan;
	}
	if (ray_angle < M_PI)
	{
		ray->ry = (((int)player.pos_y >> 6) << 6) + CELL_SIZE;
		ray->rx = ((player.pos_y) - ray->ry) * a_tan + player.pos_x;
		ray->yo = CELL_SIZE;
		ray->xo = -(ray->yo) * a_tan;
	}
	final_check(player, ray, dof, 0);
}

void	check_vertical(t_player player, t_ray *ray, double ray_angle)
{
	double	n_tan;
	int		dof;

	n_tan = -tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
	{
		ray->rx = (((int)player.pos_x >> 6) << 6);
		ray->ry = ((player.pos_x) - ray->rx) * n_tan + player.pos_y;
		ray->xo = -CELL_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
	{
		ray->rx = (((int)player.pos_x >> 6) << 6) + CELL_SIZE;
		ray->ry = ((player.pos_x) - ray->rx) * n_tan + player.pos_y;
		ray->xo = CELL_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	final_check(player, ray, dof, 1);
}
