/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 04:55:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/17 04:55:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"
#include "hud.h"
#include "raycasting.h"

/**
 * @brief Draws the player's vision on a mlx image
 */
void	draw_player_view(t_cub *cub)
{
	t_ray		ray;
	t_fvector	ray_dir;
	int			screen_x;
	float		camera_x;

	draw_background(cub);
	screen_x = 0;
	while (screen_x < WIN_WIDTH)
	{
		camera_x = 2.f * (float)screen_x / WIN_WIDTH - 1;
		pthread_mutex_lock(cub->player_data.player_lock);
		ray_dir = fvector_add(cub->player_data.player.rotation,
				fvector_mul(cub->player_data.camera, camera_x));
		pthread_mutex_unlock(cub->player_data.player_lock);
		pthread_mutex_lock(cub->map.map_lock);
		ray = ray_cast(cub, ray_dir);
		pthread_mutex_unlock(cub->map.map_lock);
		cub->z_buffer[screen_x] = ray.length;
		draw_wall(cub, screen_x, ray);
		screen_x++;
	}
	draw_sprites(cub, cub->z_buffer);
	draw_hud(cub);
}
