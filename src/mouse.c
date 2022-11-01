/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:30:17 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/19 11:54:53 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int	mouse_ctrl(int key, int x, int y, t_fractol *fractol)
{
	t_complex	mouse;
	double		zoom;

	if (key == 1)
		fractol->press = 1;
	mouse.r = (fractol->min.r + x * ((fractol->max.r - fractol->min.r)
				/ (WIDTH)));
	mouse.i = (fractol->max.i - y * ((fractol->max.i - fractol->min.i)
				/ (HEIGHT)));
	if (key == 5)
		zoom = 1.20;
	else if (key == 4)
		zoom = 0.80;
	else
		zoom = 1.0;
	fractol->min.r = interpolate(mouse.r, fractol->min.r, zoom);
	fractol->min.i = interpolate(mouse.i, fractol->min.i, zoom);
	fractol->max.r = interpolate(mouse.r, fractol->max.r, zoom);
	fractol->max.i = interpolate(mouse.i, fractol->max.i, zoom);
	draw_fractal(fractol);
	return (0);
}

int	julia_press(int key, int x, int y, t_fractol *fractol)
{
	(void) x;
	(void) y;
	if (key == 1)
		fractol->press = 0;
	return (0);
}

int	change_julia(int x, int y, t_fractol *fractol)
{
	if (fractol->press == 1)
	{
		fractol->k = init_complex(4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		draw_fractal(fractol);
	}
	return (0);
}
