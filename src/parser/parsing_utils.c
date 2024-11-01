/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:18:04 by splattje          #+#    #+#             */
/*   Updated: 2024/11/01 09:35:08 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "my_error.h"

/**
 * @param data a double pointer to the main data struct (t_data)
 * @brief gets the width and height of the seleced map;
 */
void	get_map_height_width(t_data **data)
{
	int			width;
	int			height;
	t_map_list	*list;

	width = 0;
	list = (*data)->map->map_list;
	while (list != NULL)
	{
		if ((int)list->line_size > width)
			width = list->line_size;
		list = list->next;
	}
	height = map_list_size(
			(*data)->map->map_list->next->next->next->next
			->next->next->next->next);
	(*data)->height = height;
	(*data)->width = width;
}

/**
 * @param line a char pointer with the newest line form the map
 * @return a new node for the map linked list
 * @brief makes a new node for the linked list that holds
 * the line of the map file being read
 */
t_map_list	*new_map_list(char *line)
{
	t_map_list	*map_list;

	if (line == NULL)
		return (NULL);
	map_list = (t_map_list *)malloc(sizeof(t_map_list));
	if (map_list == NULL)
		return (print_error(ERR_MALLOC), NULL);
	map_list->line = line;
	map_list->line_size = ft_strlen(map_list->line);
	map_list->next = NULL;
	return (map_list);
}

/**
 * @param list a pointer to the start node (t_map_list)
 * @return the amound of nodes in the list
 * @brief counds the amound of nodes in the linked list
 */
size_t	map_list_size(t_map_list *list)
{
	size_t		size;
	t_map_list	*position;

	size = 0;
	position = list;
	while (position != NULL)
	{
		++size;
		position = position->next;
	}
	return (size);
}

/**
 * @param data a double pointer to the main data struct (t_data)
 * @param new a new node to be added to the end of data->map->map_list
 * @brief adds the new line of the map to the back of the linked list
 */
void	map_list_add_back(t_data **data, t_map_list *new)
{
	t_map_list	*result;

	if ((*data)->map->map_list != NULL)
	{
		result = (*data)->map->map_list;
		while (result->next != NULL)
			result = result->next;
		result->next = new;
	}
	else
		(*data)->map->map_list = new;
}

/**
 * @param head a pointer to the map linked list struct (t_map_list)
 * @param skip the amount of characters to skip from the start
 * @return a sub string for the with the location of the images or the rgb value
 * @brief sets the sub string for the map linked list struct
 */
char	*set_map_info(t_map_list *head, int skip)
{
	char		*result;
	t_map_list	*position;
	t_map_list	*tmp;

	position = head;
	result = ft_strdup(position->line + skip);
	if (result == NULL)
		return (print_error(ERR_MALLOC), NULL);
	tmp = position->next;
	position = tmp;
	head = position;
	return (result);
}
