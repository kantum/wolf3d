#include "wolf.h"

int		move(int keycode, t_env *e)
{
	if (keycode == KEY_DOWN)
	{
		if ((e->h.x - e->h.dir.x * MOVSPEED) <= e->m.width &&
			e->h.x - e->h.dir.x * MOVSPEED >= 0)
			e->h.x -= e->h.dir.x * MOVSPEED;
		if ((e->h.y - e->h.dir.y * MOVSPEED) <= e->m.height &&
			e->h.y - e->h.dir.y * MOVSPEED >= 0)
			e->h.y -= e->h.dir.y * MOVSPEED;
	}
	if (keycode == KEY_UP)
	{

		if ((e->h.x + e->h.dir.x * MOVSPEED) <= e->m.width &&
			e->h.x + e->h.dir.x * MOVSPEED >= 0)
			e->h.x += e->h.dir.x * MOVSPEED;
		if ((e->h.y + e->h.dir.y * MOVSPEED) < e->m.height &&
			e->h.y + e->h.dir.y * MOVSPEED >= 0)
			e->h.y += e->h.dir.y * MOVSPEED;
	}
	if (keycode == KEY_LEFT)
	{
		float	oldirx;
		float	oldplanex;

		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x *
			cos(-ROTSPEED) - e->h.dir.y * sin(-ROTSPEED);
		e->h.dir.y = oldirx *
			sin(-ROTSPEED) + e->h.dir.y * cos(-ROTSPEED);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x *
			cos(-ROTSPEED) - e->plane.y * sin(-ROTSPEED);
		e->plane.y = oldplanex *
			sin(-ROTSPEED) + e->plane.y * cos(-ROTSPEED);
	}
	if (keycode == KEY_RIGHT)
	{
		float	oldirx;
		float	oldplanex;

		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x *
			cos(ROTSPEED) - e->h.dir.y * sin(ROTSPEED);
		e->h.dir.y = oldirx *
			sin(ROTSPEED) + e->h.dir.y * cos(ROTSPEED);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x *
			cos(ROTSPEED) - e->plane.y * sin(ROTSPEED);
		e->plane.y = oldplanex *
			sin(ROTSPEED) + e->plane.y * cos(ROTSPEED);
	}
	draw(e);
	return (0);
}
