/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 13:07:19 by splattje      #+#    #+#                 */
/*   Updated: 2023/12/12 10:30:50 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_line_ending(char *str, size_t index)
{
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		index++;
	return (index);
}

char	*get_string(char *str)
{
	char	*new_str;
	size_t	index;
	size_t	sec_index;

	index = 0;
	sec_index = 0;
	if (str[index] == '\0')
	{
		free(str);
		return (NULL);
	}
	index = find_line_ending(str, index);
	new_str = (char *)malloc((gnl_strlen(str) - index + 1));
	if (!new_str)
	{
		free(new_str);
		return (NULL);
	}
	while (str[index])
		new_str[sec_index++] = str[index++];
	new_str[sec_index] = '\0';
	if (!new_str[0])
		return (free_and_null(new_str, &str), NULL);
	free(str);
	return (new_str);
}

char	*read_the_line(char *str)
{
	char	*line;
	size_t	index;

	index = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	index = find_line_ending(str, index);
	line = (char *)malloc(sizeof(char) * index + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n')
	{
		line[index] = str[index];
		index++;
	}
	if (str[index] == '\n')
	{
		line[index] = str[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

char	*free_and_null(char *buffer1, char **buffer2)
{
	free(buffer1);
	free(*buffer2);
	*buffer2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	read_bytes = 1;
	while (!(gnl_strchr(buffer, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, line, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free_and_null(line, &buffer), NULL);
		line[read_bytes] = '\0';
		buffer = gnl_strjoin(buffer, line);
		if (!buffer)
			return (free_and_null(line, &buffer), NULL);
	}
	free(line);
	line = read_the_line(buffer);
	buffer = get_string(buffer);
	return (line);
}
