/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 15:23:41 by akorzhak          #+#    #+#             */
/*   Updated: 2018/03/04 14:23:33 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_pixel(int x, int y, t_ptr *p, t_fractal *f)
{
	int		i;
	double	zn;
	double	index;

	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
		return ;
	i = x * p->bpp + y * p->size_line;
	if (p->iter < p->iter_max)
	{
		zn = sqrt(f->z_real * f->z_real + f->z_imag * f->z_imag);
		index = p->iter + 1 - (log(2) / zn) / log(2);
		p->addr[i] = sin(p->col.b_freq * index + p->col.b_phase)
					* p->col.center * p->col.delta;
		p->addr[++i] = sin(p->col.g_freq * index + p->col.g_phase)
					* p->col.center * p->col.delta;
		p->addr[++i] = sin(p->col.r_freq * index + p->col.r_phase)
					* p->col.center * p->col.delta;
	}
	else
	{	
		p->addr[i] = 0;
		p->addr[++i] = 0;
		p->addr[++i] = 0;
	}
}

void	draw_mandelbrot(t_ptr *p, t_fractal *f)
{
    int x;
    int y;
    double temp;

	y = 0;
	while (y++ < SIZE_Y)
	{
		x = 0;
		f->c_imag = f->max_imag - y * (f->max_imag - f->min_imag) / (SIZE_Y - 1);
		while (x++ < SIZE_X)
		{
			f->c_real = f->min_real + x * (f->max_real - f->min_real) / (SIZE_X - 1);
		    p->iter = 0;
		    f->z_real = f->c_real;
		    f->z_imag = f->c_imag;
			while ((p->iter)++ < p->iter_max &&
			(f->z_real * f->z_real + f->z_imag * f->z_imag) < f->infinit_border)
			{
			    temp = f->z_real * f->z_real - f->z_imag * f->z_imag + f->c_real;
                f->z_imag = 2 * f->z_real * f->z_imag + f->c_imag;
                f->z_real = temp;
			}
			draw_pixel(x, y, p, f);
		}		
	}
}

void	draw_fractal(t_ptr *p, t_fractal *f)
{
	if (p->fract_name == MANDELBROT)
		draw_mandelbrot(p, f);
//	else if (p->fractal == JULIA)
//		draw_julia(p, f);
//	else
//		draw_burningship(p, f);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
}