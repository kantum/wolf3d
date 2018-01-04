/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdurot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 04:35:03 by qdurot            #+#    #+#             */
/*   Updated: 2017/12/10 04:35:03 by qdurot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "mlx_keys.h"
# include "libft.h"

# define NB_COLOR			6

# define WIDTH				1280
# define HEIGHT				720
# define MOVSPEED			0.07

# define MOVUP				1<<0
# define MOVDOWN			1<<1
# define MOVRIGHT			1<<2
# define MOVLEFT			1<<3

# define MAP				1<<0
# define HERO				1<<1
# define RADAR				1<<2
# define FAST				1<<3

# define GUN_1				1<<0
# define GUN_2				1<<1
# define GUN_3				1<<2

# define NB_TEXTURE			9
# define TEXWIDTH			512
# define TEXHEIGHT			512

# define NO_ARG				1
# define TEXTURE_ERR		2
# define OPEN_ERR			3
# define PARSE_ERR			4
# define MALLOC_ERR			5
# define BG_ERR				6
# define GUN_ERR			7
# define PPM_ERR			8

# define KEYPRESS			2
# define KEYRELEASE			3
# define KEYPRESSMASK		(1L<<0)
# define KEYRELEASEMASK		(1L<<1)
# define MOTIONNOTIFY		6
# define POINTERMOTIONMASK	(1L<<6)
# define BUTTONRELEASE		5
# define BUTTONRELEASEMASK	(1L<<3)
# define DESTROYNOTIFY		17
# define STRUCTURENOTIFYMASK	(1L<<17)

typedef struct			s_rgb
{
	char r;
	char g;
	char b;
}						t_rgb;

typedef struct			s_rgba
{
	char r;
	char g;
	char b;
	char a;
}						t_rgba;

typedef struct			s_ppm
{
	char	*type;
	int		width;
	int		height;
}						t_ppm;

typedef struct			s_point
{
	int		x;
	int		y;
	int		type;
	int		color;
}						t_point;

typedef struct			s_vect
{
	double	x;
	double	y;
}						t_vect;

typedef struct			s_hero
{
	double	x;
	double	y;
	t_vect	dir;
	short	mov;
	double	speed;
	double	rotspeed;
	char	*gun;
	char	*imgun;
	int		weapon;
}						t_hero;

typedef struct			s_map
{
	int		fd;
	int		width;
	int		height;
	int		offx;
	int		offy;
	int		size;
	char	*buf;
	t_point	*p;
	int		**tab;
	t_point	*tab2;
}						t_map;

typedef struct			s_rcast
{
	double		camerax;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		walldist;
	short		hit;
	short		side;
	short		stepx;
	short		stepy;
	int			lineh;
	int			drawstart;
	int			drawend;
	int			color[NB_COLOR];
	int			texnum;
	int			texsize;
	int			texbpp;
	void		*voidtex[NB_TEXTURE];
	int			*texture[NB_TEXTURE];
	double		wallx;
	int			texx;
	long int	texy;
	int			texw;
	int			texh;
}						t_rcast;

typedef struct			s_env
{
	void	*mlx;
	void	*win;
	int		color;
	void	*img;
	void	*img2;
	int		*data;
	int		size;
	int		texsize;
	int		bpp;
	int		texbpp;
	int		endian;
	int		texendian;
	int		width;
	int		height;
	t_point	p;
	t_map	m;
	t_hero	h;
	t_rcast	r;
	t_vect	plane;
	double	time;
	double	oldtime;
	double	frametime;
	int		flags;
	char	*background;

	t_ppm	file;
}						t_env;

t_env					*parse(char *arg, t_env *e);
int						quit(t_env *e);
int						mouse_hook(int button, int x, int y, t_env *e);
int						key_press(int keycode, t_env *e);
int						move(t_env *e);
void					scene(t_env *e);
void					minimap(t_env *e);
void					draw(t_env *e);
void					hero(t_env *e);
void					hooks(t_env *e);
int						key_release(int keycode, t_env *e);
int						set_mov(int keycode, t_env *e);
void					movupdown(t_env *e);
void					movleft(t_env *e);
void					movright(t_env *e);
int						init(t_env *e);
void					put_pixel(int x, int y, int color, t_env *e);
void					init_raycast(t_env *e);
void					dda1(t_env *e);
void					dda2(t_env *e);
void					raycast(t_env *e);
void					error(t_env *e, int err);
void					textures(int x, t_env *e);
void					bresenham(t_point a, t_point b, t_env *e);
t_rgb					*ppm_to_array2(char *path, t_env *e);
int						*ppm_to_array(char *path, t_env *e);
int						place_hero(t_env *e);
void					free_tab(char **tab);
void					weapon(t_env *e);
void					change_weapon(t_env *e);
void					background(int keycode, t_env *e);
void					shot(t_env *e);

#endif
