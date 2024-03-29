
#include "../headers/cub3d.h"

void	check_vertical(t_player player, t_ray *ray, double ray_angle);
void	check_horizontal(t_player player, t_ray *ray, double ray_angle);
t_ray	select_ray(t_player player, t_ray vert, t_ray horiz, double angle);
void	draw_line(t_mlx *mlx, double xo, double yo, double angle);
void	raycast(t_player player, t_ray *selected)
{
	t_ray	horiz;
	t_ray	vert;
	double	angle;
	size_t	i;

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

void	final_check(t_player player, t_ray *ray, int dof)
{
	int	mx;
	int	my;

	ray->hit = false;
	while (dof < 168)
	{
		mx = ((int)(ray->rx) >> 6);
		my = ((int)(ray->ry) >> 6);
		if (mx >= 0 && mx < player.width_map && my < player.high_map && my >= 0 && player.map[my][mx] == '1')
		{
			ray->hit = true;
			dof = 168;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			dof += 1;
		}
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
		ray->ry = (((int)player.pos_y >> 6) << 6) - 0.0001;
		ray->rx = ((player.pos_y) - (ray->ry)) * a_tan + player.pos_x;
		ray->yo = -CELL_SIZE;
		ray->xo = -(ray->yo) * a_tan;
	}
	if (ray_angle < M_PI)
	{
		ray->ry = (((int)player.pos_y >> 6) << 6) + 64;
		ray->rx = ((player.pos_y) - ray->ry) * a_tan + player.pos_x;
		ray->yo = CELL_SIZE;
		ray->xo = -(ray->yo) * a_tan;
	}
	final_check(player, ray, dof);
}

void	check_vertical(t_player player, t_ray *ray, double ray_angle)
{
	double	n_tan;
	int		dof;

	n_tan = -tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
	{
		ray->rx = (((int)player.pos_x >> 6) << 6) - 0.0001;
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
	final_check(player, ray, dof);
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

t_ray	select_ray(t_player player, t_ray vert, t_ray horiz, double ca)
{
	double	vert_dist;
	double	horiz_dist;
	t_ray	selected;

	vert_dist = dist_calc(vert.rx, vert.ry, \
						player.pos_x, player.pos_y);
	horiz_dist = dist_calc(horiz.rx, horiz.ry, \
						player.pos_x, player.pos_y);
	selected.rx = 0;
	selected.ry = 0;
	selected.dist = 0;
	if (horiz.hit && !vert.hit)
	{	selected.rx = horiz.rx;
		selected.ry = horiz.ry;
		selected.dist = horiz_dist * cos(fisheyes_fix(ca));
		selected.hit = horiz.hit;
		return (selected);
	}
	if (vert.hit && !horiz.hit)
	{
		selected.rx = vert.rx;
		selected.ry = vert.ry;
		selected.dist = vert_dist * cos(fisheyes_fix(ca));
		selected.hit = vert.hit;
		return (selected);
	}
	if (horiz_dist < vert_dist)
	{
		selected.rx = horiz.rx;
		selected.ry = horiz.ry;
		selected.dist = horiz_dist * cos(fisheyes_fix(ca));
		selected.hit = horiz.hit;
		return (selected);
	}
	selected.rx = vert.rx;
	selected.ry = vert.ry;
	selected.dist = vert_dist * cos(fisheyes_fix(ca));
	selected.hit = vert.hit;
	return (selected);
}
