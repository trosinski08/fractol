/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:19 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/06 19:48:12 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h" 
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR_MESSAGE "tutaj walniemy jakis error message"
# define WIDTH 1080
# define HEIGHT 1080
# define MAXITERATIONS 1000

// Zbiór kolorów
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define LIGHTPINK 0xFFD1DC
# define LIGHTSALMON 0xFFA07A
# define GOLD 0xFFD700
# define PALEGREEN 0x98FB98
# define LIGHTBLUE 0xADD8E6
# define HOTPINK 0xFF69B4
# define ORANGE 0xFFA500
# define TOMATO 0xFF6347
# define MOCCASIN 0xFFE4B5
# define SKYBLUE 0x87CEEB
# define RED 0xFF0000
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define MAGENTA 0xFF00FF
# define CYAN 0x00FFFF
# define YELLOW 0xFFFF00
# define DEEPPINK 0xFF1493
# define BLUEVIOLET 0x8A2BE2
# define LIMEGREEN 0x32CD32

typedef struct s_fractol
{
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		real;
	double		imag;
	double		c_real;
	double		c_imag;
	int			iter;
	double		z_real;
	double		z_imag;
	double		z_retemp;
	uint32_t	color;
	mlx_image_t	*img;
	mlx_t		*mlx;
	int			draw;
}				t_fractol;

int	get_rgba(int r, int g, int b, int a);

#endif