#include "wolf.h"

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
