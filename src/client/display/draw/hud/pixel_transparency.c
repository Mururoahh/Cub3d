/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_transparency.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:21:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/13 04:21:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

int	pixel_transparency(t_cub *cub, t_vector screen, int color)
{
	float	transparency;
	float	inv_transparency;
	int		screen_color;
	int		new_color;

	transparency = (color & 0xFF000000) >> 24;
	transparency = transparency / 0xFF;
	inv_transparency = 1.f - transparency;
	screen_color = *(int *)(cub->mlx_data->img_data.addr
			+ screen.x * cub->mlx_data->img_data.bit_ratio
			+ screen.y * cub->mlx_data->img_data.line_length);
	new_color = 0;
	new_color |= ((int)(((color & 0xFF0000) >> 16) * transparency)
			+ (int)(((screen_color & 0xFF0000) >> 16) * inv_transparency))
		<< 16;
	new_color |= ((int)(((color & 0xFF00) >> 8) * transparency)
			+ (int)(((screen_color & 0xFF00) >> 8) * inv_transparency))
		<< 8;
	new_color |= ((int)((color & 0xFF) * transparency)
			+ (int)((screen_color & 0xFF) * inv_transparency));
	return (new_color);
}

int	color_transparency(int screen_color, int color)
{
	float	transparency;
	float	inv_transparency;
	int		new_color;

	transparency = (color & 0xFF000000) >> 24;
	transparency = transparency / 0xFF;
	inv_transparency = 1.f - transparency;
	new_color = 0;
	new_color |= ((int)(((color & 0xFF0000) >> 16) * transparency)
			+ (int)(((screen_color & 0xFF0000) >> 16) * inv_transparency))
		<< 16;
	new_color |= ((int)(((color & 0xFF00) >> 8) * transparency)
			+ (int)(((screen_color & 0xFF00) >> 8) * inv_transparency))
		<< 8;
	new_color |= ((int)((color & 0xFF) * transparency)
			+ (int)((screen_color & 0xFF) * inv_transparency));
	return (new_color);
}
