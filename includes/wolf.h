# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"

# define mapWidth 24
# define mapHeight 24

# define WIDTH 1280
# define HEIGHT 800

# define KEYPRESS			2
# define KEYPRESSMASK		(1L<<0)
# define MOTIONNOTIFY		6
# define POINTERMOTIONMASK	(1L<<6)
# define BUTTONRELEASE		5
# define BUTTONRELEASEMASK	(1L<<3)
# define DESTROYNOTIFY		17
# define STRUCTURENOTIFYMASK	(1L<<17)

typedef struct			s_point
{
	int		x;
	int		y;
	int		color;
}						t_point;

typedef struct			s_env
{
	void		*mlx;
	void		*win;
	int			color;
	void		*img;
	int			*data;
	int			size;
	int			bpp;
	int			endian;
	t_point		p;
}						t_env;
