/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:39:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/08 14:49:20 by trosinsk         ###   ########.fr       */
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

void	scroll_func(double xdelta, double ydelta, void *param)
{
	t_fractol	*mandel;

	mandel = (t_fractol *)param;
	xdelta = 0.0;
	if (ydelta > 0)
	{
		mandel->x_max -= (mandel->x_max - mandel->x_min) * 0.1;
		mandel->y_max -= (mandel->y_max - mandel->y_min) * 0.1;
		mandel->x_min += (mandel->x_max - mandel->x_min) * 0.1;
		mandel->y_min += (mandel->y_max - mandel->y_min) * 0.1;
	}
	else if (ydelta < 0)
	{
		mandel->x_max += (mandel->x_max - mandel->x_min) * 0.1;
		mandel->y_max += (mandel->y_max - mandel->y_min) * 0.1;
		mandel->x_min -= (mandel->x_max - mandel->x_min) * 0.1;
		mandel->y_min -= (mandel->y_max - mandel->y_min) * 0.1;
	}
	mandel->draw = 1;
}
