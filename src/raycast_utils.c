/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:18:19 by mwubneh           #+#    #+#             */
/*   Updated: 2024/03/29 13:19:04 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static double	fisheyes_fix(double ca);
static t_ray	ray_copy(t_ray ray, double dist, double ca);
static double	dist_calc(double x1, double x2, double t1, double t2);

t_ray	select_ray(t_player player, t_ray vert, t_ray horiz, double ca)
{
	double	vert_dist;
	double	horiz_dist;

	vert_dist = dist_calc(vert.rx, vert.ry, \
						player.pos_x, player.pos_y);
	horiz_dist = dist_calc(horiz.rx, horiz.ry, \
						player.pos_x, player.pos_y);
	if (horiz.hit && !vert.hit)
		return (ray_copy(horiz, horiz_dist, ca));
	if (vert.hit && !horiz.hit)
		return (ray_copy(vert, vert_dist, ca));
	if (horiz_dist > vert_dist)
		return (ray_copy(vert, vert_dist, ca));
	return (ray_copy(horiz, horiz_dist, ca));
}

double	fisheyes_fix(double ca)
{
	if (ca < 0)
		ca += 2 * M_PI;
	if (ca > 0)
		ca -= 2 * M_PI;
	return (ca);
}

static double	dist_calc(double x1, double x2, double t1, double t2)
{
	double	prod_1;
	double	prod_2;

	prod_1 = x1 - t1;
	prod_2 = x2 - t2;
	return (sqrt((prod_1 * prod_1) + (prod_2 * prod_2)));
}

static t_ray	ray_copy(t_ray ray, double dist, double ca)
{
	t_ray	select;

	select.rx = ray.rx;
	select.ry = ray.ry;
	select.hit = ray.hit;
	select.dist = dist * cos(fisheyes_fix(ca));
	return (select);
}
