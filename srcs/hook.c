/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:17 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:22 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
	(void)e;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		loop_hook(t_env *e)
{
	move(e);
	return (0);
}

int		key_press(int keycode, t_env *e)
{
	if (keycode == KEY_ESCAPE || keycode == KEY_Q)
		quit(e);
	else if (keycode == KEY_DOWN || keycode == KEY_UP ||
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		set_mov(keycode, e);
	if (keycode == KEY_M)
		e->flags ^= MAP;
	if (keycode == KEY_SHIFT_LEFT)
		e->flags ^= FAST;
	if (keycode == KEY_0)
		e->background = "./images/background/fond.xpm";
	if (keycode == KEY_1)
		e->background = "./images/background/fond1.xpm";
	if (keycode == KEY_2)
		e->background = "./images/background/fond2.xpm";
	if (keycode == KEY_3)
		e->background = "./images/background/fond3.xpm";
	if (keycode == KEY_4)
		e->background = "./images/background/fond4.xpm";
	if (keycode == KEY_5)
		e->background = "./images/background/fond5.xpm";
	return (0);
}

int		key_release(int keycode, t_env *e)
{
	if (keycode == KEY_SHIFT_LEFT)
		e->flags ^= FAST;
	if (keycode == KEY_DOWN || keycode == KEY_UP ||
		keycode == KEY_LEFT || keycode == KEY_RIGHT)
		set_mov(keycode, e);
	move(e);
	return (0);
}

void	hooks(t_env *e)
{
	mlx_do_key_autorepeatoff(e->mlx);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, key_press, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, key_release, e);
	mlx_hook(e->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, quit, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
