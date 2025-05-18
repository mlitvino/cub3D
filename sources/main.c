/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:03:22 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/18 22:47:18 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	// parser(data)
	init_data(&data);
	show_unit_map(&data);
	show_char_pos(&data, &data.player);
	mlx_loop(data.mlx_data.mlx_ptr);
	// clean_all(&data);
	return (0);
}
