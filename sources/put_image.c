#include "minirt.h"

static char	*get_image_data(void *img)
{
	int	bpp;
	int	line_length;
	int	endian;

	return (mlx_get_data_addr(img, &bpp, &line_length, &endian));
}

static int compute_pixel_color(int x, int y)
{
    int red   = (255.999 * x) / (WIN_WIDTH - 1);
    int green = (255.999 * y) / (WIN_HEIGHT - 1);
    int blue  = 0;
    return (red << 16) | (green << 8) | blue;
}

static void	render_pixels(char *data)
{
	unsigned int	*pixels;
	int				x;
	int				y;

	pixels = (unsigned int *)data;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixels[y * WIN_WIDTH + x] = compute_pixel_color(x, y);
			x++;
		}
		y++;
	}
}

// Need to have a struct for map info
void	render_image(t_window *window)
{
	void	*img;
	char	*data;

	img = mlx_new_image(window->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		close_program(window);
	data = get_image_data(img);
	render_pixels(data);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img, 0, 0);
	//mlx_destroy_image(window->mlx_ptr, img);
}

