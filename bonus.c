/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:01:56 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 02:32:58 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	next(t_complex z)
{
	t_complex	new;
	double		temp_deno;

	temp_deno = 3 * (z.x * z.x + z.y * z.y) * (z.x * z.x + z.y * z.y);
	new.x = ((z.x * z.x * z.x * z.x * z.x + 2 * z.x * z.x * z.x * z.y * z.y
				- z.x * z.x + z.x * z.y * z.y * z.y * z.y + z.y * z.y)
			/ temp_deno);
	new.y = ((z.y * (z.x * z.x * z.x * z.x + 2 * z.x * z.x
					* z.y * z.y + 2 * z.x + z.y * z.y * z.y * z.y))
			/ temp_deno);
	z.x -= new.x;
	z.y -= new.y;
	return (z);
}

// static t_complex find_diff(t_complex z, t_complex root)
// {
//     t_complex    new;

//     new.x = z.x - root.x;
//     new.y = z.y - root.y;
//     return (new);
// }

static void	newton_iteration(t_fractol *newton, uint32_t x, uint32_t y)
{
	double		dx;
	double		dy;
	double		z_real;
	double		z_imag;
	t_complex	z;

	dx = (newton->x_max - newton->x_min) / newton->img->width;
	dy = (newton->y_max - newton->y_min) / newton->img->height;
	newton->real = newton->x_min + x * dx;
	newton->imag = newton->y_min + y * dy;
	z_real = newton->real;
	z_imag = newton->imag;
	while (newton->iter < newton->max_iter)
	{
		z.x = z_real;
		z.y = z_imag;
		z = next(z);
		dx = (z_real - z.x);
		dy = (z_imag - z.y);
		z_real -= dx;
		z_imag -= dy;
		if (fabs(dx) < EPSILON && fabs(dy) < EPSILON)
			break ;
		newton->iter++;
	}
}

void	newton_init(t_fractol *newton, mlx_t *mlx)
{
	newton->x_min = -2.0;
	newton->x_max = 2.0;
	newton->y_min = -2.0;
	newton->y_max = 2.0;
	mlx_loop_hook(mlx, ft_newton, newton);
}

void	ft_newton(void *param)
{
	uint32_t	y;
	uint32_t	x;
	t_fractol	*newton;

	newton = (t_fractol *)param;
	if (newton->draw != 1)
		return ;
	y = 0;
	while (++y < newton->img->height)
	{
		x = 0;
		while (++x < newton->img->width)
		{
			newton->iter = 0;
			newton_iteration(newton, x, y);
			newton->color = map(newton);
			mlx_put_pixel(newton->img, x, y, newton->color);
		}
	}
	newton->draw = 0;
}
