/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:51 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 12:35:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "./MLX42/include/MLX42/MLX42.h"
#ifdef __unix__
#include <unistd.h>
#endif

bool	img_control(t_fractol *mandel, mlx_t *mlx)
{
	if (!mlx)
		ft_error();
	mandel->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mandel->img || (mlx_image_to_window(mlx, mandel->img, 0, 0) < 0))
	{
		mlx_close_window(mlx);
		ft_error();
	}
	if (mlx_image_to_window(mlx, mandel->img, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		ft_error();
	}
	return (1);
}

void	f_init(t_fractol *m, mlx_t *mlx, char **argv)
{
	m->draw = 1;
	m->max_iter = MAXITERATIONS;
	if (argv[1][0] == 'm')
	{
		m->name = "mandelbrot";
		mandel_init(m, mlx);
	}
	else if (argv[1][0] == 'j')
	{
		m->c_real = ft_atod(argv[2]);
		m->c_imag = ft_atod(argv[3]);
		m->name = "julia";
		julia_init(m, mlx);
	}
	else if (argv[1][0] == 'n')
	{
		m->name = "newton";
		newton_init(m, mlx);
	}
	else
	{
		ft_putstr_fd("Param error!", 2);
		exit (0);
	}	// Initialize effect flags
	m->effect_random_trigger = false;
	m->effect_psy_flow_active = false;
	m->effect_active = false;
	m->psy_time_factor = 0.0f;
	m->random_time_factor = 0.0f;
	m->psy_spatial_factor_x = 0.01f;
	m->psy_spatial_factor_y = 0.01f;
	// Allocate memory for pixel_iterations array
	m->pixel_iterations = malloc(sizeof(int) * WIDTH * HEIGHT);
	if (!m->pixel_iterations)
		ft_error(); // Or handle memory allocation failure appropriately
	// Initialize iterations_max_value_at_render to a value that forces initial calculation
	m->iterations_max_value_at_render = -1;
}

// New hook function for the main loop
static void update_frame_hook(void *param)
{
	t_fractol *mandel = (t_fractol *)param;

	if (mandel->draw)
	{
		if (ft_strncmp(mandel->name, "mandelbrot", 10) == 0)
			ft_mandelbrot(mandel);
		else if (ft_strncmp(mandel->name, "julia", 5) == 0)
			ft_julia(mandel);
		else if (ft_strncmp(mandel->name, "newton", 6) == 0)
			ft_newton(mandel);
		mandel->draw = 0; // Reset draw flag after rendering fractal
	}

	// Track if any effect is active for mouse movement cancellation
	bool was_effect_active = mandel->effect_active;
	mandel->effect_active = (mandel->effect_random_trigger || mandel->effect_psy_flow_active);

	// Apply continuous random effect if triggered
	if (mandel->effect_random_trigger)
	{
		ft_randomize_effect(mandel);
		// Don't reset trigger - let it run continuously until interrupted
	}

	// Apply continuous psy flow effect if active
	if (mandel->effect_psy_flow_active)
	{
		ft_psy_flow_effect(mandel);
	}
	
	// If effects were deactivated, redraw the original fractal
	if (was_effect_active && !mandel->effect_active)
	{
		mandel->draw = 1; // Trigger a redraw of the original fractal
	}
}

void	performer(t_fractol *mandel, mlx_t *mlx, char **argv)
{
	instruction();
	mlx_scroll_hook(mlx, scroll_func, mandel);
	f_init(mandel, mlx, argv);
	mlx_cursor_hook(mlx, julia_dynamic, mandel);
	mlx_key_hook(mlx, my_keyhook, mandel);

	// Register the main update function to be called by mlx_loop
	mlx_loop_hook(mlx, &update_frame_hook, mandel);

	// Start the MLX42 event loop (this is a blocking call)
	mlx_loop(mlx);

	// Clean up MLX42 resources after the loop finishes
	mlx_terminate(mlx);
	// Free the allocated memory for pixel_iterations
	if (mandel->pixel_iterations)
		free(mandel->pixel_iterations);
}

int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_fractol	*mandel;

	if ((argc == 2 && ((ft_strncmp(argv[1], "mandelbrot", 10) == 0)
				|| ft_strncmp(argv[1], "newton", 6) == 0))
		|| (argc == 4 && (ft_strncmp(argv[1], "julia", 5) == 0)))
	{
		mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		mandel = (t_fractol *)malloc(sizeof(t_fractol));
		mandel->mlx = mlx;
		if (img_control(mandel, mlx) && mandel)
		{
			performer(mandel, mlx, argv);
			return (EXIT_SUCCESS);
		}
		free(mandel);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		ft_putstr_fd(ERROR_MESSAGE1, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}
