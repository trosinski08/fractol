/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:43:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/25 23:39:03 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Initialize the Julia fractal parameters and set the rendering hook
 * 
 * @param mandel Pointer to the fractal structure
 * @param mlx Pointer to the MLX42 instance
 * 
 * The Julia set is viewed in the complex plane within a symmetric square
 * from (-1.5, -1.5) to (1.5, 1.5).
 */
void	julia_init(t_fractol *mandel, mlx_t *mlx)
{
	mandel->x_min = -1.5;
	mandel->x_max = 1.5;
	mandel->y_min = -1.5;
	mandel->y_max = 1.5;
	mlx_loop_hook(mlx, ft_julia, mandel);
}

/**
 * Calculate iterations for the Julia set at a specific complex point (zr + zi*i)
 * with the complex parameter c = cr + ci*i
 * 
 * @param zr Real part of the complex number z
 * @param zi Imaginary part of the complex number z
 * @param cr Real part of the parameter c
 * @param ci Imaginary part of the parameter c
 * @return Number of iterations before escape or max iterations
 * 
 * Unlike Mandelbrot where c varies and z starts at 0,
 * in Julia sets c is fixed and z varies across the complex plane.
 * For each point z, we iterate the function z = z² + c 
 * and check if it escapes to infinity.
 */
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

/**
 * Render the Julia fractal
 * 
 * @param param Pointer to the fractal structure (cast to void*)
 * 
 * For each pixel:
 * 1. Map pixel coordinates to complex plane (value of z)
 * 2. Calculate iterations using the fixed parameter c (from user input)
 * 3. Color the pixel based on number of iterations
 * 
 * Unlike Mandelbrot where c varies and z starts at 0, in Julia sets c is fixed
 * (provided as parameters when running the program) and the starting z value
 * varies for each pixel.
 */
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
			mandel->color = pixel_clr(mandel, mandel->iter);
			mlx_put_pixel(mandel->img, x, y, mandel->color);
			// Store iteration count for this pixel
			if (mandel->pixel_iterations)
				mandel->pixel_iterations[y * WIDTH + x] = mandel->iter;
		}
	}
	// Update the max_iter value associated with the current pixel_iterations data
	mandel->iterations_max_value_at_render = mandel->max_iter;
	mandel->draw = 0;
}
