/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:57:56 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 20:38:54 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

bool	spe_case(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' '
		|| c == '\'' || c == '"')
		return (true);
	return (false);
}

/**
** Copie le char lu dans le buffer, realloue un buffer de taille superieure
** le fera jusqu'a ce que le buffer constitue un arg entier *
*** @author malatini
*/
char	*copy_in_buffer(char *old_buf, char c, t_mem *mem)
{
	int		len;
	char	*new;
	int		i;

	(void)mem;
	i = 0;
	new = NULL;
	len = ft_strlen(old_buf) + 1;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		failure(-1, mem);
	while (old_buf && old_buf[i])
	{
		new[i] = old_buf[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	if (old_buf)
		free(old_buf);
	return (new);
}

/**
 * ! Deprecated
 ** Ajoute un chaine de chars au buffer
 * @author: malatini
 */
char	*copy_str_in_buf(char *old_buf, char *s1, t_mem *mem)
{
	int		len;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(old_buf) + ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		failure(-1, mem);
	while (old_buf && old_buf[i])
	{
		new[i] = old_buf[i];
		i++;
	}
	while (s1[j])
	{
		new[i + j] = s1[j];
		j++;
	}
	new[i + j] = '\0';
	if (old_buf)
		free(old_buf);
	return (new);
}

void	quote_expand(t_mem *m, int *pos)
{
	char	*key;
	char	*value;

	key = cpy_key(m, *pos);
	value = find_value_in_env(key, m);
	if (value)
		*(m->buffer) = copy_str_in_buf(*(m->buffer), value, m);
	*pos += ft_strlen(key) + 1;
	free(value);
	free(key);
}
