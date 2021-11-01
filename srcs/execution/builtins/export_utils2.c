/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:14:31 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 20:49:12 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Va permettre de realiser l'expansion (remplace les keys par les values)
** Utilisee dans le heredoc et fonction similaire parsing
* @author: malatini
*/
char	*expand_line(char *line, t_mem *m, int i, char *temp)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char));
	if (!buffer)
		failure(-1, m);
	buffer[0] = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			i += 2;
			temp = ft_itoa(return_last_ret(m), m);
			buffer = copy_str_in_buf(buffer, temp, m);
			free(temp);
		}
		else if (line[i] == '$' && is_key_char_begin(line[i + 1]))
		{
			m->line = line;
			m->buffer = &buffer;
			quote_expand(m, &i);
		}
		else if (line[i++])
			buffer = copy_in_buffer(buffer, line[i - 1], m);
	}
	return (buffer);
}
