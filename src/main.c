//usr/bin/cc $0 -Iinclude -L. -lm -lmlx_Linux -lmlx -lXext -lX11 -o a.out && ./a.out; exit;
//#include <mlx.h>

#include <stdlib.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ft_global.h"
#include "fdf.h"
#include "mlx.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <ft_stdlib.h>

#include <math.h>


void error(const char *s)
{
	fprintf(stderr, "%s\n", s);
	ft_exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	t_model	*mdl;
	void *mlx;
	void *img;
	void *win;

	ft_atexit(ft_g_mmfree);
	PRINT("Start:\n");
	PRINT(" - canvas(width: %d, height: %d, lsize: %#lx)\n", CANVAS_W, CANVAS_H, (size_t)4 * CANVAS_W * CANVAS_H);
	if(argc !=2)
		error("invalid arguments");
	mlx = mlx_init();
	mdl = get_model(argv[1]);
	if(mdl == NULL)
		error("read model error");
	//PRINT("- max_x: %lu, max_y: %lu\n", mdl->x_len, mdl->y_len);
	//PRINT("- max_x: %lu, max_y: %lu\n", max_x(mdl), max_y(mdl));
	img = model2image(mlx, mdl);
	win = mlx_new_window(mlx, CANVAS_W, CANVAS_H, "fdf");
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	add_hooks(win);
	mlx_loop(mlx);
	ft_exit(EXIT_SUCCESS);
}


