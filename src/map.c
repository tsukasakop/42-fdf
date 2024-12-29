/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:38:57 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/29 16:39:15 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_max_y(t_pixel ***m)
{
	size_t	c;

	c = 0;
	while (m[c])
		c++;
	return (c);
}

size_t	get_max_x(t_pixel ***m)
{
	size_t	c;

	if (m[0] == NULL)
		return (0);
	c = 0;
	while (m[0][c])
		c++;
	return (c);
}

void	set_pixel(t_pixel ***m, size_t x, size_t y, t_pixel *px)
{
	m[y][x] = px;
}

t_pixel	***_map_new(size_t x, size_t y)
{
	t_pixel	***map;
	size_t	i;

	map = ft_g_mmmalloc(sizeof(t_pixel **) * (y + 1));
	i = 0;
	while (i < y)
	{
		map[i] = ft_g_mmmalloc(sizeof(t_pixel *) * (x + 1));
		map[i][x] = NULL;
		i++;
	}
	map[y] = NULL;
	return (map);
}

void	map_iter(t_pixel ***map, void (*f)(t_pixel *))
{
	size_t	x;
	size_t	y;
	size_t	max_x;
	size_t	max_y;

	y = 0;
	max_x = get_max_x(map);
	max_y = get_max_y(map);
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			f(get_pixel(map, x, y));
			x++;
		}
		y++;
	}
}
