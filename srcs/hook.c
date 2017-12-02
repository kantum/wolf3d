#include "wolf.h"

int		mouse_hook(int button, int x, int y, t_env *e)
{
	(void)e;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ESCAPE || keycode == KEY_Q)
		quit(e);
	else if (keycode == KEY_DOWN || keycode == KEY_UP ||
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		move(keycode, e);
	return (0);
}

void	hooks(t_env *e)
{
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, key_hook, e);
	mlx_hook(e->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, quit, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_loop(e->mlx);
}

