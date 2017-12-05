#include "wolf.h"

void	hero(t_env *e)
{
	int		size;

	size = -3;
	while (++size < 3)
	{
		put_pixel(e->h.x * e->m.size + e->m.offx + size,
				e->h.y * e->m.size + e->m.offy, 0xff66cc, e);
		put_pixel(e->h.x * e->m.size + e->m.offx,
				e->h.y * e->m.size + e->m.offy + size, 0xff66cc, e);
	}
}

void	minimap(t_env *e)
{
	int		i;
	int		k;

	i = -1;
	k = -1;
	while (++i < e->m.height)
	{
		while (++k < e->m.width)
		{
			if (e->m.tab[i][k] == 1)
				put_pixel(i * e->m.size + e->m.offx,
						k * e->m.size + e->m.offy, 0x00ff00, e);
			else if (e->m.tab[i][k] == 2)
				put_pixel(i * e->m.size + e->m.offx,
						k * e->m.size + e->m.offy, 0x0000ff, e);
			else if (e->m.tab[i][k] == 3)
				put_pixel(i * e->m.size + e->m.offx,
						k * e->m.size + e->m.offy, 0xff0f0f, e);
			else if (e->m.tab[i][k] == 4)
				put_pixel(i * e->m.size + e->m.offx,
						k * e->m.size + e->m.offy, 0x000fff, e);
		}
		k = -1;
	}
	hero(e);
}
