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

/**
 * Zoom the fractal view centered around a specific point
 * 
 * @param mandel Pointer to the fractal structure
 * @param xpos X coordinate in the complex plane to zoom around
 * @param ypos Y coordinate in the complex plane to zoom around
 * @param a Zoom factor (< 1 for zoom in, > 1 for zoom out)
 * 
 * This function performs a centered zoom, keeping the point (xpos, ypos)
 * stationary while scaling the view around it. This creates the effect of
 * zooming into/out of the point under the mouse cursor.
 */
void	cursor_zooming(t_fractol *mandel, double xpos, double ypos, double a)
{
	mandel->x_max = xpos + (mandel->x_max - xpos) * a;
	mandel->y_max = ypos + (mandel->y_max - ypos) * a;
	mandel->x_min = xpos + (mandel->x_min - xpos) * a;
	mandel->y_min = ypos + (mandel->y_min - ypos) * a;
}

/**
 * Handle mouse scroll events for zooming
 * 
 * @param xdelta Horizontal scroll amount (unused)
 * @param ydelta Vertical scroll amount (positive for scroll up, negative for down)
 * @param param Pointer to the fractal structure
 * 
 * When user scrolls:
 * 1. Get mouse position
 * 2. Convert screen coordinates to complex plane coordinates
 * 3. Zoom in (scroll up) or out (scroll down) centered on that point
 * 4. Trigger redraw of the fractal
 */
void	scroll_func(double xdelta, double ydelta, void *param)
{
	t_fractol	*mandel;
	float		xpos;
	float		ypos;
	double		a;

	mandel = (t_fractol *)param;
	if (xdelta) 
		xdelta = 0.0;  // Ignore horizontal scroll
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
	}	if (ydelta > 0)
		a = 0.9;  // Zoom in (90% of original size)
	else if (ydelta < 0)
		a = 1.1;  // Zoom out (110% of original size)
	cursor_zooming(mandel, xpos, ypos, a);
	
	// Only trigger a redraw if no effects are active
	if (!mandel->effect_random_trigger && !mandel->effect_psy_flow_active)
		mandel->draw = 1;  // Trigger redraw
}

/**
 * Dynamically update Julia set parameters based on mouse position
 * 
 * @param xpos X position of the cursor
 * @param ypos Y position of the cursor
 * @param param Pointer to the fractal structure
 * 
 * For Julia sets, this enables interactive exploration by changing the
 * parameter c based on mouse cursor position. As the user moves the mouse,
 * the Julia set dynamically changes in real-time, creating an interactive
 * and exploratory experience.
 * 
 * This is particularly useful to discover interesting Julia sets that are
 * related to specific areas of the Mandelbrot set.
 */
void	julia_dynamic(double xpos, double ypos, void *param)
{
	t_fractol	*mandel;

	mandel = (t_fractol *)param;	mlx_get_mouse_pos(mandel->mlx, &mandel->x_pos, &mandel->y_pos);
	if ((ft_strncmp(mandel->name, "julia", 5) == 0)
		&& (mandel->x_pos >= 0 && mandel->x_pos < (int32_t)mandel->img->width)
		&& (mandel->y_pos >= 0 && mandel->y_pos < (int32_t)mandel->img->height))
	{
		mandel->c_real = map2(mandel, xpos);
		mandel->c_imag = map3(mandel, ypos);
		
		// Only trigger a redraw if no effects are active
		if (!mandel->effect_random_trigger && !mandel->effect_psy_flow_active)
			mandel->draw = 1;  // Trigger redraw with new parameters
	}
}
