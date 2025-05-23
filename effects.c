#include "fractol.h"

static uint32_t fast_rand_state = 123456789;

static uint8_t fast_rand(void)
{
	fast_rand_state ^= fast_rand_state << 13;
	fast_rand_state ^= fast_rand_state >> 17;
	fast_rand_state ^= fast_rand_state << 5;
	return (uint8_t)(fast_rand_state & 0xFF);
}

static uint32_t noise_rand(void)
{
	static uint32_t noise_state = 987654321;
	noise_state = noise_state * 1664525 + 1013904223;
	return noise_state;
}

static void ft_add_tv_glitch(t_fractol *f, uint32_t x, uint32_t y, uint8_t *r, uint8_t *g, uint8_t *b)
{
	float glitch_factor;
	uint32_t noise_value;
	
	noise_value = noise_rand();
	if ((noise_value & 0xFFF) == 0)
	{
		if (y % 2 == 0)
		{
			*r = 255;
			*g = 255;
			*b = 255;
		}
		else
		{
			*r = 0;
			*g = 0;
			*b = 0;
		}
		return;
	}
	if ((noise_value & 0xFFFF) == 0)
	{
		glitch_factor = sin(f->random_time_factor * 3.0f + x * 0.01f) * 0.5f + 0.5f;
		*r = (uint8_t)(*r * glitch_factor);
		*g = (uint8_t)(*g * glitch_factor);
		*b = (uint8_t)(*b * glitch_factor);
		return;
	}
}

static void ft_process_static_pixel(t_fractol *f, uint32_t x, uint32_t y)
{
	int iter_count;
	uint8_t r, g, b;
	uint32_t color;
	
	if (f->pixel_iterations[y * WIDTH + x] >= f->iterations_max_value_at_render)
		return;
	iter_count = f->pixel_iterations[y * WIDTH + x];
	if (fast_rand() % 100 < 15) // Increased white pixel chance
	{
		r = 255;
		g = 255;
		b = 255;
	}
	else
	{
		r = 80 + (fast_rand() % 80); // Brighter base colors
		g = 80 + (fast_rand() % 80);
		b = 80 + (fast_rand() % 80);
		if (fast_rand() % 100 < 55) // Higher chance of colored pixels
		{
			r = (r + iter_count * 3) % 256;
			g = (g + iter_count * 5) % 256;
			b = (b + iter_count * 7) % 256;
		}
	}
	ft_add_tv_glitch(f, x, y, &r, &g, &b); // Apply TV-like glitch effects
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	mlx_put_pixel(f->img, x, y, color);
}

static int should_preserve_black(t_fractol *f, uint32_t x, uint32_t y)
{
	// Preserve black areas (which are typically max iterations)
	return f->pixel_iterations[y * WIDTH + x] >= f->iterations_max_value_at_render;
}

void ft_randomize_effect(t_fractol *f)
{
	uint32_t x;
	uint32_t y;
	uint32_t scan_line;
	int preserve_black;
	
	if (!f || !f->img || !f->pixel_iterations)
		return;
	f->random_time_factor += 0.1f; // Update time factor for animations
	fast_rand_state = fast_rand_state * 1103515245 + 12345;
	scan_line = (uint32_t)(sin(f->random_time_factor * 0.5f) * 50.0f + 50.0f) % f->img->height;
	y = 0;
	while (y < f->img->height)
	{
		x = 0;
		// Create occasional horizontal scan lines for TV effect
		if (y == scan_line || (y > 0 && y % 90 == (uint32_t)(f->random_time_factor * 10) % 90))
		{
			while (x < f->img->width)
			{
				preserve_black = should_preserve_black(f, x, y);
				if (!preserve_black)
				{
					uint8_t intensity = 180 + (fast_rand() % 76);
					uint32_t scan_color = (intensity << 24) | (intensity << 16) | (intensity << 8) | 0xFF;
					mlx_put_pixel(f->img, x, y, scan_color);
				}
				x++;
			}
		}
		else
		{
			while (x < f->img->width)
			{
				ft_process_static_pixel(f, x, y);
				x++;
			}
		}
		y++;
	}
}

static float ft_calculate_chaos_wave(float x, float y, float dx, float dy, 
		float chaos_factor, float wave_intensity, float time_factor, int iter_count)
{
	float distortion_x;
	float distortion_y;
	float chaos_wave;
	
	distortion_x = sin(dx * chaos_factor * 10.0f + time_factor * 1.2f);
	distortion_y = cos(dy * chaos_factor * 8.0f + time_factor * 0.9f);
	chaos_wave = sin(distortion_x * distortion_y * 3.1415f * wave_intensity);
	chaos_wave += cos(x * 0.03f * sin(time_factor * 0.5f) + y * 0.02f * cos(time_factor * 0.3f));
	chaos_wave *= sin(time_factor * 0.8f + iter_count * 0.01f) * 0.5f + 0.5f;
	return (chaos_wave);
}

static float ft_calculate_hue(float chaos_wave, float time_factor, t_fractol *f)
{
	float hue_base;
	float color_shift;
	float dreamlike_hue;
	
	// Use chaos wave to create vibrant, dynamic hue shifts
	hue_base = fmod(chaos_wave + time_factor * 0.25f, 1.0f);
	
	// Create a dreamlike color mapping that's more diverse
	if (hue_base < 0.2f)
		dreamlike_hue = hue_base * 0.25f; // Red range (0.0-0.05)
	else if (hue_base < 0.4f)
		dreamlike_hue = 0.05f + (hue_base - 0.2f) * 0.35f; // Orange to yellow (0.05-0.12)
	else if (hue_base < 0.5f)
		dreamlike_hue = 0.12f + (hue_base - 0.4f) * 0.6f; // Yellow (0.12-0.18)
	else if (hue_base < 0.65f)
		dreamlike_hue = 0.25f + (hue_base - 0.5f) * 0.67f; // Bright green (0.25-0.35)
	else if (hue_base < 0.75f)
		dreamlike_hue = 0.12f + (hue_base - 0.65f) * 0.3f; // Back to yellow range
	else if (hue_base < 0.9f)
		dreamlike_hue = 0.05f + (hue_base - 0.75f) * 0.47f; // Orange range
	else
		dreamlike_hue = 0.8f + (hue_base - 0.9f); // Purple range (0.8-0.9)
	
	// Add color cycling if enabled
	if (f->color_cycling)
	{
		// Create more varied cycling through the dream palette
		color_shift = fmod(sin(time_factor * f->color_cycle_speed) * 0.5f + 0.5f, 1.0f);
		
		// Use wider color range for cycling
		if (color_shift < 0.15f)
			color_shift = 0.12f + color_shift * 0.4f; // Yellow range
		else if (color_shift < 0.35f)
			color_shift = 0.05f + (color_shift - 0.15f) * 0.35f; // Orange range
		else if (color_shift < 0.55f)
			color_shift = (color_shift - 0.35f) * 0.25f; // Red range
		else if (color_shift < 0.75f)
			color_shift = 0.25f + (color_shift - 0.55f) * 0.5f; // Bright green
		else 
			color_shift = 0.8f + (color_shift - 0.75f) * 0.6f; // Purple range
			
		hue_base = color_shift;
	}
	else
	{
		hue_base = dreamlike_hue;
	}
	
	return (hue_base);
}

/* Forward declaration */
static void ft_continue_process_pixel(t_fractol *f, uint32_t x, uint32_t y,
		float chaos_wave, float *rgb_vals);

static void ft_calculate_rgb(float i, float unused_ff, float p, float q, float t,
		float *r_val, float *g_val, float *b_val)
{
	(void)unused_ff; /* Declaring as unused to avoid compiler warning */
	if (i == 0.0f) {
		*r_val = 1.0f; *g_val = t; *b_val = p;
	} else if (i == 1.0f) {
		*r_val = q; *g_val = 1.0f; *b_val = p;
	} else if (i == 2.0f) {
		*r_val = p; *g_val = 1.0f; *b_val = t;
	} else if (i == 3.0f) {
		*r_val = p; *g_val = q; *b_val = 1.0f;
	} else if (i == 4.0f) {
		*r_val = t; *g_val = p; *b_val = 1.0f;
	} else {
		*r_val = 1.0f; *g_val = p; *b_val = q;
	}
}

static void ft_process_pixel(t_fractol *f, uint32_t x, uint32_t y, 
		float chaos_factor, float wave_intensity)
{
	int iter_count;
	float center_x, center_y, dx, dy, chaos_wave, hue_base, h, i, ff;
	float p, q, t, r_val, g_val, b_val;
	float rgb_vals[3];
	
	if (f->pixel_iterations[y * WIDTH + x] >= f->iterations_max_value_at_render)
		return;
	iter_count = f->pixel_iterations[y * WIDTH + x];
	center_x = f->img->width / 2.0f;
	center_y = f->img->height / 2.0f;
	dx = (x - center_x) / center_x;
	dy = (y - center_y) / center_y;
	chaos_wave = ft_calculate_chaos_wave(x, y, dx, dy, chaos_factor, 
			wave_intensity, f->psy_time_factor, iter_count);
	hue_base = ft_calculate_hue(chaos_wave, f->psy_time_factor, f);
	h = hue_base * 6.0f;
	i = floor(h);
	ff = h - i;
	p = 0.0f;
	q = 1.0f - ff;
	t = ff;
	r_val = 1.0f;
	g_val = 0.0f;
	b_val = 0.0f;
	ft_calculate_rgb(i, ff, p, q, t, &r_val, &g_val, &b_val);
	rgb_vals[0] = r_val;
	rgb_vals[1] = g_val;
	rgb_vals[2] = b_val;
	ft_continue_process_pixel(f, x, y, chaos_wave, rgb_vals);
}

static void ft_apply_pulsation(t_fractol *f, float *chaos_intensity, float chaos_wave, int iter_count)
{
	float pulse;
	float wave_modifier;
	float rainbow_pulse;
	
	// Create multiple pulsation frequencies for a more psychedelic effect
	pulse = sin(f->psy_time_factor * 2.0f) * 0.5f + 0.5f;
	wave_modifier = sin(iter_count * 0.03f + f->psy_time_factor) * 0.3f;
	rainbow_pulse = sin(f->psy_time_factor * 0.7f + iter_count * 0.01f) * 0.5f + 0.5f;
	
	// Create more complex pulsating effect with varying intensities
	if (pulse > 0.7f)
	{
		*chaos_intensity *= 1.0f + pulse * 0.6f; // Stronger intensity during pulse peaks
		if (fabs(chaos_wave) > 0.6f)
		{
			*chaos_intensity *= 1.3f + rainbow_pulse * 0.2f;
		}
	}
	else if (rainbow_pulse > 0.7f)
	{
		// Add secondary pulsation pattern
		*chaos_intensity *= 1.0f + rainbow_pulse * 0.4f;
		if (fabs(chaos_wave) > 0.5f)
		{
			*chaos_intensity *= 1.2f;
		}
	}
	else
	{
		if (fabs(chaos_wave) > 0.65f)
		{
			*chaos_intensity *= 1.15f + wave_modifier;
		}
	}
}

static void ft_enhance_dreamlike_colors(uint8_t *r, uint8_t *g, uint8_t *b)
{
	// Enhance all colors to make them more vibrant and dreamlike
	
	// Enhance yellows - make extremely vibrant
	if (*r > 180 && *g > 180)
	{
		*r = (uint8_t)fmin(255, *r * 1.2f);
		*g = (uint8_t)fmin(255, *g * 1.2f);
		*b = (uint8_t)fmin(70, *b * 0.5f); // Keep blue low for pure yellows
	}
	
	// Enhance orange tones - rich, warm oranges
	if (*r > 200 && *g > 80 && *g < 180 && *b < 100)
	{
		*r = (uint8_t)fmin(255, *r * 1.15f);
		*g = (uint8_t)fmin(220, *g * 1.1f);
		*b = (uint8_t)fmin(40, *b * 0.4f); // Keep blue very low for vivid orange
	}
	
	// Enhance red tones - make them more brilliant
	if (*r > 180 && *g < 100 && *b < 100)
	{
		*r = (uint8_t)fmin(255, *r * 1.2f);
		*g = (uint8_t)fmin(80, *g * 0.9f);
		*b = (uint8_t)fmin(80, *b * 0.9f);
	}
	
	// Enhance bright greens - make them electric/neon
	if (*g > 180 && *r < 150 && *b < 150)
	{
		*g = (uint8_t)fmin(255, *g * 1.25f);
		*r = (uint8_t)fmin(100, *r * 0.85f);
		*b = (uint8_t)fmin(100, *b * 0.7f);
	}
	
	// Enhance purples - make them more psychedelic
	if (*r > 150 && *b > 150 && *g < 120)
	{
		*r = (uint8_t)fmin(255, *r * 1.15f);
		*b = (uint8_t)fmin(255, *b * 1.2f);
		*g = (uint8_t)fmin(80, *g * 0.8f); // Keep green low for vivid purple
	}
	
	// Add occasional flashes of brightness
	if ((*r + *g + *b) > 500)
	{
		// For already bright colors, make them even brighter
		*r = (uint8_t)fmin(255, *r * 1.1f);
		*g = (uint8_t)fmin(255, *g * 1.1f);
		*b = (uint8_t)fmin(255, *b * 1.1f);
	}
}

static void ft_continue_process_pixel(t_fractol *f, uint32_t x, uint32_t y,
		float chaos_wave, float *rgb_vals)
{
	float chaos_intensity;
	uint8_t r, g, b;
	uint32_t color;
	int iter_count;
	float dream_factor;
	
	iter_count = f->pixel_iterations[y * WIDTH + x];
	
	// Make chaos intensity more varied and complex
	chaos_intensity = sin(iter_count * 0.05f + f->psy_time_factor * 1.5f) * 0.5f + 0.5f;
	chaos_intensity += cos(iter_count * 0.03f - f->psy_time_factor * 0.8f) * 0.3f;
	dream_factor = sin(f->psy_time_factor * 0.3f + (float)x * (float)y * 0.00001f) * 0.2f + 0.8f;
	chaos_intensity *= dream_factor; // Apply dream-like modulation
	
	// Apply pulsating effect
	ft_apply_pulsation(f, &chaos_intensity, chaos_wave, iter_count);
	
	chaos_intensity = chaos_intensity * 1.35f; // Slightly higher base intensity
	if (chaos_intensity > 1.0f)
		chaos_intensity = 1.0f;
		
	r = (uint8_t)(rgb_vals[0] * 255.0f * chaos_intensity);
	g = (uint8_t)(rgb_vals[1] * 255.0f * chaos_intensity);
	b = (uint8_t)(rgb_vals[2] * 255.0f * chaos_intensity);
	
	// Apply color enhancement for dreamlike colors
	ft_enhance_dreamlike_colors(&r, &g, &b);
	
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	mlx_put_pixel(f->img, x, y, color);
}

void ft_psy_flow_effect(t_fractol *f)
{
	float chaos_factor;
	float wave_intensity;
	uint32_t x;
	uint32_t y;
	
	if (!f || !f->img || !f->pixel_iterations)
		return;
	f->psy_time_factor += 0.18f;
	
	// Create more complex wave patterns with multiple frequencies
	chaos_factor = sin(f->psy_time_factor * 0.7f) * 0.8f + 0.5f;
	wave_intensity = cos(f->psy_time_factor * 0.3f) * 0.7f + 0.5f;
	
	// Add occasional bursts of intensity
	if ((int)(f->psy_time_factor * 10) % 40 < 5)
	{
		chaos_factor *= 1.4f;
		wave_intensity *= 1.2f;
	}
	y = 0;
	while (y < f->img->height)
	{
		x = 0;
		while (x < f->img->width)
		{
			ft_process_pixel(f, x, y, chaos_factor, wave_intensity);
			x++;
		}
		y++;
	}
}
