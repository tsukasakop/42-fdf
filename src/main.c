/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:38:38 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/29 16:38:46 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	ft_atexit(ft_g_mmfree);
	if (argc != 2)
		error("invalid arguments");
	mlx = mlx_init();
	mdl = get_model(argv[1]);
	if (mdl == NULL)
		error("read model error");
	img = model2image(mlx, mdl);
	win = mlx_new_window(mlx, CANVAS_W, CANVAS_H, "fdf");
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	add_hooks(win);
	mlx_loop(mlx);
	ft_exit(EXIT_SUCCESS);
}
