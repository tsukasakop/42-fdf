#include <stdlib.h>
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#include <stdio.h>
#define PRINT(...) printf(__VA_ARGS__)

int key_hook_esc(int keycode)
{
	if (keycode == XK_Escape)
		exit(0);
	PRINT("%#x\n", keycode);
	return 0;
}

int btn_hook_cross()
{
	exit(0);
}

int main()
{
	void *mlx;
	void *win;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 100, 100, "aiueo");
	mlx_key_hook(win, key_hook_esc, NULL);
	mlx_hook(win, DestroyNotify, NoEventMask, btn_hook_cross, NULL);
	mlx_loop(mlx);
}
