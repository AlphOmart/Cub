
# include "../includes/cub3d.h"

void	check_vertical(t_data data, t_ray *ray, double ray_angle);
void	check_horizontal(t_data data, t_ray *ray, double ray_angle);
void	select_ray(t_player player, t_ray vert, t_ray horiz, double def[2]);

void	raycast(t_data data)
{
	t_ray	horiz;
	double	def_inter[2];
	double	angle;
	t_ray	vert;
	size_t	i;

	angle =((data.player.pa * 180) / M_PI) - (data.player.fov * 0.5);
	angle = fmod((fmod(angle, 360) + 360), 360);
	angle = angle * M_PI / 180;
	i = 0;
	while (i < 1280)
	{
		check_vertical(data, &vert, angle);
		check_horizontal(data, &horiz, angle);
		select_ray(data.player, vert, horiz, def_inter);
		draw_line(data, def_inter[0], def_inter[1], angle);
		//draw_line(data, horiz.rx, horiz.ry, angle);
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
		if (mx >= 0 && mx < 10 && my < 10 && my>=0 && map[my][mx] == '1')
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

	a_tan = - 1 / tan(ray_angle);
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

void	select_ray(t_player player, t_ray vert, t_ray horiz, double def[2])
{
	double	vert_dist;
	double	horiz_dist;
	double	prod1;
	double	prod2;

	prod1 = vert.rx - player.pos_x;
	prod2 = vert.ry - player.pos_y;

	vert_dist = sqrt((prod1 * prod1) + (prod2 * prod2));
	prod1 = horiz.rx - player.pos_x;
	prod2 = horiz.ry - player.pos_y;
	horiz_dist = sqrt((prod1 * prod1) + (prod2 * prod2));
	if (horiz_dist < vert_dist)
	{
		def[0] = horiz.rx;
		def[1] = horiz.ry;
		return ;
	}
	else if (vert_dist < horiz_dist)
	{
		def[0] = vert.rx;
		def[1] = vert.ry;
		return;
	}
}
