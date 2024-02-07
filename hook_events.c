/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:39:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/07 21:37:41 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The mouse wheel zooms in and out, almost infinitely

//Pressing ESC must close the window and quit the program in a clean way.

//Clicking on the cross on the window’s frame must close the window 
// and quit the program in a clean way.

#include "fractol.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*mandel;

	mandel = (t_fractol *)param;
	// if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	// {
	// 	mandel->y_min += (mandel->y_max - mandel->y_min) * -0.1;
	// 	mandel->y_max += (mandel->y_max - mandel->y_min) * -0.1;
	// }
	// if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	// {
	// 	mandel->y_min -= (mandel->y_max - mandel->y_min) * -0.1;
	// 	mandel->y_max -= (mandel->y_max - mandel->y_min) * -0.1;
	// }
	// if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	// {
	// 	mandel->x_min += (mandel->x_max - mandel->x_min) * -0.1;
	// 	mandel->x_max += (mandel->x_max - mandel->x_min) * -0.1;
	// }
	// if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	// {
	// 	mandel->x_min -= (mandel->x_max - mandel->x_min) * -0.1;
	// 	mandel->x_max -= (mandel->x_max - mandel->x_min) * -0.1;
	// }
	// if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	// 	return (exit(0));
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
