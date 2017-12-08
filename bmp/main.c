#include "bmp.h"

int		main(int argc, char **argv)
{
	int		*tab;

	if (argc < 2 || argc > 2)
		return (-1);
	else
		tab = bmp(argv[1]);
	return (0);
}
