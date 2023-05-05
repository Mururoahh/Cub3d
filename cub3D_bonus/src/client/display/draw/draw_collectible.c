/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* 	 draw_collectible.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include "collectible.h"
#include "cub.h"
#include "draw.h"

static void		collectible_set_dist(t_cub *cub);
static void		collectible_sort(t_cub *cub);

void	draw_collectible(t_cub *cub, const float *z_buffer)
{
	size_t	i;

	collectible_set_dist(cub);
	collectible_sort(cub);
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		draw_collectible_sprite(cub, cub->map.collectible_data.collectible[i], z_buffer);
		i++;
	}
}

/**
 * @brief Set the distance from the player of all collectibles
 */
static void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectible;

	collectible = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		pthread_mutex_lock(cub->player_data.player_lock);
		collectible[i].relative_pos = fvector_sub(cub->player_data.player.pos, collectible[i].pos);
		pthread_mutex_unlock(cub->player_data.player_lock);
		collectible[i].dist = collectible[i].relative_pos.x * collectible[i].relative_pos.x
			+ collectible[i].relative_pos.y * collectible[i].relative_pos.y;
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
static void	collectible_sort(t_cub *cub)
{
	t_collectible	*collectible;
	t_collectible	tmp;
	bool			flag;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < cub->map.collectible_data.size)
		{
			if (collectible[i].dist > collectible[i - 1].dist)
			{
				flag = true;
				tmp = collectible[i];
				collectible[i] = collectible[i - 1];
				collectible[i - 1] = tmp;
			}
			i++;
		}
	}
}
