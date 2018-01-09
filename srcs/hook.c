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
	else if (keycode == KEY_M)
		e->flags ^= MAP;
	else if (keycode == KEY_SHIFT_LEFT)
		e->flags ^= FAST;
	else if (keycode == KEY_0 || keycode == KEY_1 || keycode == KEY_2 ||
		keycode == KEY_3 || keycode == KEY_4 || keycode == KEY_5 ||
		keycode == KEY_6 || keycode == KEY_7 || keycode == KEY_8)
		background(keycode, e);
	else if (keycode == KEY_SPACEBAR)
		e->flags ^= SHOT;
	else if (keycode == KEY_MINUS)
		e->m.size -= 0.15;
	else if (keycode == KEY_EQUAL)
		e->m.size += 0.15;
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
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
