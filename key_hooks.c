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

static void	key_zoom(t_fractol *mandel, mlx_key_data_t keydata)
{
	double zoom_factor;
	double center_x;
	double center_y;

	center_x = mandel->x_min + (mandel->x_max - mandel->x_min) / 2.0;
	center_y = mandel->y_min + (mandel->y_max - mandel->y_min) / 2.0;
	if (keydata.key == MLX_KEY_EQUAL)
		zoom_factor = 0.9;
	else
		zoom_factor = 1.1;
	cursor_zooming(mandel, center_x, center_y, zoom_factor);
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
	}	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		key_x_shift(mandel, keydata);
	if ((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_KP_SUBTRACT))
		key_max_iter(mandel, keydata);
	if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		key_zoom(mandel, keydata);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		mandel->effect_random_trigger = !mandel->effect_random_trigger;
		if (mandel->effect_random_trigger)
		{
			mandel->random_time_factor = 0.0f;
			mandel->effect_psy_flow_active = false;
		}
	}	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		mandel->effect_psy_flow_active = !mandel->effect_psy_flow_active;
		if (mandel->effect_psy_flow_active)
		{
			mandel->psy_time_factor = (double)rand() / RAND_MAX * 10.0f;
			mandel->psy_spatial_factor_x = 0.08f + ((double)rand() / RAND_MAX) * 0.05f;
			mandel->psy_spatial_factor_y = 0.08f + ((double)rand() / RAND_MAX) * 0.05f;
			mandel->effect_random_trigger = false;
		}
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		mandel->color_cycling = !mandel->color_cycling;
		if (mandel->color_cycling)
		{
			mandel->color_cycle_speed = 0.2f + ((double)rand() / RAND_MAX) * 0.3f;
			if (!mandel->effect_psy_flow_active)
				mandel->effect_psy_flow_active = true;
		}
	}
	if (keydata.key == MLX_KEY_N && keydata.action == MLX_PRESS)
	{
		mandel->effect_random_trigger = false;
		mandel->effect_psy_flow_active = false;
		mandel->draw = 1;
	}

	if (keydata.key != MLX_KEY_R && keydata.key != MLX_KEY_P && keydata.key != MLX_KEY_N)
		// Only set draw for non-effect keys that change fractal params
		mandel->draw = 1;
}
