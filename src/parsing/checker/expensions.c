#include "cub3d.h"

void	zero_expension(char **map, int x, int y)
{
	if (map[y] && map[y][x] && (map[y][x] == '1' || map[y][x] == 'X'))
		return ;
	else if (map[y][x] == 32 || map[y][x] == '\n')
	{
		errno = 4;
		return ;
	}
	map[y][x] = 'X';
	if (map[y] && map[y][x + 1])
		zero_expension(map, x + 1, y);
	if (map[y + 1])
		zero_expension(map, x, y + 1);
	if (map[y] && x - 1 >= 0 && map[y][x - 1])
		zero_expension(map, x - 1, y);
	if (y - 1 >= 0 && map[y - 1])
		zero_expension(map, x, y - 1);
}

void	one_expension(char **map, int x, int y)
{
	if (map[y] && map[y][x] && (map[y][x] == 'Z'
			|| map[y][x] == 32 || map[y][x] == '\n'))
		return ;
	map[y][x] = 'Z';
	if (map[y] && map[y][x + 1])
		one_expension(map, x + 1, y);
	if (map[y + 1])
		one_expension(map, x, y + 1);
	if (map[y] && x - 1>= 0 && map[y][x - 1])
		one_expension(map, x - 1, y);
	if (y - 1 >= 0 && map[y - 1])
		one_expension(map, x, y - 1);
}