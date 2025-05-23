/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:32:19 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/25 23:38:12 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifndef STDERR_FILENO
#  define STDERR_FILENO 2
# endif
# ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
# endif
# ifndef STDIN_FILENO
#  define STDIN_FILENO 0
# endif

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/include/libft.h"
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# ifdef __unix__
#  include <unistd.h>
# endif

# define ERROR_MESSAGE "Error!\nEnter:\n./fractol mandelbrot\nor ./fractol"
# define ERROR_MESSAGE1 " julia \t<param1> \t<param2>\nor ./fractol newton"
# define WIDTH 720
# define HEIGHT 720
# define MAXITERATIONS 1000
# define EPSILON 0.00000001

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
	uint32_t	color;
	int32_t		x_pos;
	int32_t		y_pos;
	mlx_image_t	*img;
	mlx_t		*mlx;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		real;
	double		imag;
	double		c_real;
	double		c_imag;
	double		z_real;
	double		z_imag;
	double		z_retemp;
	int			iter;
	int			max_iter;
	int			draw;
	int			x;
	int			y;
	float		tolerance;
	char		*name;	// New members for effects
	bool		effect_random_trigger;
	bool		effect_psy_flow_active;
	bool		effect_active; // Flag to indicate if any effect is active
	float		psy_activity_status;
	float		psy_time_factor;
	float		random_time_factor; // Time factor for random animation
	float		psy_spatial_factor_x;
	float		psy_spatial_factor_y;
	bool		color_cycling; // Flag for color cycling mode
	float		color_cycle_speed; // Speed of color cycling
	// Storing iteration counts for effects
	int			*pixel_iterations; // Array to store iteration count for each pixel
	int			iterations_max_value_at_render; // max_iter value when pixel_iterations was last updated
}				t_fractol;

typedef struct s_complex
{
	long double		x;
	long double		y;
}				t_complex;

//   utils
void	ft_error(void);
double	map(t_fractol *mandel);
double	map2(t_fractol *mandel, double xpos);
double	map3(t_fractol *mandel, double ypos);
void	instruction(void);
int		pixel_clr(t_fractol *mandel, int itr);
//mandelbrot
void	ft_mandelbrot(void *param);
void	mandel_init(t_fractol *mandel, mlx_t *mlx);
//julia
void	julia_init(t_fractol *mandel, mlx_t *mlx);
void	ft_julia(void *param);
//atod
double	ft_atod(char *str);
//hook event
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	scroll_func(double xdelta, double ydelta, void *param);
void	julia_dynamic(double xpos, double ypos, void *param);
//bonus_utils.c
void	cursor_zooming(t_fractol *mandel, double xpos, double ypos, double a);
//bonus
void	newton_init(t_fractol *newton, mlx_t *mlx);
void	ft_newton(void *param);
// Prototypes for new effect functions
void	ft_randomize_effect(t_fractol *f);
void	ft_psy_flow_effect(t_fractol *f);

#endif