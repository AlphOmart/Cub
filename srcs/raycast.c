
#include "../includes/cub3d.h"

void	check_vertical(t_data data, t_ray *ray, double ray_angle);
void	check_horizontal(t_data data, t_ray *ray, double ray_angle);
t_ray	select_ray(t_data data, t_ray vert, t_ray horiz, double angle);

void	raycast(t_data data, t_ray *selected)
{
	t_ray	horiz;
	t_ray	vert;
	double	angle;
	size_t	i;

	angle = ((data.player.pa * 180) / M_PI) - (data.player.fov * 0.5);
	angle = fmod((fmod(angle, 360) + 360), 360);
	angle = angle * M_PI / 180;
	i = 0;
	while (i < 1280)
	{
		check_vertical(data, &vert, angle);
		check_horizontal(data, &horiz, angle);
		selected[i] = select_ray(data, vert, horiz, data.player.pa - angle);
		draw_line(data, selected[i].rx, selected[i].ry, angle);
		//draw_line(data, horiz.rx, horiz.ry, angle);
		//draw_walls(data, selected[i], i);
		angle = (angle * 180 / M_PI) + (data.player.fov / 1280);
		angle = fmod((fmod(angle, 360) + 360), 360);
		angle = angle * M_PI / 180;
		i++;
	}
}

void	final_check(t_data data, t_ray *ray, double ray_angle, int dof)
{
	int	mx;
	int	my;
	int	mp;

	if (ray_angle == 0 || ray_angle == M_PI)
	{
		ray->rx = data.player.pos_x;
		ray->ry = data.player.pos_y;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = ((int)(ray->rx) >> 6);
		my = ((int)(ray->ry) >> 6);
		mp = (mx * mapX + my);
		(void)mp;
		if (mx >= 0 && mx < 10 && my < 10 && my >= 0 && map[my][mx] == '1')
			dof = 8;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			dof += 1;
		}
	}
}

void	check_horizontal(t_data data, t_ray *ray, double ray_angle)
{
	double	a_tan;
	int		dof;

	a_tan = -1 / tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI)
	{
		ray->ry = (((int)data.player.pos_y >> 6) << 6) - 0.0001;
		ray->rx = ((data.player.pos_y) - (ray->ry)) * a_tan + data.player.pos_x;
		ray->yo = -mapS;
		ray->xo = -(ray->yo) * a_tan;
	}
	if (ray_angle < M_PI)
	{
		ray->ry = (((int)data.player.pos_y >> 6) << 6) + 64;
		ray->rx = ((data.player.pos_y) - ray->ry) * a_tan + data.player.pos_x;
		ray->yo = mapS;
		ray->xo = -(ray->yo) * a_tan;
	}
	final_check(data, ray, ray_angle, dof);
}

void	check_vertical(t_data data, t_ray *ray, double ray_angle)
{
	double	n_tan;
	int		dof;

	n_tan = -tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
	{
		ray->rx = (((int)data.player.pos_x >> 6) << 6) - 0.0001;
		ray->ry = ((data.player.pos_x) - ray->rx) * n_tan + data.player.pos_y;
		ray->xo = -CELL_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
	{
		ray->rx = (((int)data.player.pos_x >> 6) << 6) + CELL_SIZE;
		ray->ry = ((data.player.pos_x) - ray->rx) * n_tan + data.player.pos_y;
		ray->xo = CELL_SIZE;
		ray->yo = -(ray->xo) * n_tan;
	}
	final_check(data, ray, ray_angle, dof);
}

double	fisheyes_fix(double ca)
{
	if (ca < 0)
		ca += 2 * M_PI;
	if (ca > 0)
		ca -= 2 * M_PI;
	return (ca);
}

double	dist_calc(double x1, double x2, double t1, double t2)
{
	double	prod_1;
	double	prod_2;

	prod_1 = x1 - t1;
	prod_2 = x2 - t2;
	return (sqrt((prod_1 * prod_1) + (prod_2 * prod_2)));
}

t_ray	select_ray(t_data data, t_ray vert, t_ray horiz, double ca)
{
	double	vert_dist;
	double	horiz_dist;
	t_ray	selected;

	vert_dist = dist_calc(vert.rx, vert.ry, \
						data.player.pos_x, data.player.pos_y);
	horiz_dist = dist_calc(horiz.rx, horiz.ry, \
						data.player.pos_x, data.player.pos_y);
	selected.rx = 0;
	selected.ry = 0;
	selected.dist = 0;
	if (horiz_dist < vert_dist)
	{
		selected.rx = horiz.rx;
		selected.ry = horiz.ry;
		selected.dist = horiz_dist * cos(fisheyes_fix(ca));
	}
	else if (vert_dist <= horiz_dist)
	{
		selected.rx = vert.rx;
		selected.ry = vert.ry;
		selected.dist = vert_dist * cos(fisheyes_fix(ca));
	}
	return (selected);
}
