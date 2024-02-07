/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:21:01 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/07 21:32:57 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_error(void)
{
	ft_printf(ERROR_MESSAGE);
	exit(EXIT_FAILURE);
}

double	map(t_fractol *mandel)
{
	return ((BLACK - SKYBLUE) * mandel->iter / MAXITERATIONS + SKYBLUE);
}
