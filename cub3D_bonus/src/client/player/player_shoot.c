/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:19:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/07 21:19:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "draw.h"
#include "weapons_data.h"
#include "event.h"

static t_damage get_damage_by_weapon(t_weapon weapon);

void	player_shoot(t_cub *cub)
{
	t_enemy			enemies[PLAYER_LIMIT - 1];
	t_player		player;
	t_player_status	player_status;
	t_fvector		camera;
	t_draw_param	dp;
	size_t			i;

	pthread_mutex_lock(cub->player_data.player_lock);
	player = cub->player_data.player;
	player_status = cub->player_data.player_status;
	pthread_mutex_unlock(cub->player_data.player_lock);
	enemies_set_dist(cub, enemies, player);
	i = 0;
	while (i < PLAYER_LIMIT - 1)
	{
		if (enemies[i].id != -1)
		{
			camera = enemy_camera_projection(cub, enemies[i]);
			dp = enemy_get_draw_param(cub, camera);
			if (dp.screen.x < WIN_WIDTH / 2 + dp.width / 2
				&& dp.screen.x > WIN_WIDTH / 2 - dp.width / 2)
			{
//				add_damage_event(cub, enemies[i].id,
//					get_damage_by_weapon(player_status.weapon_equipped));
				printf("Hit: %d damage\n", get_damage_by_weapon(player_status.weapon_equipped));
			}
			else
				printf("Miss\n");
		}
		i++;
	}
}

static t_damage get_damage_by_weapon(t_weapon weapon)
{
	const t_weapon		weapon_index[] =
		{KNIFE_INDEX, PISTOL_INDEX,ASSAULT_RIFLE_INDEX};
	const t_damage		damage[] =
		{KNIFE_DAMAGE, PISTOL_DAMAGE, ASSAULT_RIFFLE_DAMAGE};
	size_t	count;

	count = 0;
	while (count < NB_WEAPONS)
	{
		if (weapon == weapon_index[count])
			return (damage[count]);
		count++;
	}
	return (0);
}
