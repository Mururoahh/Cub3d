/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:28:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/09 16:28:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef HUD_H
# define HUD_H

# include "cub.h"

# define BULLET_PATH		"asset/hud/bullet.xpm"
# define KNIFE_HUD_PATH		"asset/hud/knife_hud.xpm"
# define PISTOL_HUD_PATH	"asset/hud/pistol_hud.xpm"
# define AR_HUD_PATH		"asset/hud/assault_rifle_hud.xpm"
# define DEATH_SCREEN_PATH  "asset/hud/death_screen.xpm"

# define KNIFE_0			"asset/hud/knife_animation/knife_0.xpm"
# define KNIFE_1			"asset/hud/knife_animation/knife_1.xpm"
# define KNIFE_2			"asset/hud/knife_animation/knife_2.xpm"
# define KNIFE_3			"asset/hud/knife_animation/knife_3.xpm"
# define KNIFE_4			"asset/hud/knife_animation/knife_4.xpm"
# define KNIFE_5			"asset/hud/knife_animation/knife_5.xpm"
# define KNIFE_6			"asset/hud/knife_animation/knife_6.xpm"

# define PISTOL_0			"asset/hud/pistol_animation/pistol_0.xpm"
# define PISTOL_1			"asset/hud/pistol_animation/pistol_1.xpm"
# define PISTOL_2			"asset/hud/pistol_animation/pistol_2.xpm"
# define PISTOL_3			"asset/hud/pistol_animation/pistol_3.xpm"
# define PISTOL_4			"asset/hud/pistol_animation/pistol_4.xpm"
# define PISTOL_5			"asset/hud/pistol_animation/pistol_5.xpm"
# define PISTOL_6			"asset/hud/pistol_animation/pistol_6.xpm"
# define PISTOL_7			"asset/hud/pistol_animation/pistol_7.xpm"

# define AR_0			"asset/hud/assault_rifle_animation/assault_rifle_0.xpm"
# define AR_1			"asset/hud/assault_rifle_animation/assault_rifle_1.xpm"
# define AR_2			"asset/hud/assault_rifle_animation/assault_rifle_2.xpm"
# define AR_3			"asset/hud/assault_rifle_animation/assault_rifle_3.xpm"
# define AR_4			"asset/hud/assault_rifle_animation/assault_rifle_4.xpm"

# define BORDER_SIZE 2

# define MAP_HALF_SIZE 5
# define MAP_RADIUS 80
# define MAP_PIXEL_OFFSET 20
# define MAP_TRANSPARENCY 0x80000000
# define MAP_EMPTY_COLOR 0x161616
# define MAP_PLAYER_COLOR 0xFF0000
# define MAP_WALL_COLOR 0x000000
# define MAP_FLOOR_COLOR 0xFFFFFF
# define MAP_DOOR_CLOSE_COLOR 0x00FF00
# define MAP_DOOR_OPEN_COLOR 0x0000FF
# define MAP_BORDER_COLOR 0x101010

# define HEALTH_BAR_WIDTH 300
# define HEALTH_BAR_HEIGHT 25
# define HEALTH_BAR_OFFSET 20
# define BORDER_RADIUS 12
# define HB_BORDER_COLOR 0xBB000000
# define HB_EMPTY_COLOR 0x44888888
# define HB_HEALTH_COLOR 0x44d12d

# define AMMO_Y_OFFSET 25
# define AMMO_X_OFFSET 240
# define BULLET_PER_ROW 10
# define BULLET_Y_OFFSET 10

# define KNIFE_OFFSET_X	45
# define KNIFE_OFFSET_Y 20
# define PISTOL_OFFSET_X 110
# define PISTOL_OFFSET_Y 20
# define AR_OFFSET_X 50

# define DEATH_SCREEN_COLOR 0xFF0000
# define DEATH_SCREEN_DURATION 90
# define DEATH_SCREEN_TRANSPARENCY 0x80

typedef struct s_mlx_data	t_mlx_data;

void	draw_hud(t_cub *cub);
void	draw_minimap(t_cub *cub);
void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);
void	draw_health_bar(t_cub *cub);
void	draw_ammo(t_cub *cub);
void	draw_weapon(t_cub *cub);
void	draw_weapon_view(t_cub *cub);
void	draw_crosshair(t_cub *cub);
void	draw_death_screen(t_cub *cub);

int		pixel_transparency(t_cub *cub, t_vector screen, int color);
int		color_transparency(int screen_color, int color);

#endif