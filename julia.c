/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:43:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/07 17:48:22 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(float zr, float zi, float cr, float ci)
{
	int		iterations;
	double	temp;

	iterations = 0;
	while (iterations < MAXITERATIONS && (zr * zr + zi * zi) <= 4)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = temp;
		iterations++;
	}
	return (iterations);
}

void	ft_julia(void *param)
{
	t_fractol	*mandel;
	uint32_t	x;
	uint32_t	y;

	mandel = (t_fractol *)param;
	if (mandel->draw != 1)
		return ;
	y = 0;
	while (++y < mandel->img->height)
	{
		x = 0;
		while (++x < mandel->img->width)
		{
			mandel->real = mandel->x_min + (double)x
				/ mandel->img->width * (mandel->x_max - mandel->x_min);
			mandel->imag = mandel->y_min + (double)y
				/ mandel->img->height * (mandel->y_max - mandel->y_min);
			mandel->iter = julia(mandel->real,
					mandel->imag, mandel->c_real, mandel->c_imag);
			mandel->color = map(mandel);
			mlx_put_pixel(mandel->img, x, y, mandel->color);
		}
	}
	mandel->draw = 0;
}
