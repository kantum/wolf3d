#include "wolf.h"

void	trace_tex(int x, t_env *e)
{
	int	y;
	long int	d;
	int	col;

	y = e->r.drawstart;
	while (y < e->r.drawend)
	{
		d = y * 256 - HEIGHT * 128 + e->r.lineh * 128;
		e->r.texy = ((d * e->r.texh) / e->r.lineh) / 256;
		col = (int)(e->r.texture[e->r.texnum][e->r.texw * e->r.texy + e->r.texx]);
		if (e->r.side == 1) col = (col >> 1) & 0x7F7F7F;
		put_pixel(x, y, col, e);
		y++;
	}
}

void	texture(int x, t_env *e)
{
	e->texsize = 128;
	e->r.texw = e->texsize;
	e->r.texh = e->texsize;
	e->r.texnum = e->m.tab[e->r.mapx][e->r.mapy] - 1;
	if (e->r.side == 0)
		e->r.wallx = e->r.posy + e->r.walldist * e->r.diry;
	else
		e->r.wallx = e->r.posx + e->r.walldist * e->r.dirx;
	e->r.wallx -= floor(e->r.wallx);
	e->r.texx = (int)(e->r.wallx * (double)(e->r.texw));
	if ((e->r.side == 0 && e->r.dirx > 0) || (e->r.side == 1 && e->r.diry < 0))
		e->r.texx = e->r.texw - e->r.texx - 1;
	trace_tex(x, e);
}
