/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:29:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/01 15:29:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static int	receive_confirmation(int client_socket);
static int	map_size_send(int client_socket, size_t height, size_t width);
static int	map_content_send(int client_socket, t_server_data *server_data);
static int	spawn_send(int client_socket, t_spawn *spawn);

int	map_send(int client_socket, t_server_data *server_data, t_spawn *spawn)
{
	if (map_size_send(client_socket, server_data->map->height,
			server_data->map->width) == -1)
		return (-1);
	if (map_content_send(client_socket, server_data) == -1)
		return (-1);
	if (spawn_send(client_socket, spawn) == -1)
		return (-1);
	return (0);
}

static int	map_size_send(int client_socket, size_t height, size_t width)
{
	char	buf;

	printf("Send map size\n");
	if (write(client_socket, &height, sizeof(size_t)) == -1
		|| write(client_socket, &width, sizeof(size_t)) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == '1')
		return (cub_error(CLIENT_ERR_MSG));
	printf("Map size send\n");
	return (0);
}

static int	map_content_send(int client_socket, t_server_data *server_data)
{
	size_t	index;
	char	**map;

	index = 0;
	pthread_mutex_lock(server_data->map_lock);
	map = server_data->map->map;
	printf("Send map content\n");
	while (index < server_data->map->height)
	{
		if (write(client_socket, map[index], server_data->map->width) == -1)
		{
			pthread_mutex_unlock(server_data->map_lock);
			return (cub_error(CLIENT_LOST));
		}
		index++;
	}
	pthread_mutex_unlock(server_data->map_lock);
	if (receive_confirmation(client_socket) == -1)
	{
		pthread_mutex_unlock(server_data->map_lock);
		return (-1);
	}
	printf("Map content send\n");
	return (0);
}

static int	receive_confirmation(int client_socket)
{
	char	buf;

	if (read(client_socket, &buf, sizeof(char )) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == '1')
		return (cub_error(CLIENT_ERR_MSG));
	return (0);
}

static int	spawn_send(int client_socket, t_spawn *spawn)
{
	char	buf;

	printf("Send spawn\n");
	if (write(client_socket, &spawn->x, sizeof(size_t)) == -1
		|| write(client_socket, &spawn->y, sizeof(size_t)) == -1
		|| write(client_socket, &spawn->orientation, sizeof(char)) == -1)
		return (cub_error(CLIENT_LOST));
	if (read(client_socket, &buf, sizeof(char )) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == '1')
		return (cub_error(CLIENT_ERR_MSG));
	printf("Spawn send\n");
	return (0);
}
