/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:34:57 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:34:57 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		place_hero(t_env *e)
{
	int	i;
	int	k;

	i = -1;
	while (++i < e->m.height)
	{
		k = -1;
		while (++k < e->m.width)
		{
			if (e->m.tab[i][k] < 0 || e->m.tab[i][k] > 9)
			{
				if ((e->m.tab[i][k] == 'x' - '0') ||
					(e->m.tab[i][k] == 'X' - '0'))
				{
					e->h.x = i + 0.5;
					e->h.y = k + 0.5;
					e->m.tab[i][k] = 0;
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

void	cross(int x, int y, int color, t_env *e)
{
	int start;

	start = -e->m.size / 2;
	while (++start < e->m.size / 2)
	{
		if (y * e->m.size + start >= 0 &&
				y * e->m.size + start <= e->m.size * e->m.height - e->m.size)
			put_pixel(y * e->m.size + e->m.offx + start,
					x * e->m.size + e->m.offy, color, e);
		if (x * e->m.size + start >= 0 &&
				x * e->m.size + start <= e->m.size * e->m.width - e->m.size)
			put_pixel(y * e->m.size + e->m.offx,
					x * e->m.size + e->m.offy + start, color, e);
	}
}

void	color_map(int x, int y, t_env *e)
{
	if (e->m.tab[y][x] == 0)
		cross(x, y, 0x333e62, e);
	if (e->m.tab[y][x] == 1)
		cross(x, y, 0xff00ff, e);
	else if (e->m.tab[y][x] == 2)
		cross(x, y, 0x00ff00, e);
	else if (e->m.tab[y][x] >= 3)
		cross(x, y, 0x0000ff, e);
	else if (e->m.tab[y][x] == 4)
		cross(x, y, 0xff0000, e);
}

void	minimap(t_env *e)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	e->m.tab2 = (t_point*)malloc(sizeof(t_point) * e->m.height * e->m.width);
	while (++y <= e->m.width * e->m.size)
	{
		while (++x <= e->m.height * e->m.size)
			put_pixel(x + e->m.offx - e->m.size / 2,
					y + e->m.offy - e->m.size / 2, BLACK, e);
		x = -1;
	}
	y = -1;
	x = -1;
	while (++y < e->m.height)
	{
		while (++x < e->m.width)
		{
			e->m.tab2[y * e->m.width + x].x = x * e->m.size + e->m.offx;
			e->m.tab2[y * e->m.width + x].y = y * e->m.size + e->m.offy;
			color_map(x, y, e);
		}
		x = -1;
	}
}
