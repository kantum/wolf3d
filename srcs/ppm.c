#include "wolf.h"

char		*ppm_to_array(char *path, t_env *e)
{
	int		fd;
	int		i;
	char	*line;

	if (!(fd = open(path, O_RDONLY)))
		error(e, OPEN_ERR);

	get_next_line(fd, &line);
	e->file.type = ft_strdup(line);
	free(line);
	get_next_line(fd, &line);
	i = 0;
	e->file.width = ft_atoi(&line[i]);
	while(ft_isdigit((int)&line[i]))
		i++;
	e->file.height = ft_atoi(&line[i]);
	free(line);
	get_next_line(fd, &line);
	if (ft_atoi(line) != 255)
		error(e, TEXTURE_ERR);
	free(line);
	get_next_line(fd, &line);
	return (line);
}

int					*ppm_to_array2(char *path, t_env *e)
{
	char	*buf;
	char	*ret;
	int		i;
	int		j;

	buf = ppm_to_array(path, e);
	i = 0;
	j = 0;
	ret = malloc(sizeof(char*) * (e->file.width * e->file.height) * 4);

	while (42)
	{
		if (buf[i] == 0)
			break;
		ret[j +3] = 0;
		ret[j+2] = buf[i];
		ret[j+1] = buf[i+1];
		ret[j] = buf[i+2];
		j += 4;
		i += 3;
	}
	free(buf);
	return ((int*)ret);
}
