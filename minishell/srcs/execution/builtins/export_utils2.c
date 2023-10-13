/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:14:31 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:31:35 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
