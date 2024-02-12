/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:50:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 00:14:36 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandel_init(t_fractol *mandel, mlx_t *mlx)
{
	mandel->x_min = -2.0;
	mandel->x_max = 1.0;
	mandel->y_min = -1.5;
	mandel->y_max = 1.5;
	mlx_loop_hook(mlx, ft_mandelbrot, mandel);
}

static void	mandelbroting(t_fractol *mandel, u_int32_t x, uint32_t y)
{
	mandel->real = mandel->x_min + (double)x
		/ mandel->img->width * (mandel->x_max - mandel ->x_min);
	mandel->imag = mandel->y_min + (double)y
		/ mandel->img->height * (mandel->y_max - mandel ->y_min);
	mandel ->c_real = mandel ->real;
	mandel ->c_imag = mandel ->imag;
	mandel ->iter = 0;
	mandel ->z_real = 0.0;
	mandel ->z_imag = 0.0;
}

static void	next_iter(t_fractol *mandel)
{
	double	temp;

	temp = mandel->z_real * mandel->z_real
		- mandel->z_imag * mandel->z_imag + mandel ->c_real;
	mandel->z_imag = 2.0 * mandel->z_real * mandel->z_imag + mandel->c_imag;
	mandel->z_real = temp;
	mandel->iter++;
}

void	ft_mandelbrot(void *param)
{
	uint32_t	y;
	uint32_t	x;
	t_fractol	*mandel;

	mandel = (t_fractol *)param;
	if (mandel->draw != 1)
		return ;
	y = 0;
	while (++y < mandel->img->height)
	{
		x = 0;
		while (++x < mandel->img->width)
		{
			mandelbroting(mandel, x, y);
			while (mandel->iter < mandel->max_iter && mandel->z_real
				* mandel->z_real + mandel->z_imag * mandel->z_imag <= 4.0)
			{
				next_iter(mandel);
			}
			mandel->color = map(mandel);
			mlx_put_pixel(mandel->img, x, y, mandel->color);
		}
	}
	mandel->draw = 0;
}
