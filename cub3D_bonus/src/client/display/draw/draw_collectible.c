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
#include "collectible.h"
#include "cub.h"
#include "draw.h"

void	draw_collectible(t_cub *cub, const float *z_buffer)
{
	size_t	i;

	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		draw_collectible_sprite(cub, cub->map.collectible_data.collectible[i], z_buffer);
		i++;
	}
}
