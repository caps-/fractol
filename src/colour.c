/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:24:22 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/19 15:23:44 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Sets up our colours. We're using bitshifting here to interpolate properly
 * between the different shades of red, green, blue and transparency. If we
 * tried to shift from blue to red by increasing hex values directly the 
 * pallette would move through green (and everything else inbetween) until it 
 * hit red. In other words, it would start at FF0000, but to reach 0000FF it
 * would have to increment through 00FF00 and literally every other combination
 * until it finally got to 0000FF. D doing it this way lets us interpolate the
 * trgb values individually.
 *
 * Also trgb, I get it, but dunno why mlx doesn't use rgba.
 * 
 * 42 gunna 42 I spose. */
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/* Our own mlx_pixel_put() function that mimics the behaviour of the original
 * function but in a much faster way. */
void	my_mlx_pixel_put(t_fractol *fractol, int x, int y, int colour)
{
	char	*dst;

	dst = fractol->img->data_addr + (y * fractol->img->line_size
			+ x * (fractol->img->bpp / 8));
	*(unsigned int *)dst = colour;
}

/* A pretty simple function to shift the palette around. Like, literally just
 * shifting the values around and cycling between them. Perhaps not as cool as
 * switching to entirely new colourways but it's easy and still gives us some
 * cool resaults. */
int	init_colour(t_fractol *fractol)
{
	double	t;
	int		colour[4];

	t = (double)fractol->iter / (double)fractol->max_iter;
	colour[0] = 0;
	if (fractol->shift == 1)
	{
		colour[1] = (int)(9 * (1 - t) * pow(t, 3) * 255);
		colour[2] = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		colour[3] = (int)(8.5 * pow((1 - t), 3) * t * 225);
	}
	if (fractol->shift == 2)
	{
		colour[2] = (int)(9 * (1 - t) * pow(t, 3) * 255);
		colour[1] = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		colour[3] = (int)(8.5 * pow((1 - t), 3) * t * 225);
	}
	if (fractol->shift == 3)
	{
		colour[3] = (int)(9 * (1 - t) * pow(t, 3) * 255);
		colour[2] = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		colour[1] = (int)(8.5 * pow((1 - t), 3) * t * 225);
	}
	return (create_trgb(colour[0], colour[1], colour[2], colour[3]));
}
