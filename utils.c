/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:21:01 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/26 00:11:22 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// color = (BLACk - WHITE) * mandel->iter /   mandel->max_iterter + -100;
// BLACK 0x000000
// WHITE 0xFFFFFF
// LIGHTPINK 0xFFD1DC
// LIGHTSALMON 0xFFA07A
// GOLD 0xFFD700
// PALEGREEN 0x98FB98
// LIGHTBLUE 0xADD8E6
// HOTPINK 0xFF69B4
// ORANGE 0xFFA500
// TOMATO 0xFF6347
// MOCCASIN 0xFFE4B5
// SKYBLUE 0x87CEEB
// RED 0xFF0000
// LIME 0x00FF00
// BLUE 0x0000FF
// MAGENTA 0xFF00FF
// CYAN 0x00FFFF
// YELLOW 0xFFFF00
// DEEPPINK 0xFF1493
// BLUEVIOLET 0x8A2BE2
// LIMEGREEN 0x32CD32
#include "fractol.h"

// int	pixel_clr(int itr)
// {
// 	int	red;
// 	int	green;
// 	int	blue;

// 	red = itr % 255;
// 	green = itr % 128;
// 	blue = itr % 64;
// 	return (0xFF << 24 | red << 16 | green << 8 | blue);
// }

int	pixel_clr(t_fractol *mandel, int itr)
{
	double	frequency;
	int		red;
	int		green;
	int		blue;

	if (itr == 0)
		return (WHITE);
	if (itr == mandel->max_iter)
		return (BLACK);
	itr = (mandel->max_iter - itr);
	frequency = 0.1;
	red = (sin(frequency * itr + 2) * 127.5 + 127.5);
	green = (sin(frequency * itr + 0) * 127.5 + 127.5);
	blue = (sin(frequency * itr + 4) * 127.5 + 127.5);

	return (0xFF << 24 | (int)blue << 16 | (int)green << 8 | (int)red);
}

void	ft_error(void)
{
	ft_putstr_fd(ERROR_MESSAGE, 1);
	exit(EXIT_FAILURE);
}

double	map(t_fractol *mandel)
{
	double	color;

	// color = (WHITE - BLACK) * mandel->iter / mandel->max_iter + BLACK;
	color = 1.0 - (double)mandel->iter / (double)mandel->max_iter;
	return (color);
}

double	map2(t_fractol *mandel, double coord)
{
	double	result;

	result = 0.0;
	result = (1.5 - - 1.5) * coord / mandel->img->width + -1.5;
	return (result);
}

double	map3(t_fractol *mandel, double coord)
{
	double	result;

	result = 0.0;
	result = ( -1.5 - 1.5) * coord / mandel->img->height + 1.5;
	return (result);
}

void	instruction(void)
{
	ft_putstr_fd("|------------------------------------------------|\n", 1);
	ft_putstr_fd("|                                                |\n", 1);
	ft_putstr_fd("|  Have fun with my fractal generator!           |\n", 1);
	ft_putstr_fd("|  You can generate: MANDELBROT by ./mandelbrot  |\n", 1);
	ft_putstr_fd("|  JULIA by ./julia <real param> <imagin param>  |\n", 1);
	ft_putstr_fd("|  NEWTON by ./newton                            |\n", 1);
	ft_putstr_fd("|  list of availabale options:                   |\n", 1);
	ft_putstr_fd("|  ARROW UP: move up                             |\n", 1);
	ft_putstr_fd("|  ARROW DOWN: move down                         |\n", 1);
	ft_putstr_fd("|  ARROW ->: move right                          |\n", 1);
	ft_putstr_fd("|  ARROW <- : move left                          |\n", 1);
	ft_putstr_fd("|  ZOOM IN AND OUT: scroll mouse wheel           |\n", 1);
	ft_putstr_fd("|  CHANGE COLORS: + AND -                        |\n", 1);
	ft_putstr_fd("|  CHANGE SHAPE(ONLY FOR JULIA):                 |\n", 1);
	ft_putstr_fd("|  move cursor inside of image                   |\n", 1);
	ft_putstr_fd("|                                                |\n", 1);
	ft_putstr_fd("|------------------------------------------------|\n", 1);
}
