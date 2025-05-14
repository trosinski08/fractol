/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:43:53 by trosinsk          #+#    #+#             */
/*   Updated: 2024/04/23 21:40:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cursor_zooming(t_fractol *mandel, double xpos, double ypos, double a)
{
	mandel->x_max = xpos + (mandel->x_max - xpos) * a;
	mandel->y_max = ypos + (mandel->y_max - ypos) * a;
	mandel->x_min = xpos + (mandel->x_min - xpos) * a;
	mandel->y_min = ypos + (mandel->y_min - ypos) * a;
}

void	scroll_func(double xdelta, double ydelta, void *param)
{
	t_fractol	*mandel;
	float		xpos;
	float		ypos;
	double		a;

	mandel = (t_fractol *)param;
	if (xdelta) 
		xdelta = 0.0;
	xpos = 0;
	ypos = 0;
	a = 0;
	mlx_get_mouse_pos(mandel->mlx, &mandel->x_pos, &mandel->y_pos);
	if (mandel->x_pos >= 0 && mandel->x_pos < (int32_t)mandel->img->width
		&& mandel->y_pos >= 0 && mandel->y_pos < (int32_t)mandel->img->height)
	{
		xpos = (double)mandel->x_pos * (mandel->x_max - mandel->x_min)
			/ (double)WIDTH + mandel->x_min;
		ypos = (double)mandel->y_pos * (mandel->y_max - mandel->y_min)
			/ (double)HEIGHT + mandel->y_min;
	}
	if (ydelta > 0)
		a = 0.9;
	else if (ydelta < 0)
		a = 1.1;
	cursor_zooming(mandel, xpos, ypos, a);
	mandel->draw = 1;
}

void	julia_dynamic(double xpos, double ypos, void *param)
{
	t_fractol	*mandel;

	mandel = (t_fractol *)param;
	mlx_get_mouse_pos(mandel->mlx, &mandel->x_pos, &mandel->y_pos);
	if ((ft_strncmp(mandel->name, "julia", 5) == 0)
		&& (mandel->x_pos >= 0 && mandel->x_pos < (int32_t)mandel->img->width)
		&& (mandel->y_pos >= 0 && mandel->y_pos < (int32_t)mandel->img->height))
	{
		mandel->c_real = map2(mandel, xpos);
		mandel->c_imag = map3(mandel, ypos);
	}
	mandel->draw = 1;
}
