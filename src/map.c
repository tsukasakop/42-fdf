#include "fdf.h"

size_t	get_max_y(t_pixel ***m)
{
	size_t c;

	c = 0;
	while(m[c])
		c++;
	return c;
}

size_t	get_max_x(t_pixel ***m)
{
	size_t c;

	if(m[0] == NULL)
		return 0;
	c = 0;
	while(m[0][c])
		c++;
	return c;
}

void	set_pixel(t_pixel ***m, size_t x, size_t y, t_pixel *px)
{
	m[y][x] = px;
}

t_pixel	***_map_new(size_t x, size_t y)
{
	PRINT("Making map\n");
	t_pixel ***map;
	map = ft_g_mmmalloc(sizeof(t_pixel **)*(y+1));
	size_t i;
	i=0;
	while(i < y)
	{
		map[i] = ft_g_mmmalloc(sizeof(t_pixel *)*(x+1));
		map[i][x] = NULL;
		i++;
	}
	map[y] = NULL;
	return map;
}

void    map_iter(t_pixel ***map, void(*f)(t_pixel *))
{
        size_t x;
        size_t y;
        size_t max_x;
        size_t max_y;

        y = 0;
        max_x = get_max_x(map);
        max_y = get_max_y(map);
        PRINT("- max_x: %lu, max_y: %lu\n", max_x, max_y);
        while (y < max_y)
        {
                x = 0;
                while(x < max_x)
                {
                        f(get_pixel(map, x, y));
                        x++;
                }
                y++;
        }
}

