/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:35:02 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:35:02 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	background(int keycode, t_env *e)
{
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
	if (keycode == KEY_6)
		e->background = "./images/background/fond6.xpm";
}

void	textures(int x, t_env *e)
{
	int			y;
	long int	d;
	int			col;

	e->r.texnum = e->m.tab[e->r.mapx][e->r.mapy] - 1;
	if (e->r.side == 0)
		e->r.wallx = e->r.posy + e->r.walldist * e->r.diry;
	else
		e->r.wallx = e->r.posx + e->r.walldist * e->r.dirx;
	e->r.wallx -= floor(e->r.wallx);
	e->r.texx = (int)(e->r.wallx * (double)(TEXWIDTH));
	if ((e->r.side == 0 && e->r.dirx > 0) || (e->r.side == 1 && e->r.diry < 0))
		e->r.texx = TEXWIDTH - e->r.texx - 1;
	y = e->r.drawstart;
	while (y < e->r.drawend)
	{
		d = y * 256 - HEIGHT * 128 + e->r.lineh * 128;
		e->r.texy = ((d * TEXHEIGHT) / e->r.lineh) / 256;
		col = e->r.texture[e->r.texnum]
			[TEXWIDTH * e->r.texy + e->r.texx];
		if (e->r.side == 1)
			col = (col >> 1) & 8355711;
		put_pixel(x, y, col, e);
		y++;
	}
}
