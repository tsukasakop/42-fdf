/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:23:30 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 12:56:51 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	search_limit(t_pixel *px)
{
	t_norm	*n;

	n = (t_norm *)ft_get_global("norm");
	if (px->x > n->max[0])
		n->max[0] = px->x;
	if (px->y > n->max[1])
		n->max[1] = px->y;
	if (px->x < n->min[0])
		n->min[0] = px->x;
	if (px->y < n->min[1])
		n->min[1] = px->y;
}

void	norm_pixel(t_pixel *px)
{
	t_norm	*n;

	(void)px;
	n = (t_norm *)ft_get_global("norm");
	scale_pixel(px, n->scale[0], n->scale[1]);
	move_pixel(px, n->move[0], n->move[1]);
}

void	norm_map(t_pixel ***map)
{
	t_norm	n;

	n = (t_norm){{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}, {0.0, 0.0}, {0, 0}};
	ft_set_global("norm", &n);
	map_iter(map, search_limit);
	n.scale[0] = (double)(CANVAS_W - 1) / (n.max[0] - n.min[0]);
	n.scale[1] = (double)(CANVAS_H - 1) / (n.max[1] - n.min[1]);
	if (n.scale[0] < n.scale[1])
		n.scale[1] = n.scale[0];
	else
		n.scale[0] = n.scale[1];
	n.move[0] = round(n.scale[0] * -0.5 * (n.max[0] + n.min[0])) + CANVAS_W / 2;
	n.move[1] = round(n.scale[1] * -0.5 * (n.max[1] + n.min[1])) + CANVAS_H / 2;
	map_iter(map, norm_pixel);
	ft_delone_global("norm", NULL);
}
