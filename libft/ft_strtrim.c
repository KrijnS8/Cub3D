/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:37:55 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 09:04:07 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_start_end(char **start, char **end, char const *set)
{
	while (**start && ft_strchr(set, **start))
		(*start)++;
	while (*end > *start && ft_strchr(set, **end))
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*start;
	char	*end;
	size_t	new_len;
	char	*trimmed;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	len = ft_strlen(s1);
	start = (char *)s1;
	end = (char *)s1 + len - 1;
	set_start_end(&start, &end, set);
	new_len = (size_t)(end - start) + 1;
	trimmed = (char *)malloc(new_len + 1);
	if (trimmed == NULL)
		return (NULL);
	ft_memcpy(trimmed, start, new_len);
	trimmed[new_len] = '\0';
	return (trimmed);
}
