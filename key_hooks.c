/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:39:36 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 12:41:57 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	key_max_iter(t_fractol *mandel, mlx_key_data_t keydata)
{
	int	change;

	change = 10;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && mandel->max_iter - change <= 0)
		change *= 0;
	if (keydata.key == MLX_KEY_KP_SUBTRACT)
		change *= -1;
	mandel->max_iter += change;
}

static void	key_x_shift(t_fractol *mandel, mlx_key_data_t keydata)
{
	double	change;

	change = (mandel->x_max - mandel->x_min) * 0.05;
	if (keydata.key == MLX_KEY_RIGHT)
		change *= -1;
	mandel->x_min += change;
	mandel->x_max += change;
}

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
		key_x_shift(mandel, keydata);
	if ((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_KP_SUBTRACT))
		key_max_iter(mandel, keydata);
	mandel->draw = 1;
}
