//usr/bin/cc $0 -L. -lm -lmlx_Linux -lmlx -lXext -lX11 -o a.out && ./a.out; exit;
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	void*p, *w;
	p=mlx_init();
	w=mlx_new_window(p,500,500,"new win");
	mlx_pixel_put(p, w, 250, 250, 0x808080);
	mlx_loop(p);
}
