#include "wolf.h"

int		move(t_env *e)
{
	movup(e);
	movdown(e);
	movleft(e);
	movright(e);
	draw(e);
	return (0);
}

void	movdown(t_env *e)
{
	if (e->h.mov & MOVDOWN)
	{
		if (!(e->m.tab[(int)(e->h.x - e->h.dir.x * MOVSPEED)]
			[(int)e->h.y]))
			e->h.x -= e->h.dir.x * MOVSPEED;

		if (!(e->m.tab[(int)e->h.x][(int)(e->h.y - e->h.dir.y * MOVSPEED)]))
			e->h.y -= e->h.dir.y * MOVSPEED;
	}
}

void	movup(t_env *e)
{
	if (e->h.mov & MOVUP)
	{

		if ((!(e->m.tab[(int)(e->h.x + e->h.dir.x * MOVSPEED)]
			[(int)e->h.y])))
			e->h.x += e->h.dir.x * MOVSPEED;
		if (!(e->m.tab[(int)e->h.x][(int)(e->h.y + e->h.dir.y * MOVSPEED)]))
			e->h.y += e->h.dir.y * MOVSPEED;
	}
}

void	movleft(t_env *e)
{
	if (e->h.mov & MOVLEFT)
	{
		float	oldirx;
		float	oldplanex;

		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x * cos(-ROTSPEED) - e->h.dir.y * sin(-ROTSPEED);
		e->h.dir.y = oldirx * sin(-ROTSPEED) + e->h.dir.y * cos(-ROTSPEED);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x * cos(-ROTSPEED) - e->plane.y * sin(-ROTSPEED);
		e->plane.y = oldplanex * sin(-ROTSPEED) + e->plane.y * cos(-ROTSPEED);
	}
}

void	movright(t_env *e)
{
	if (e->h.mov & MOVRIGHT)
	{
		float	oldirx;
		float	oldplanex;

		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x * cos(ROTSPEED) - e->h.dir.y * sin(ROTSPEED);
		e->h.dir.y = oldirx * sin(ROTSPEED) + e->h.dir.y * cos(ROTSPEED);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x * cos(ROTSPEED) - e->plane.y * sin(ROTSPEED);
		e->plane.y = oldplanex * sin(ROTSPEED) + e->plane.y * cos(ROTSPEED);
	}
}

int		set_mov(int keycode, t_env *e)
{
	if (keycode == KEY_UP)
		e->h.mov ^=  MOVUP;
	if (keycode == KEY_DOWN)
		e->h.mov ^=  MOVDOWN;
	if (keycode == KEY_LEFT)
		e->h.mov ^=  MOVLEFT;
	if (keycode == KEY_RIGHT)
		e->h.mov ^=  MOVRIGHT;
	return (0);
}
