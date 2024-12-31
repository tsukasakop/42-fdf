/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:38:38 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 13:35:37 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	declare_globals(void)
{
	ft_set_global("mlx", NULL);
	ft_set_global("win", NULL);
	ft_set_global("img", NULL);
}

void	mlx_destroy(void)
{
	if (ft_get_global("mlx") && ft_get_global("win"))
		mlx_destroy_window(ft_get_global("mlx"), ft_get_global("win"));
	if (ft_get_global("mlx") && ft_get_global("img"))
		mlx_destroy_image(ft_get_global("mlx"), ft_get_global("img"));
	if (ft_get_global("mlx"))
		mlx_destroy_display(ft_get_global("mlx"));
	ft_delone_global("win", NULL);
	ft_delone_global("img", NULL);
	ft_delone_global("mlx", NULL);
}

void	error(const char *s)
{
	fprintf(stderr, "%s\n", s);
	ft_exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_model	*mdl;
	void	*mlx;
	void	*img;
	void	*win;

	declare_globals();
	ft_atexit(mlx_destroy);
	ft_atexit(ft_g_mmfree);
	if (argc != 2)
		error("invalid arguments");
	mdl = get_model(argv[1]);
	if (mdl == NULL)
		error("file read error");
	mlx = mlx_init();
	ft_set_global("mlx", mlx);
	img = model2image(mlx, mdl);
	ft_set_global("img", img);
	win = mlx_new_window(mlx, CANVAS_W, CANVAS_H, "fdf");
	ft_set_global("win", win);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	add_hooks(win);
	mlx_loop(mlx);
	ft_exit(EXIT_SUCCESS);
}
