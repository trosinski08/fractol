/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:50:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/06 20:20:15 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map_value(t_fractol *mandel, u_int32_t x, uint32_t y)
{
	mandel->real = (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
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
			map_value(mandel, x, y);
			while (mandel->iter < MAXITERATIONS && mandel->z_real
				* mandel->z_real + mandel->z_imag * mandel->z_imag <= 4.0)
			{
				// updt_value(m);function to itertate thru pixels to drawn a pictures TODO
			}
			mandel->color = ft_pixel(mandel->iter % 128, mandel->iter % 64,
					mandel->iter % 255, 255);
			mlx_put_pixel(mandel->img, x, y, mandel->color);
		}
	}
	mandel->draw = 0;
}
