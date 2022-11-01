/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:10:04 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/23 19:39:30 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Handles movement via keyboard input. We're calling our variable delta here
 * in the math sense of it representing a change in something. We've set it up
 * so each movement (WASD in this case) moves it around by a factor of 0.05 in
 * whatever direction, so it should be a nice gentle ammount.*/
void	movement(int key, t_fractol *fractol)
{
	t_complex	delta;

	delta = init_complex((fractol->max.r - fractol->min.r) * 0.05,
			(fractol->max.i - fractol->min.i) * 0.05);
	if (key == 0)
	{
		fractol->min.r = fractol->min.r - delta.r;
		fractol->max.r = fractol->max.r - delta.r;
	}
	else if (key == 2)
	{
		fractol->min.r = fractol->min.r + delta.r;
		fractol->max.r = fractol->max.r + delta.r;
	}
	else if (key == 1)
	{
		fractol->min.i = fractol->min.i - delta.i;
		fractol->max.i = fractol->max.i - delta.i;
	}
	else if (key == 13)
	{
		fractol->min.i = fractol->min.i + delta.i;
		fractol->max.i = fractol->max.i + delta.i;
	}
}

/* Function to shift our colours around. Key codes are as follows:
 * 69 = + (numpad)
 * 78 = - (numpad)
 * 49 = SPACE
 * 53 = ESC
 * 13, 0, 1, 2 = WASD
 * 8 = C*/
void	colour_shift(t_fractol *fractol)
{
	fractol->shift++;
	if (fractol->shift > 3)
		fractol->shift = 1;
}

int	key_ctrl(int key, t_fractol *fractol)
{
	if (key == 14)
	{
		if (fractol->max_iter < 50)
			fractol->max_iter += 1;
		else if (fractol->max_iter < 1000000000)
			fractol->max_iter *= 1.05;
	}
	if (key == 12)
	{
		if (fractol->max_iter > 50)
			fractol->max_iter *= 0.95;
		else if (fractol->max_iter > 1)
			fractol->max_iter -= 1;
	}
	if (key == 49)
		init_default(fractol);
	if (key == 53)
		exit(0);
	if (key == 0 || key == 2 || key == 1 || key == 13)
		movement(key, fractol);
	if (key == 8)
		colour_shift(fractol);
	draw_fractal(fractol);
	return (0);
}
