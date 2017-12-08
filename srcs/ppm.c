#include "wolf.h"

unsigned int		*ppm_to_array(char *path, t_env *e)
{
	t_ppm	file;
	int		fd;
	int		i;
	char	*line;

	if (!(fd = open(path, O_RDONLY)))
		error(e, OPEN_ERR);

	get_next_line(fd, &line);
	file.type = ft_strdup(line);
	free(line);
	get_next_line(fd, &line);
	i = 0;
	file.width = ft_atoi(&line[i]);
	while(ft_isdigit((int)&line[i]))
		i++;
	file.height = ft_atoi(&line[i]);
	free(line);
	get_next_line(fd, &line);
	if (ft_atoi(line) != 255)
		error(e, TEXTURE_ERR);
	free(line);
	get_next_line(fd, &line);
	return ((unsigned int*)line);
}

int					*ppm_to_array2(char *path, t_env *e)
{
	char	*buf;
	char	*ret;
	int		i;
	int		j;

	buf = (char*)ppm_to_array(path, e);
	i = -1;
	j = -1;
	j = -1;
	ret = malloc(sizeof(char *) * MAX_IMG_SIZE);
	while (buf[++i])
	{
		if (i % 3)
				ret[++j] = 0;
		else
			ret[++j] = buf[++i];
	}
	j = -1;
	free(buf);
	return ((int*)ret);
}
