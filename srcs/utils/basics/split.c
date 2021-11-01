/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:32:14 by malatini          #+#    #+#             */
/*   Updated: 2021/09/24 14:37:29 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_find_charsep(char str, char c)
{
	if (c == str)
		return (1);
	else if (str == '\0')
		return (1);
	return (0);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if ((ft_find_charsep(str[i + 1], c) == 1
				&& ft_find_charsep(str[i], c) == 0))
			word++;
		i++;
	}
	return (word);
}

static void	ft_copy_word(char *dest, const char *from, char c)
{
	int	i;

	i = 0;
	while (ft_find_charsep(from[i], c) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	ft_transfert(char **tab, const char *str, char c)
{
	int	i;
	int	word;
	int	j;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (ft_find_charsep(str[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_find_charsep(str[i + j], c) == 0)
				j++;
			tab[word] = malloc(sizeof(char) * (j + 1));
			ft_copy_word(tab[word], str + i, c);
			i = i + j;
			word++;
		}
	}
	tab[word] = NULL;
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		word;

	if (!str)
		return (NULL);
	word = ft_count_words(str, c);
	tab = malloc(sizeof(char *) * (word + 1));
	if (tab == NULL)
		return (NULL);
	tab[word] = 0;
	ft_transfert(tab, str, c);
	return (tab);
}
