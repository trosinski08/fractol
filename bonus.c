/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:01:56 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/09 14:16:15 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	sierpinski_init(t_fractol *mandel, mlx_t *mlx)
// {
// 	mandel->x_min = -1.5;
// 	mandel->x_max = 1.5;
// 	mandel->y_min = -1.5;
// 	mandel->y_max = 1.5;
// 	mandel->x1 = WIDTH / 2;
// 	mandel->y1 = 50;
// 	mandel->x2 = 50;
// 	mandel->y2 = HEIGHT - 50;
// 	mandel->x3 = WIDTH - 50;
// 	mandel->y3 = HEIGHT - 50;
// 	mlx_loop_hook(mlx, ft_sierpinski, mandel);
// }

// void	ft_sierpinski(void *param)
// {
// 	t_fractol	*mandel;
// 	int			i;
// 	int			x;
// 	int			y;
// 	int			r;

// 	mandel = (t_fractol *)param;
// 	x = 50;
// 	y = HEIGHT - 50;
// 	i = 0;
// 	while (i++ < 10000)
// 	{
// 		r = rand() % 3;
// 		if (r == 0)
// 		{
// 			x = (x + mandel->x1) / 2;
// 			y = (y + mandel->y1) / 2;
// 		}
// 		else if (r == 1)
// 		{
// 			x = (x + mandel->x2) / 2;
// 			y = (y + mandel->y2) / 2;
// 		}
// 		else if (r == 2)
// 		{
// 			x = (x + mandel->x3) / 2;
// 			y = (y + mandel->y3) / 2;
// 		}
// 		mandel->color = WHITE;
// 		mlx_put_pixel(mandel->img, x, y, mandel->color);
// 	}
// 	mandel->draw = 0;
// }
#include "fractol.h"

void	newton_init(t_fractol *newton, mlx_t *mlx)
{
	newton->x_min = -2.0;
	newton->x_max = 2.0;
	newton->y_min = -2.0;
	newton->y_max = 2.0;
	mlx_loop_hook(mlx, ft_newton, newton);
}

static void	newton_iteration(t_fractol *newton, uint32_t x, uint32_t y)
{
	double	dx;
	double	dy;
	double	z_real;
	double	z_imag;

	dx = (newton->x_max - newton->x_min) / newton->img->width;
	dy = (newton->y_max - newton->y_min) / newton->img->height;
	newton->real = newton->x_min + x * dx;
	newton->imag = newton->y_min + y * dy;
	newton->iter = 0;
	z_real = newton->real;
	z_imag = newton->imag;
	while (newton->iter < MAXITERATIONS)
	{
		dx = (z_real * z_real - z_imag * z_imag + newton->c_real)
			/ (2 * z_real);
		dy = (2 * z_real * z_imag + newton->c_imag) / (2 * z_real);
		z_real -= dx;
		z_imag -= dy;
		if (fabs(dx) < EPSILON && fabs(dy) < EPSILON)
			break ;
		newton->iter++;
	}
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
			newton_iteration(newton, x, y);
			newton->color = map(newton);
			mlx_put_pixel(newton->img, x, y, newton->color);
		}
	}
	newton->draw = 0;
}
