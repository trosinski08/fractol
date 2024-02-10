/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:51 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/09 18:55:08 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "../../MLX42/include/MLX42/MLX42.h"

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
	if (argv[1][0] == 'm')
	{
		mandel_init(m, mlx);
	}
	else if (argv[1][0] == 'j')
	{
		m->c_real = ft_atod(argv[2]);
		m->c_imag = ft_atod(argv[3]);
		julia_init(m, mlx);
	}
	else if (argv[1][0] == 'n')
	{
		newton_init(m, mlx);
	}
	else
	{
		write(1, "param error", 1);
		exit (0);
	}
}

void	performer(t_fractol *mandel, mlx_t *mlx, char **argv)
{
	mlx_scroll_hook(mlx, scroll_func, mandel);
	f_init(mandel, mlx, argv);
	mlx_key_hook(mlx, my_keyhook, mandel);
	mlx_loop(mlx);
	mlx_terminate(mlx);
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
		exit (EXIT_FAILURE);
	}
}
