#include "fdf.h"
#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <ft_stdlib.h>

int key_hook_esc(int keycode)
{
	if (keycode == XK_Escape)
		ft_exit(0);
	PRINT("%#x\n", keycode);
	return 0;
}

int btn_hook_cross()
{
	ft_exit(0);
	return 0;
}

void add_hooks(void *win)
{
	mlx_key_hook(win, key_hook_esc, NULL);
	mlx_hook(win, DestroyNotify, NoEventMask, btn_hook_cross, NULL);
}
