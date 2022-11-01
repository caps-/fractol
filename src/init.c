/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:57:14 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/23 19:42:45 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Initializes the real and imaginary parts of our complex number. */
t_complex	init_complex(double r, double i)
{
	t_complex	complex;

	complex.r = r;
	complex.i = i;
	return (complex);
}

/* Init the image mlx is going to use. */
t_img	*init_img(t_fractol *fractol)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	img->data_addr = mlx_get_data_addr(img->img, &(img->bpp), &(img->line_size),
			&(img->endian));
	return (img);
}

/* And finally a function to init everything else. */
void	init_default(t_fractol *fractol)
{
	fractol->max_iter = 50;
	fractol->min.r = -2.0;
	fractol->max.r = 2.0;
	fractol->min.i = -2.0;
	fractol->max.i = fractol->min.i + (fractol->max.r - fractol->min.r)
		* HEIGHT / WIDTH;
	fractol->k = init_complex(-0.4, 0.6);
	fractol->press = 0;
	fractol->shift = 1;
}
