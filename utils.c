/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:21:01 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/10 01:38:51 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(void)
{
	ft_printf(ERROR_MESSAGE);
	exit(EXIT_FAILURE);
}

double	map(t_fractol *mandel)
{
	double	color;

	color = (BLACK - WHITE) * mandel->iter / MAXITERATIONS + WHITE;
	return (color);
}
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