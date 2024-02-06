/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:51 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/06 19:49:10 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "../../MLX42/include/MLX42/MLX42.h"
#define BPP sizeof (int32_t)

// Exit the program as failure.
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
// static void	ft_hook(void *param)
// {
// 	const mlx_t *mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

	// MLX allows you to define its core behaviour before startup.
	/* Do stuff */

	// Create and display the image.
	// Even after the image is being displayed, we can still modify the buffer.
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!

int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if ((argc == 2 && (ft_strncmp(argv[1], "mandelbrot", 10) == 0))
		|| (argc == 5 && (ft_strncmp(argv[4], "julia", 5) == 0)))
	{
		// ft_putstr_fd("jest OK!", 1);
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		if (!mlx)
			ft_error();

		img = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
			ft_error();

		mlx_put_pixel(img, 0, 0, 0xFF0000FF);
		ft_memset(img->pixels, 255, img->width * img->height * BPP);
		mlx_image_to_window(mlx, img, 0, 0);

		// mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}
