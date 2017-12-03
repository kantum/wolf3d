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
	return (0);
}

int		key_release(int keycode, t_env *e)
{
	if (keycode == KEY_DOWN || keycode == KEY_UP ||
		keycode == KEY_LEFT || keycode == KEY_RIGHT)
		set_mov(keycode, e);
	move(e);
	return(0);
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

