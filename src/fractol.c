/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:01:06 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/23 20:01:43 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Function to draw the fractal to te screen. */
void	draw_fractal(t_fractol *fractol)
{
	int			x;
	int			y;
	t_complex	scale;

	scale = init_complex((fractol->max.r - fractol->min.r)
			/ (WIDTH), (fractol->max.i - fractol->min.i) / (HEIGHT));
	y = 0;
	while (y < HEIGHT)
	{
		fractol->c.i = fractol->max.i - y * scale.i;
		x = 0;
		while (x < WIDTH)
		{
			fractol->c.r = fractol->min.r + x * scale.r;
			fractol->formula(fractol);
			my_mlx_pixel_put(fractol, x, y, init_colour(fractol));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
		fractol->img->img, 0, 0);
}

/* Suuuper simple function to print out a help message on the screen.*/
void	print_help(void)
{
	ft_putendl_fd("-------------------------------------------\n", 1);
	ft_putendl_fd("Usage: ./fractol <number>", 1);
	ft_putendl_fd("Fractals avaliable:", 1);
	ft_putendl_fd("1 - mandelbrot ", 1);
	ft_putendl_fd("2 - julia", 1);
	ft_putendl_fd("3 - burning ship", 1);
	ft_putendl_fd("\n", 1);
	ft_putendl_fd("Mouse:", 1);
	ft_putendl_fd("Scrollwheel to zoom.", 1);
	ft_putendl_fd("Move that shit around to make Julia change.", 1);
	ft_putendl_fd("\n", 1);
	ft_putendl_fd("Keys:", 1);
	ft_putendl_fd("WASD keys to move.", 1);
	ft_putendl_fd("Q and E keys to increase or decrease iterations.", 1);
	ft_putendl_fd("C to shift colours.", 1);
	ft_putendl_fd("SPACE ah go reset di ting.", 1);
	ft_putendl_fd("ESC to quit.", 1);
	ft_putendl_fd("-------------------------------------------\n", 1);
}

/* This function sets up the window and runs the draw_fractal() function. We're
 * setting our mlx_ptr to return the connection identifier from the mlx_init()
 * function so we can get a connection going between our program and the
 * display and use all the other mlx functions. We create a new window and a new
 * image, init everything and then get our keyboard and mouse hooks going to give
 * us some input ability once the program is running. The Julia set runs a little
 * differently form the other sets, having some cool mouse functionality, so if
 * the user has chosen it we'll use some slightly different hooks for that. Then
 * we run our function to draw it all on the screen and use the mlx_loop()
 * function to keep it going until the user quits.*/
void	start(t_fractol *fractol)
{
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WIDTH, HEIGHT,
			"Fract-ol");
	fractol->img = init_img(fractol);
	init_default(fractol);
	mlx_hook(fractol->win_ptr, 2, 0, key_ctrl, fractol);
	mlx_hook(fractol->win_ptr, 4, 0, mouse_ctrl, fractol);
	if (fractol->formula == &julia)
	{
		mlx_hook(fractol->win_ptr, 5, 0, julia_press, fractol);
		mlx_hook(fractol->win_ptr, 6, 0, change_julia, fractol);
	}
	draw_fractal(fractol);
	mlx_loop(fractol->mlx_ptr);
}

/* This function checks to see what fractal set the user is trying to load. We 
 * use malloc here to set the length of fractol variable it's taking, then we 
 * use our ft_strcmp() function to compare  what the user has typed with the 
 * actual names of the sets. If they match it goes ahead and loads the fractal, 
 * if not it frees up the allocated memory alocated to the fractal variable and 
 * then prints our likkle help message.*/
void	parse(char *arg)
{
	t_fractol	*fractol;

	fractol = malloc(sizeof(t_fractol));
	if (!(ft_strncmp(arg, "1", 1)))
	{
		fractol->formula = &mandelbrot;
		start(fractol);
	}
	else if (!(ft_strncmp(arg, "2", 1)))
	{
		fractol->formula = &julia;
		start(fractol);
	}
	else if (!(ft_strncmp(arg, "3", 1)))
	{
		fractol->formula = &burning_ship;
		start(fractol);
	}
	free(fractol);
	print_help();
}

/* Preeeetty simple main function. Code should be self explanitory here. */
int	main(int argc, char **argv)
{
	if (argc == 2)
		parse(argv[1]);
	else
		print_help();
	return (0);
}
