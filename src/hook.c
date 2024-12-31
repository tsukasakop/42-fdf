/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:40:16 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 12:48:55 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/keysym.h>
#include <ft_stdlib.h>
#include <stdlib.h>
#include <mlx.h>

int	key_hook_esc(int keycode)
{
	if (keycode == XK_Escape)
		ft_exit(EXIT_SUCCESS);
	return (0);
}

int	btn_hook_cross(void)
{
	ft_exit(EXIT_SUCCESS);
	return (0);
}

void	add_hooks(void *win)
{
	mlx_key_hook(win, key_hook_esc, NULL);
	mlx_hook(win, DestroyNotify, NoEventMask, btn_hook_cross, NULL);
}
