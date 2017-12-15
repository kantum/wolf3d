/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:58 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:58 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		move(t_env *e)
{
	movupdown(e);
	movleft(e);
	movright(e);
	draw(e);
	return (0);
}

void	movupdown(t_env *e)
{
	if (e->flags & FAST)
		e->h.speed = 0.2;
	else
		e->h.speed = 0.07;
	if (e->h.mov & MOVDOWN)
	{
		if (!(e->m.tab[(int)(e->h.x - e->h.dir.x * e->h.speed)]
			[(int)e->h.y]))
			e->h.x -= e->h.dir.x * e->h.speed;
		if (!(e->m.tab[(int)e->h.x][(int)(e->h.y - e->h.dir.y * e->h.speed)]))
			e->h.y -= e->h.dir.y * e->h.speed;
	}
	if (e->h.mov & MOVUP)
	{
		if ((!(e->m.tab[(int)(e->h.x + (e->h.dir.x * 3) * e->h.speed)]
			[(int)e->h.y])))
			e->h.x += e->h.dir.x * e->h.speed;
		if (!(e->m.tab[(int)e->h.x]
					[(int)(e->h.y + (e->h.dir.y * 3) * e->h.speed)]))
			e->h.y += e->h.dir.y * e->h.speed;
	}
}

void	movleft(t_env *e)
{
	double	oldirx;
	double	oldplanex;

	if (e->h.mov & MOVLEFT)
	{
		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x * cos(-e->h.rotspeed) -
			e->h.dir.y * sin(-e->h.rotspeed);
		e->h.dir.y = oldirx * sin(-e->h.rotspeed) +
			e->h.dir.y * cos(-e->h.rotspeed);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x * cos(-e->h.rotspeed) -
			e->plane.y * sin(-e->h.rotspeed);
		e->plane.y = oldplanex * sin(-e->h.rotspeed) +
			e->plane.y * cos(-e->h.rotspeed);
	}
}

void	movright(t_env *e)
{
	double	oldirx;
	double	oldplanex;

	if (e->h.mov & MOVRIGHT)
	{
		oldirx = e->h.dir.x;
		e->h.dir.x = e->h.dir.x * cos(e->h.rotspeed) -
			e->h.dir.y * sin(e->h.rotspeed);
		e->h.dir.y = oldirx * sin(e->h.rotspeed) +
			e->h.dir.y * cos(e->h.rotspeed);
		oldplanex = e->plane.x;
		e->plane.x = e->plane.x * cos(e->h.rotspeed) -
			e->plane.y * sin(e->h.rotspeed);
		e->plane.y = oldplanex * sin(e->h.rotspeed) +
			e->plane.y * cos(e->h.rotspeed);
	}
}

int		set_mov(int keycode, t_env *e)
{
	if (keycode == KEY_UP)
		e->h.mov ^= MOVUP;
	if (keycode == KEY_DOWN)
		e->h.mov ^= MOVDOWN;
	if (keycode == KEY_LEFT)
		e->h.mov ^= MOVLEFT;
	if (keycode == KEY_RIGHT)
		e->h.mov ^= MOVRIGHT;
	return (0);
}
