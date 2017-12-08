#include "wolf.h"

#pragma pack(push, 1)

typedef struct		s_pixel
{
  unsigned char		R;
  unsigned char		G;
  unsigned char		B;
}					t_pixel;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct		s_bitmap
{
    short			signature;
    int				size;
    short			reserved1;
    short			reserved2;
    int				dataoffSet;
    int				bitmapheadersize;
    int				width;
    int				height;
    short			planes;
    short			bitsperpixel;
    int				compression;
    int				sizeImage;
    int				xpixelspremeter;
    int				ypixelspremeter;
    int				colorsused;
    int				colorsimportant;
}					t_bitmap;
#pragma pack(pop)
/** END BITMAP **/


