/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:41:42 by mlitvino          #+#    #+#             */
/*   Updated: 2025/05/29 15:00:24 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*create_door(t_door **doors_list,int grid_x, int grid_y)
{
	t_door	*new_door;
	t_door	*temp;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (NULL);
	new_door->state = CLOSED;
	new_door->len = BLOCK_SIZE;
	new_door->grid_x = grid_x;
	new_door->grid_y = grid_y;
	new_door->next = NULL;
	// closing timer?
	// closing speed?
	temp = *doors_list;
	while (temp && temp->next)
		temp = temp->next;
	if (!temp)
		*doors_list = new_door;
	else if (!temp->next)
		temp->next = new_door;
	return (new_door);
}
