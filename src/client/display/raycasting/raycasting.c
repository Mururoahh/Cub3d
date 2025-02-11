/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:29:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 07:29:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "raycasting.h"
#include "player.h"

static void		ray_update(t_cub *cub, t_ray *ray, t_vector *map_index);
static t_ray	ray_init(t_cub *cub, t_fvector ray_dir);
static void		set_ray_step(t_ray *ray, t_fvector ray_dir);

t_ray	ray_cast(t_cub *cub, t_fvector ray_dir)
{
	t_ray		ray;
	t_vector	map_index;

	ray = ray_init(cub, ray_dir);
	map_index = vector_init((int) cub->player_data.player.pos.x,
			(int) cub->player_data.player.pos.y);
	while (cub->map.map[map_index.y][map_index.x] != WALL
		&& cub->map.map[map_index.y][map_index.x] != DOOR_CLOSE)
		ray_update(cub, &ray, &map_index);
	if (ray.wall_face == WEST || ray.wall_face == EAST)
	{
		ray.length = ray.ray.x - ray.unit_step.x;
		ray.pos.y = cub->player_data.player.pos.y + ray.length * ray_dir.y;
	}
	else
	{
		ray.length = ray.ray.y - ray.unit_step.y;
		ray.pos.x = cub->player_data.player.pos.x + ray.length * ray_dir.x;
	}
	if (cub->map.map[map_index.y][map_index.x] == DOOR_CLOSE)
		ray.is_door = true;
	return (ray);
}

static void	ray_update(t_cub *cub, t_ray *ray, t_vector *map_index)
{
	ray->is_door = false;
	if (cub->map.map[map_index->y][map_index->x] == DOOR_OPEN)
		ray->is_door = true;
	if (ray->ray.x < ray->ray.y)
	{
		map_index->x += ray->step.x;
		ray->ray.x += ray->unit_step.x;
		if (ray->step.x == 1)
			ray->wall_face = WEST;
		else
			ray->wall_face = EAST;
	}
	else
	{
		map_index->y += ray->step.y;
		ray->ray.y += ray->unit_step.y;
		if (ray->step.y == 1)
			ray->wall_face = NORTH;
		else
			ray->wall_face = SOUTH;
	}
}

static t_ray	ray_init(t_cub *cub, t_fvector ray_dir)
{
	t_ray	ray;

	ray.pos = cub->player_data.player.pos;
	ray.unit_step.x = fabsf(1 / ray_dir.x);
	ray.unit_step.y = fabsf(1 / ray_dir.y);
	ray.ray = fvector_init(0, 0);
	ray.is_door = false;
	set_ray_step(&ray, ray_dir);
	return (ray);
}

static void	set_ray_step(t_ray *ray, t_fvector ray_dir)
{
	if (ray_dir.x > 0)
	{
		ray->step.x = 1;
		ray->ray.x = ((int) ray->pos.x + 1 - ray->pos.x) * ray->unit_step.x;
	}
	else
	{
		ray->step.x = -1;
		ray->ray.x = (ray->pos.x - (int) ray->pos.x) * ray->unit_step.x;
	}
	if (ray_dir.y > 0)
	{
		ray->step.y = 1;
		ray->ray.y = ((int) ray->pos.y + 1 - ray->pos.y) * ray->unit_step.y;
	}
	else
	{
		ray->step.y = -1;
		ray->ray.y = (ray->pos.y - (int) ray->pos.y) * ray->unit_step.y;
	}
}
