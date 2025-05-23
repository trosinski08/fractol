/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:50:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/26 00:15:45 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * Initialize the Mandelbrot fractal parameters and set the rendering hook
 * 
 * @param mandel Pointer to the fractal structure
 * @param mlx Pointer to the MLX42 instance
 * 
 * The Mandelbrot set is viewed in the complex plane from (-2.0, -1.5) to (1.0, 1.5)
 * which captures the entire characteristic shape.
 */
void	mandel_init(t_fractol *mandel, mlx_t *mlx)
{
	mandel->x_min = -2.0;
	mandel->x_max = 1.0;
	mandel->y_min = -1.5;
	mandel->y_max = 1.5;
	mlx_loop_hook(mlx, ft_mandelbrot, mandel);
}

/**
 * Map pixel coordinates to complex plane coordinates and initialize variables
 * for the Mandelbrot calculation
 * 
 * @param mandel Pointer to the fractal structure
 * @param x X coordinate on the screen (pixel)
 * @param y Y coordinate on the screen (pixel)
 * 
 * For each pixel (x,y), calculate the corresponding point (real,imag) in the complex plane.
 * In the Mandelbrot algorithm, this point is the constant c in z = z² + c, and we start with z = 0.
 */
static void	mandelbroting(t_fractol *mandel, uint32_t x, uint32_t y)
{
	mandel->real = mandel->x_min + (double)x
		/ mandel->img->width * (mandel->x_max - mandel ->x_min);
	mandel->imag = mandel->y_min + (double)y
		/ mandel->img->height * (mandel->y_max - mandel ->y_min);
	mandel ->c_real = mandel ->real;
	mandel ->c_imag = mandel ->imag;
	mandel ->iter = 0;
	mandel ->z_real = 0.0;
	mandel ->z_imag = 0.0;
}

/**
 * Perform one iteration of the Mandelbrot formula: z = z² + c
 * 
 * @param mandel Pointer to the fractal structure
 * 
 * For complex numbers z = a + bi and c = c_real + c_imag*i,
 * the formula z = z² + c becomes:
 * (a + bi)² + (c_real + c_imag*i) = 
 * (a² - b² + c_real) + (2ab + c_imag)i
 */
static void	next_iter(t_fractol *mandel)
{
	double	temp;

	temp = mandel->z_real * mandel->z_real
		- mandel->z_imag * mandel->z_imag + mandel ->c_real;
	mandel->z_imag = 2.0 * mandel->z_real * mandel->z_imag + mandel->c_imag;
	mandel->z_real = temp;
	mandel->iter++;
}

/**
 * Render the Mandelbrot fractal
 * 
 * @param param Pointer to the fractal structure (cast to void*)
 * 
 * For each pixel:
 * 1. Map pixel coordinates to complex plane
 * 2. Iterate the Mandelbrot formula until either:
 *    - Maximum iterations reached (point may be in the set)
 *    - |z| > 2 (point escapes, not in the set)
 * 3. Color the pixel based on number of iterations
 * 
 * The escape radius is 2 (squared to 4.0 for efficiency), 
 * meaning if |z| exceeds 2, the point is not in the Mandelbrot set.
 */
void	ft_mandelbrot(void *param)
{
	uint32_t	y;
	uint32_t	x;
	t_fractol	*mandel;

	mandel = (t_fractol *)param;
	if (mandel->draw != 1)
		return ;
	y = 0;
	while (++y < mandel->img->height)
	{
		x = 0;
		while (++x < mandel->img->width)
		{
			mandelbroting(mandel, x, y);
			while (mandel->iter < mandel->max_iter && mandel->z_real
				* mandel->z_real + mandel->z_imag * mandel->z_imag <= 4.0)
			{
				next_iter(mandel);
			}
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
