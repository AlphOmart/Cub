
# include "../includes/cub3d.h"

void check_vertical(t_data data, t_ray *ray, double ray_angle)
{;
	double		aTan;
	int			dof;

	aTan =  -1 / tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI)
	{
		ray->ry = (((int)data.player.pos_y >> 6) << 6) - 0.0001;
		ray->rx = ((data.player.pos_y) - ray->ry) * aTan + data.player.pos_x;
		ray->yo = -CELL_SIZE;
		ray->xo = -(ray->yo)*aTan;
	}
	if (ray_angle < M_PI)
	{
		ray->ry = (((int)data.player.pos_y >> 6) << 6) + CELL_SIZE;
		ray->rx = ((data.player.pos_y) - ray->ry) * aTan + data.player.pos_x;
		ray->yo = CELL_SIZE;
		ray->xo = -(ray->yo)*aTan;
	}
	if (ray_angle == 0 || ray_angle == M_PI)
	{
		ray->rx = data.player.pos_x;
		ray->ry = data.player.pos_y;
		dof = 8;
	}
	final_check(data, ray, ray_angle,dof);
}