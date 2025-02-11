/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:16:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 07:16:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"

void	init_hook(t_cub *cub)
{
	mlx_do_key_autorepeatoff(cub->mlx_data->mlx_ptr);
	cub->mlx_data->mouse_disable = true;
	mlx_hook(cub->mlx_data->win_ptr, ON_DESTROY, BUTTON_RELEASE_MASK,
		cub_exit, cub);
	mlx_hook(cub->mlx_data->win_ptr, ON_KEY_DOWN, KEY_PRESS_MASK,
		key_press, cub);
	mlx_hook(cub->mlx_data->win_ptr, ON_KEY_UP, KEY_RELEASE_MASK,
		key_release, cub);
	mlx_mouse_hook(cub->mlx_data->win_ptr, mouse_hook, cub);
}
