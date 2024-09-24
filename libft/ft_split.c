/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 11:54:47 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 08:44:42 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	word_count;
	int	index;

	word_count = 0;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			word_count++;
			while (s[index] != '\0' && s[index] != c)
				index++;
		}
		if (s[index] != '\0')
			index++;
	}
	return (word_count);
}

static char	**ft_freemem(char **s, size_t index)
{
	while (s[index] != NULL && index >= 0)
	{
		free(s[index]);
		s[index] = NULL;
		index--;
	}
	free(s);
	s = NULL;
	return (NULL);
}

static char	**set_words(char const **s, char c, size_t *index, char ***words)
{
	size_t	len;

	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	(*words)[(*index)] = ft_substr(*s, 0, len);
	if ((*words)[(*index)] == NULL)
	{
		*index = *index - 1;
		return (ft_freemem(*words, *index));
	}
	(*index)++;
	(*s) += len;
	return ((char **)s);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	size_t	word_count;
	char	**words;

	if (!s)
		return (NULL);
	word_count = ft_wordcount(s, c);
	words = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (words == NULL)
		return (NULL);
	index = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			if (set_words(&s, c, &index, &words) == NULL)
				return (NULL);
		}
	}
	words[index] = NULL;
	return (words);
}
