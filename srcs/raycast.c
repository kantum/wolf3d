/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:35:01 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:35:01 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	dda1(t_env *e)
{
	if (e->r.dirx < 0)
	{
		e->r.stepx = -1;
		e->r.sidedistx = (e->r.posx - e->r.mapx) * e->r.deltadistx;
	}
	else
	{
		e->r.stepx = 1;
		e->r.sidedistx = (e->r.mapx + 1.0 - e->r.posx) *
			e->r.deltadistx;
	}
	if (e->r.diry < 0)
	{
		e->r.stepy = -1;
		e->r.sidedisty = (e->r.posy - e->r.mapy) * e->r.deltadisty;
	}
	else
	{
		e->r.stepy = 1;
		e->r.sidedisty = (e->r.mapy + 1.0 - e->r.posy) *
			e->r.deltadisty;
	}
}

void	dda2(t_env *e)
{
	while (e->r.hit == 0)
	{
		if (e->r.sidedistx < e->r.sidedisty)
		{
			e->r.sidedistx += e->r.deltadistx;
			e->r.mapx += e->r.stepx;
			e->r.side = 0;
		}
		else
		{
			e->r.sidedisty += e->r.deltadisty;
			e->r.mapy += e->r.stepy;
			e->r.side = 1;
		}
		if (e->m.tab[e->r.mapx][e->r.mapy] > 0)
			e->r.hit = 1;
	}
	if (e->r.side == 0)
		e->r.walldist = (e->r.mapx - e->r.posx + (1 - e->r.stepx) / 2)
			/ e->r.dirx;
	else
		e->r.walldist = (e->r.mapy - e->r.posy + (1 - e->r.stepy) / 2)
			/ e->r.diry;
}

void	walls(t_env *e)
{
	e->r.lineh = (int)(HEIGHT / e->r.walldist);
	e->r.drawstart = -e->r.lineh / 2 + HEIGHT / 2;
	if (e->r.drawstart < 0)
		e->r.drawstart = 0;
	e->r.drawend = e->r.lineh / 2 + HEIGHT / 2;
	if (e->r.drawend >= HEIGHT)
		e->r.drawend = HEIGHT - 1;
}

void	raycast(t_env *e)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		e->r.camerax = 2 * x / (double)(WIDTH) - 1;
		e->r.posx = e->h.x;
		e->r.posy = e->h.y;
		e->r.dirx = e->h.dir.x + e->plane.x * e->r.camerax;
		e->r.diry = e->h.dir.y + e->plane.y * e->r.camerax;
		e->r.mapx = (int)(e->r.posx);
		e->r.mapy = (int)(e->r.posy);
		e->r.deltadistx = sqrt(1 + (e->r.diry * e->r.diry) /
			(e->r.dirx * e->r.dirx));
		e->r.deltadisty = sqrt(1 + (e->r.dirx * e->r.dirx) /
			(e->r.diry * e->r.diry));
		e->r.hit = 0;
		dda1(e);
		dda2(e);
		walls(e);
		textures(x, e);
	}
}
