/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:39:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/10 00:43:40 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*mandel;
	double		change;

	mandel = (t_fractol *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
	{
		change = (mandel->y_max - mandel->y_min) * 0.05;
		if (keydata.key == MLX_KEY_DOWN)
			change *= -1;
		mandel->y_min += change;
		mandel->y_max += change;
	}
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
	{
		change = (mandel->x_max - mandel->x_min) * 0.05;
		if (keydata.key == MLX_KEY_LEFT)
			change *= -1;
		mandel->x_min += change;
		mandel->x_max += change;
	}
	mandel->draw = 1;
}

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
