
# include "../includes/cub3d.h"

void check_vertical(t_data data, double *rx, double *ry)
{
	double		ray_angle = data.player.pa;
	double		aTan;
	double		yo, xo;
	int			mp, mx, my, dof;

	aTan =  -1 / tan(ray_angle);
	dof = 0;
	if (ray_angle > M_PI)
	{
		*ry = (((int)data.player.pos_y >> 6) << 6) - 0.0001;
		*rx = ((data.player.pos_y) - *ry) * aTan + data.player.pos_x;
		yo = -CELL_SIZE;
		xo = -yo*aTan;
	}
	if (ray_angle < M_PI)
	{
		*ry = (((int)data.player.pos_y >> 6) << 6) + CELL_SIZE;
		*rx = ((data.player.pos_y) - *ry) * aTan + data.player.pos_x;
		yo = CELL_SIZE;
		xo = -yo*aTan;
	}
	if (ray_angle == 0 || ray_angle == M_PI)
	{
		*rx = data.player.pos_x;
		*ry = data.player.pos_y;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)(*rx) >> 6;
		my = (int)(*ry) >> 6;
		mp = mx * mapX + my;
		if (mp > 0 && mp < (mapX*mapY) && map[mp] == 1)
			dof = 8;
		else
		{
			*rx += xo;
			*ry += yo;
			dof += 1;
		}
	}
}