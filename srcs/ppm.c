/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:35:00 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:35:00 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_rgb		*ppm_to_array(char *path, t_env *e)
{
	int		fd;
	int		i;
	char	*line;

	if (!(fd = open(path, O_RDONLY)))
		error(e, OPEN_ERR);
	if (get_next_line(fd, &line) < 1)
		error(e, TEXTURE_ERR);
	free(line);
	get_next_line(fd, &line);
	while (line[0] == '#')
	{
		free(line);
		get_next_line(fd, &line);
	}
	i = 0;
	e->file.width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	e->file.height = ft_atoi(&line[i]);
	free(line);
	get_next_line(fd, &line);
	free(line);
	get_next_line(fd, &line);
	return ((t_rgb*)line);
}

int			*ppm_to_array2(char *path, t_env *e)
{
	t_rgb	*buf;
	t_rgba	*ret;
	int		i;

	buf = ppm_to_array(path, e);
	i = -1;
	if (!(ret = malloc(sizeof(t_rgba) * (e->file.width * e->file.height))))
		return (NULL);
	while (++i < (e->file.width * e->file.height))
	{
		ret[i].r = buf[i].b;
		ret[i].g = buf[i].g;
		ret[i].b = buf[i].r;
		ret[i].a = 0;
	}
	free(buf);
	return ((int*)ret);
}
