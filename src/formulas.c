/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:23:53 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/18 13:49:26 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Our Mandelbrot formua. We're taking advantage of the pow() function from
 * the math.h library here too, man it for more info on how it works. I can't be
 * bothered writing out a whole explanation for the set here, but we're just
 * using it to make the z^2 part of z^2 + c here.*/
void	mandelbrot(t_fractol *fractol)
{
	t_complex	z;

	z = init_complex(fractol->c.r, fractol->c.i);
	fractol->iter = 0;
	while (pow(z.r, 2.0) + pow(z.i, 2.0) <= 4
		&& fractol->iter < fractol->max_iter)
	{
		z = init_complex(pow(z.r, 2.0) - pow(z.i, 2.0) + fractol->c.r, 2.0
				* z.r * z.i + fractol->c.i);
		fractol->iter++;
	}
}

/* Our Julia set. The set is almost identical to the Mandelbrot set, but instead
 * of starting with 0 for the real and imaginary parts of z it starts with
 * pixel coordinates and then adds another complex number k each iteration. K
 * now determines the shape of the fractol.
 *
 * Also thanks to this project I CANNOT stop spelling 'fractal' as 'fractol'.
 *
 * Goddamnit.*/
void	julia(t_fractol *fractol)
{
	t_complex	z;

	z = init_complex(fractol->c.r, fractol->c.i);
	fractol->iter = 0;
	while (pow(z.r, 2.0) + pow(z.i, 2.0) <= 4
		&& fractol->iter < fractol->max_iter)
	{
		z = init_complex(pow(z.r, 2.0) - pow(z.i, 2.0) + fractol->k.r, 2.0
				* z.r * z.i + fractol->k.i);
		fractol->iter++;
	}
}

/* Our Burning Ship set. Using pow() again here as well as the fabs() function
 * to get the absolute value of our complex number z. This set is actually
 * pretty similar to the way the Mandelbrot set is calculated, the difference
 * being that with Burning Ship the real and imaginary parts are set to their
 * respective absolute values before they get squared.*/
void	burning_ship(t_fractol *fractol)
{
	t_complex	z;

	z = init_complex(fractol->c.r, fractol->c.i);
	fractol->iter = 0;
	while (pow(z.r, 2.0) + pow(z.i, 2.0) <= 4
		&& fractol->iter < fractol->max_iter)
	{
		z = init_complex(pow(z.r, 2.0) - pow(z.i, 2.0)
				+ fractol->c.r, -2.0 * fabs(z.r * z.i) + fractol->c.i);
		fractol->iter++;
	}
}
