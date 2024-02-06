#include "cub3d.h"

static bool	close_up(char *str);
static bool	close_down(char **cpy);
static bool	close_left(char **cpy);
static bool	close_right(char **cpy);

bool	is_close(char **cpy)
{
	int		start[2];

	start[0] = -1;
	start[1] = -1;
	get_pos(cpy, start);
	if (start[0] == -1 || start[1] == -1)
		return (errno = 4, false);
	cpy[start[0]][start[1]] = 'x';
	zero_expension(cpy, start[1], start[0]);
	int	i = -1;
	while(cpy[++i])
		printf("%s", cpy[i]);
	if (!close_up(cpy[0]) || !close_down(cpy) || !close_left(cpy) || !close_right(cpy))
		return (errno = 4, false);
	one_expension(cpy, start[1], start[0]);
	if(!is_block(cpy))
		return (errno = 4, false);
	return (true);
}

static bool	close_up(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'X')
			return (false);
		i++;
	}
	return (true);
}

static bool	close_down(char **cpy)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cpy[i])
		i++;
	i -= 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] == 'X')
			return (false);
		j++;
	}
	return (true);
}

static bool	close_left(char **cpy)
{
	size_t	j;

	j = 0;
	while (cpy[j])
	{
		if (cpy[j][0] == 'X')
			return (false);
		j++;
	}
	return (true);
}

static bool	close_right(char **cpy)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cpy[i])
	{
		j = ft_strlen(cpy[i]);
		while (j >= 0 && cpy[i] && cpy[i][j] && cpy[i][j] != 1)
		{
			if (cpy[i][j] == 'X')
				return (false);
			j--;
		}
		i++;
	}
	return (true);
}
