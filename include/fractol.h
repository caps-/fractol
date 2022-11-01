/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwhittin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:38:32 by pwhittin          #+#    #+#             */
/*   Updated: 2022/10/19 12:00:16 by pwhittin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HEIGHT 800
# define WIDTH 800

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

/* Helps us handle our complex numbers */
typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

/* A bunch of params we'll need to set up and draw our images */
typedef struct s_img
{
	void	*img;
	char	*data_addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

/* Stuff we'll be using to calculate our fractals */
typedef struct s_fractol
{
	t_img		*img;
	void		*mlx_ptr;
	void		*win_ptr;
	t_complex	max;
	t_complex	min;
	t_complex	c;
	t_complex	k;
	int			iter;
	int			max_iter;
	int			press;
	int			shift;
	void		(*formula)(struct s_fractol *);
}	t_fractol;

/* All the other functions we're gunna use */
t_complex	init_complex(double r, double i);
t_img		*init_img(t_fractol *fractol);
void		init_default(t_fractol *fractol);
int			init_colour(t_fractol *fractol);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_fractol *fractol, int x, int y, int colour);
double		interpolate(double start, double end, double interpolation);
int			mouse_ctrl(int key, int x, int y, t_fractol *fractol);
int			key_ctrl(int key, t_fractol *fractol);
void		draw_fractal(t_fractol *fractol);
void		mandelbrot(t_fractol *fractol);
void		julia(t_fractol *fractol);
void		burning_ship(t_fractol *fractol);
void		start(t_fractol *fractol);
void		parse(char *arg);
void		print_help(void);
int			change_julia(int x, int y, t_fractol *fractol);
int			julia_press(int key, int x, int y, t_fractol *fractol);
void		movement(int key, t_fractol *fractol);
void		colour_shift(t_fractol *fractol);

#endif
